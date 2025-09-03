#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <thread>

#include "DatabaseManager.h"
#include <QString>
#include <QTextStream>

#include "handler.h"
#include "onlinemanager.h"
#include <QCoreApplication>
#include <QThread>

#pragma comment(lib, "Ws2_32.lib")  // Подключаем библиотеку сокетов

#define PORT 12345

void handleClient(SOCKET clientSocket,
                  const QString &host,
                  const QString &dbName,
                  const QString &user,
                  const QString &password,
                  int port,
                  OnlineManager &onlineManager)
{
    char buffer[1024];
    // Подключаемся к БД
    if (!DatabaseManager::instance().connectForCurrentThread(host, dbName, user, password, port)) {
        std::cerr << "Ошибка подключения к БД\n";
        closesocket(clientSocket);
        return;
    }
    qDebug() << "Клиент подключён. Поток:" << QThread::currentThreadId();

    QSqlDatabase db = DatabaseManager::instance().getDb();
    QString currentUser;  // хранит логин залогиненного пользователя

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead <= 0) {
            std::cout << "Клиент отключился\n";
            break;
        }

        QString request = QString::fromUtf8(buffer).trimmed();
        if (request.isEmpty()) continue;

        // передаём currentUser по ссылке
        QString response = handleCommand(request, DatabaseManager::instance(), currentUser, clientSocket, onlineManager);

        QByteArray responseBytes = response.toUtf8();
        send(clientSocket, response.toUtf8().constData(), response.toUtf8().size(), 0);
    }

    if (!currentUser.isEmpty()) {
        onlineManager.logoutUser(currentUser);
    }

    closesocket(clientSocket);
}



int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    OnlineManager onlineManager;
    setlocale(LC_ALL, "Russian");

    // Инициализация WinSock
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "Ошибка WSAStartup: " << wsaResult << "\n";
        return 1;
    }


    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Ошибка socket(): " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Ошибка bind(): " << WSAGetLastError() << "\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Ошибка listen(): " << WSAGetLastError() << "\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Сервер запущен на порту " << PORT << "...\n";

    while (true) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Ошибка accept(): " << WSAGetLastError() << "\n";
            continue;
        }

        std::cout << "Новое подключение\n";
        QString dbHost = "localhost";
        QString dbName = "messenger";
        QString dbUser = "postgres";
        QString dbPassword = "7nekva8b";
        int dbPort = 5432;
        std::thread([clientSocket, dbHost, dbName, dbUser, dbPassword, dbPort, &onlineManager]() {
            handleClient(clientSocket, dbHost, dbName, dbUser, dbPassword, dbPort, onlineManager);
        }).detach();
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
