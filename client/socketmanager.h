#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QObject>
#include <QString>
#include <WinSock2.h>
#include <thread>
#include <atomic>

#pragma comment(lib, "Ws2_32.lib")

class SocketManager : public QObject {
    Q_OBJECT

public:

    static SocketManager& instance();
    bool connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    void sendMessage(const QString &message);
    bool isConnected() const;

signals:
    void messageReceived(const QString &message);
    void connectionClosed();

private:
    SocketManager();
    ~SocketManager();
    void listenThreadFunc();

    SOCKET socketFd = INVALID_SOCKET;
    std::thread listenThread;
    std::atomic_bool running = false;
};

#endif // SOCKETMANAGER_H
