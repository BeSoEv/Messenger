#include "SocketManager.h"
#include <QDebug>
#include <WS2tcpip.h>

SocketManager::SocketManager() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        qDebug() << "Ошибка WSAStartup:" << result;
    }
}

SocketManager::~SocketManager() {
    disconnectFromServer();
}

SocketManager &SocketManager::instance()
{
    static SocketManager instance;
    return instance;
}

bool SocketManager::connectToServer(const QString &host, quint16 port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        qDebug() << "WinSock init failed";
        return false;
    }

    socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFd == INVALID_SOCKET) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, host.toStdString().c_str(), &addr.sin_addr);

    if (::connect(socketFd, (SOCKADDR*)&addr, static_cast<int>(sizeof(addr))) == SOCKET_ERROR) {
        closesocket(socketFd);
        socketFd = INVALID_SOCKET;
        return false;
    }

    running = true;
    listenThread = std::thread(&SocketManager::listenThreadFunc, this);
    return true;
}

void SocketManager::disconnectFromServer() {
    running = false;
    if (socketFd != INVALID_SOCKET) {
        closesocket(socketFd);
        socketFd = INVALID_SOCKET;
    }
    if (listenThread.joinable()) {
        listenThread.join();
    }
    emit connectionClosed();
    WSACleanup();
}

void SocketManager::sendMessage(const QString &message) {
    if (socketFd != INVALID_SOCKET) {
        std::string msg = message.toUtf8().toStdString() + "\n";
        send(socketFd, msg.c_str(), static_cast<int>(msg.length()), 0);
    }
}

bool SocketManager::isConnected() const {
    return socketFd != INVALID_SOCKET;
}

void SocketManager::listenThreadFunc() {
    char buffer[10000];
    while (running) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(socketFd, buffer, sizeof(buffer), 0);

        if (bytes <= 0) {
            qDebug() << "Сервер отключился или произошла ошибка";
            break;
        }

        QString msg = QString::fromUtf8(buffer).trimmed();
        emit messageReceived(msg);
    }

    // Принудительно закрываем соединение
    if (socketFd != INVALID_SOCKET) {
        closesocket(socketFd);
        socketFd = INVALID_SOCKET;
    }
    running = false;
    emit connectionClosed();  // Уведомляем UI о разрыве
}
