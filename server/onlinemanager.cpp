#include "OnlineManager.h"
#include <QStringList>

void OnlineManager::loginUser(const QString &login, SOCKET socket) {
    std::lock_guard<std::mutex> lock(mutex);
    onlineUsers[login] = socket;
}

void OnlineManager::logoutUser(const QString &login) {
    std::lock_guard<std::mutex> lock(mutex);
    onlineUsers.erase(login);
}

bool OnlineManager::isOnline(const QString &login) {
    std::lock_guard<std::mutex> lock(mutex);
    return onlineUsers.find(login) != onlineUsers.end();
}

SOCKET OnlineManager::getSocket(const QString &login) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = onlineUsers.find(login);
    return (it != onlineUsers.end()) ? it->second : INVALID_SOCKET;
}

bool OnlineManager::sendToUser(const QString &receiverLogin, const QString &message) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = onlineUsers.find(receiverLogin);
    if (it == onlineUsers.end()) return false;

    const std::string msg = ("INBOX|||" + message).toUtf8().toStdString() + '\n';
    send(it->second, msg.c_str(), static_cast<int>(msg.length()), 0);
    return true;
}

void OnlineManager::broadcastToGroup(const QStringList &groupUsers,
                                     const QString &senderLogin,
                                     const QString &message)
{
    std::lock_guard<std::mutex> lock(mutex);
    std::string msg = (message).toUtf8().toStdString() + '\n';

    for (const QString &user : groupUsers) {
        if (user == senderLogin) continue;

        auto it = onlineUsers.find(user);
        if (it != onlineUsers.end()) {
            send(it->second, msg.c_str(), static_cast<int>(msg.length()), 0);
        }
    }
}

void OnlineManager::broadcastToAllExcept(const QString &excludedLogin, const QString &message) {
    std::lock_guard<std::mutex> lock(mutex);
    std::string msg = message.toUtf8().toStdString() + '\n';

    for (const auto& pair : onlineUsers) {
        const QString &login = pair.first;
        SOCKET socket = pair.second;

        if (login == excludedLogin) continue;

        send(socket, msg.c_str(), static_cast<int>(msg.length()), 0);
    }
}
