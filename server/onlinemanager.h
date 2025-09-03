#ifndef ONLINEMANAGER_H
#define ONLINEMANAGER_H

#include <map>
#include <mutex>
#include <QString>
#include <WinSock2.h>

class OnlineManager {
public:
    void loginUser(const QString &login, SOCKET socket);
    void logoutUser(const QString &login);
    bool isOnline(const QString &login);
    SOCKET getSocket(const QString &login);

    bool sendToUser(const QString &receiverLogin, const QString &message);
    void broadcastToGroup(const QStringList &groupUsers,
                          const QString &senderLogin,
                          const QString &message);
    void broadcastToAllExcept(const QString &excludedLogin, const QString &message);

private:
    std::map<QString, SOCKET> onlineUsers;
    std::mutex mutex;
};

#endif // ONLINEMANAGER_H
