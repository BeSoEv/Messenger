#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QStringList>
#include <QSqlDatabase>

class DatabaseManager {
public:
    static DatabaseManager& instance();

    bool connectForCurrentThread(const QString &host,
                                 const QString &dbName,
                                 const QString &user,
                                 const QString &password,
                                 int port = 5432);

    // Оставляем все твои методы — они будут использовать подключение текущего потока
    bool registerUser(const QString &name, const QString &login, const QString &password);
    bool loginUser(const QString &login, const QString &password);
    bool sendPrivateMessage(const QString &sender, const QString &receiver, const QString &message);
    QStringList getMessagesFrom(const QString &sender, const QString &receiver);
    QStringList getDialogWith(const QString &user1, const QString &user2);
    QStringList getAllUserLogins();
    QStringList getGroupsForUser(const QString &login);
    bool createGroup(const QString &groupName, const QString &creatorLogin);
    QString addUserToGroup(const QString &groupName, const QString &creatorLogin, const QString &userToAdd);
    QString removeUserFromGroup(const QString &groupName, const QString &creatorLogin, const QString &userToRemove);
    bool sendGroupMessage(const QString &groupName, const QString &sender, const QString &message);
    QStringList getGroupMessages(const QString &groupName, const QString &userLogin);
    QStringList getGroupUsers(const QString &groupName, const QString &requestingUser);
    bool deleteGroup(const QString &groupName, const QString &creatorLogin);
     QSqlDatabase getDb();
private:
    DatabaseManager() = default;
    ~DatabaseManager() = default;
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;
};

#endif // DATABASEMANAGER_H
