#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QThread>
#include <QDebug>
#include <QDateTime>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager inst;
    return inst;
}

bool DatabaseManager::connectForCurrentThread(const QString &host,
                                              const QString &dbName,
                                              const QString &user,
                                              const QString &password,
                                              int port)
{
    QString connName = QString("conn_%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
    if (QSqlDatabase::contains(connName)) return true;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connName);
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);
    db.setPort(port);

    if (!db.open()) {
        qDebug() << "Ошибка подключения к БД:" << db.lastError().text();
        return false;
    }

    return true;
}

QSqlDatabase DatabaseManager::getDb() {
    QString connName = QString("conn_%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
    return QSqlDatabase::database(connName);
}
// bool DatabaseManager::connect(const QString &host,
//                               const QString &dbName,
//                               const QString &user,
//                               const QString &password,
//                               int port)
// {
//     db.setHostName(host);
//     db.setDatabaseName(dbName);
//     db.setUserName(user);
//     db.setPassword(password);
//     db.setPort(port);

//     if (!db.open()) {
//         qDebug() << "Ошибка подключения к БД:" << db.lastError().text();
//         return false;
//     }

//     qDebug() << "БД подключена для потока" << connectionName;
//     return true;
// }

bool DatabaseManager::registerUser(const QString &name, const QString &login, const QString &password) {
    QSqlDatabase db = getDb();
    QSqlQuery query(db);
    query.prepare("INSERT INTO users (name, login, password) VALUES (:name, :login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Ошибка регистрации:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::loginUser(const QString &login, const QString &password) {
    QSqlDatabase db = getDb();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Ошибка входа:" << query.lastError().text();
        return false;
    }

    return query.next();  // true, если найдена строка
}

bool DatabaseManager::sendPrivateMessage(const QString &sender, const QString &receiver, const QString &message) {
    QSqlDatabase db = getDb();
    QSqlQuery query(db);
    query.prepare("INSERT INTO personal_messages (sender_login, receiver_login, message, sent_at) "
                  "VALUES (:sender_login, :receiver, :message, CURRENT_TIMESTAMP)");
    query.bindValue(":sender_login", sender);
    query.bindValue(":receiver", receiver);
    query.bindValue(":message", message);

    if (!query.exec()) {
        qDebug() << "Ошибка отправки сообщения:" << query.lastError().text();
        return false;
    }

    return true;
}

QStringList DatabaseManager::getMessagesFrom(const QString &sender, const QString &receiver) {
    QSqlDatabase db = getDb();
    QSqlQuery query(db);
    query.prepare("SELECT message, sent_at FROM personal_messages "
                  "WHERE sender_login = :sender AND receiver_login = :receiver "
                  "ORDER BY sent_at ASC");
    query.bindValue(":sender", sender);
    query.bindValue(":receiver", receiver);

    QStringList results;

    if (!query.exec()) {
        qDebug() << "Ошибка получения сообщений:" << query.lastError().text();
        return results;
    }

    while (query.next()) {
        QString text = query.value(0).toString();
        QString timestamp = query.value(1).toDateTime().toString(Qt::ISODate);
        results.append(sender + "|||" + timestamp + "|||" + text);
    }

    return results;
}

QStringList DatabaseManager::getDialogWith(const QString &user1, const QString &user2) {
    QSqlDatabase db = getDb();
    QSqlQuery query(db);
    query.prepare("SELECT sender_login, message, sent_at FROM personal_messages "
                  "WHERE (sender_login = :u1 AND receiver_login = :u2) OR (sender_login = :u2 AND receiver_login = :u1) "
                  "ORDER BY sent_at ASC");
    query.bindValue(":u1", user1);
    query.bindValue(":u2", user2);

    QStringList dialog;

    if (!query.exec()) {
        qDebug() << "Ошибка получения диалога:" << query.lastError().text();
        return dialog;
    }

    while (query.next()) {
        QString sender = query.value(0).toString();
        QString message = query.value(1).toString();
        QString timestamp = query.value(2).toDateTime().toString(Qt::ISODate);  // удобно парсить

        dialog.append(sender + "||" + timestamp + "||" + message);
    }

    return dialog;
}

QStringList DatabaseManager::getAllUserLogins() {
    QSqlDatabase db = getDb();
    QSqlQuery query(db);
    QStringList users;

    if (!query.exec("SELECT login FROM users ORDER BY login ASC")) {
        qDebug() << "Ошибка получения списка пользователей:" << query.lastError().text();
        return users;
    }

    while (query.next()) {
        users.append(query.value(0).toString());
    }

    return users;
}

QStringList DatabaseManager::getGroupsForUser(const QString &login) {
    QSqlDatabase db = getDb();
    QSqlQuery query(db);
    QStringList groups;

    query.prepare("SELECT group_name FROM groups_users WHERE user_login = :login ORDER BY group_name ASC");
    query.bindValue(":login", login);

    if (!query.exec()) {
        qDebug() << "Ошибка получения групп:" << query.lastError().text();
        return groups;
    }

    while (query.next()) {
        groups.append(query.value(0).toString());
    }

    return groups;
}

bool DatabaseManager::createGroup(const QString &groupName, const QString &creatorLogin) {
    QSqlDatabase db = getDb();
    db.transaction();  // Начинаем транзакцию

    // 1. Вставка в таблицу groups
    qDebug() << groupName;
    QSqlQuery groupQuery(db);
    groupQuery.prepare("INSERT INTO groups VALUES (:g)");
    groupQuery.bindValue(":g", groupName);

    if (!groupQuery.exec()) {
        qDebug() << "Ошибка создания группы:" << groupQuery.lastError().text();
        qDebug() << groupQuery.lastQuery();
        db.rollback();  // откат при ошибке
        return false;
    }

    // 2. Вставка создателя в groups_users
    QSqlQuery userQuery(db);
    userQuery.prepare("INSERT INTO groups_users (group_name, user_login, is_creator) "
                      "VALUES (:g, :u, TRUE)");
    userQuery.bindValue(":g", groupName);
    userQuery.bindValue(":u", creatorLogin);

    if (!userQuery.exec()) {
        qDebug() << "Ошибка добавления создателя в группу:" << userQuery.lastError().text();
        db.rollback();  // откат и удаление созданной группы
        return false;
    }

    return db.commit();  // подтверждаем транзакцию
}



QString DatabaseManager::addUserToGroup(const QString &groupName, const QString &creatorLogin, const QString &userToAdd) {
    QSqlDatabase db = getDb();
    // Проверим, что текущий пользователь — создатель
    QSqlQuery checkCreator(db);
    checkCreator.prepare("SELECT 1 FROM groups_users WHERE group_name = :g AND user_login = :u AND is_creator = TRUE");
    checkCreator.bindValue(":g", groupName);
    checkCreator.bindValue(":u", creatorLogin);

    if (!checkCreator.exec() || !checkCreator.next()) {
        return "not_creator";  // Не создатель — нельзя добавлять
    }

    // Проверим, что пользователь ещё не состоит в группе
    QSqlQuery existsCheck(db);
    existsCheck.prepare("SELECT 1 FROM groups_users WHERE group_name = :g AND user_login = :newuser");
    existsCheck.bindValue(":g", groupName);
    existsCheck.bindValue(":newuser", userToAdd);
    existsCheck.exec();
    if (existsCheck.next()) {
        return "already_here";  // Уже в группе
    }

    // Добавим пользователя
    QSqlQuery add(db);
    add.prepare("INSERT INTO groups_users (group_name, user_login, is_creator) "
                "VALUES (:g, :newuser, FALSE)");
    add.bindValue(":g", groupName);
    add.bindValue(":newuser", userToAdd);

    if(add.exec()){
        return "true";
    }
    return "false";
}

QString DatabaseManager::removeUserFromGroup(const QString &groupName,
                                          const QString &creatorLogin,
                                          const QString &userToRemove)
{
    QSqlDatabase db = getDb();
    // Проверим, что вызывающий — создатель группы
    QSqlQuery checkCreator(db);
    checkCreator.prepare("SELECT 1 FROM groups_users WHERE group_name = :g AND user_login = :u AND is_creator = TRUE");
    checkCreator.bindValue(":g", groupName);
    checkCreator.bindValue(":u", creatorLogin);

    if (!checkCreator.exec() || !checkCreator.next()) {
        return "not_creator";  // не создатель
    }

    // Не даём удалить самого себя (создателя)
    if (creatorLogin == userToRemove) {
        return "creator";
    }

    // Удаляем
    QSqlQuery remove(db);
    remove.prepare("DELETE FROM groups_users WHERE group_name = :g AND user_login = :u");
    remove.bindValue(":g", groupName);
    remove.bindValue(":u", userToRemove);

    if(remove.exec()){
        return "true";
    }
    return "false";
}

bool DatabaseManager::sendGroupMessage(const QString &groupName, const QString &sender, const QString &message)
{
    QSqlDatabase db = getDb();
    // Проверим, что пользователь состоит в группе
    QSqlQuery check(db);
    check.prepare("SELECT 1 FROM groups_users WHERE group_name = :g AND user_login = :u");
    check.bindValue(":g", groupName);
    check.bindValue(":u", sender);

    if (!check.exec() || !check.next()) {
        return false;
    }

    // Вставляем сообщение
    QSqlQuery insert(db);
    insert.prepare("INSERT INTO group_messages (group_name, sender_login, message, sent_at) "
                   "VALUES (:g, :s, :m, CURRENT_TIMESTAMP)");
    insert.bindValue(":g", groupName);
    insert.bindValue(":s", sender);
    insert.bindValue(":m", message);

    return insert.exec();
}

QStringList DatabaseManager::getGroupMessages(const QString &groupName, const QString &userLogin)
{
    QSqlDatabase db = getDb();
    QStringList messages;

    // Проверка: состоит ли пользователь в группе
    QSqlQuery check(db);
    check.prepare("SELECT 1 FROM groups_users WHERE group_name = :g AND user_login = :u");
    check.bindValue(":g", groupName);
    check.bindValue(":u", userLogin);

    if (!check.exec() || !check.next()) {
        return messages;  // пусто — пользователь не состоит в группе
    }

    // Получаем сообщения
    QSqlQuery query(db);
    query.prepare("SELECT sender_login, message, sent_at FROM group_messages "
                  "WHERE group_name = :g ORDER BY sent_at ASC");
    query.bindValue(":g", groupName);

    if (!query.exec()) {
        qDebug() << "Ошибка чтения сообщений группы:" << query.lastError().text();
        return messages;
    }

    while (query.next()) {
        QString sender = query.value(0).toString();
        QString text = query.value(1).toString();
        QString timestamp = query.value(2).toDateTime().toString(Qt::ISODate);

        // Структурированный формат: отправитель ||| время ||| сообщение
        messages.append(sender + "|||" + timestamp + "|||" + text);
    }

    return messages;
}

QStringList DatabaseManager::getGroupUsers(const QString &groupName, const QString &requestingUser)
{
    QSqlDatabase db = getDb();
    QStringList users;

    // Проверка: состоит ли пользователь в группе
    QSqlQuery check(db);
    check.prepare("SELECT 1 FROM groups_users WHERE group_name = :g AND user_login = :u");
    check.bindValue(":g", groupName);
    check.bindValue(":u", requestingUser);

    if (!check.exec() || !check.next()) {
        return users;  // пусто — не в группе
    }

    // Получаем список участников
    QSqlQuery query(db);
    query.prepare("SELECT user_login FROM groups_users WHERE group_name = :g ORDER BY user_login ASC");
    query.bindValue(":g", groupName);

    if (!query.exec()) {
        qDebug() << "Ошибка получения участников группы:" << query.lastError().text();
        return users;
    }

    while (query.next()) {
        users.append(query.value(0).toString());
    }

    return users;
}

bool DatabaseManager::deleteGroup(const QString &groupName, const QString &creatorLogin) {
    QSqlDatabase db = getDb();
    // Проверка, что пользователь — создатель
    QSqlQuery check(db);
    check.prepare("SELECT 1 FROM groups_users WHERE group_name = :g AND user_login = :u AND is_creator = TRUE");
    check.bindValue(":g", groupName);
    check.bindValue(":u", creatorLogin);
    //qDebug() <<  << groupName << creatorLogin;

    if (!check.exec() || !check.next()) {
        qDebug() << "Не создатель или ошибка запроса";
        return false;
    }
    // Удаляем группу из таблицы groups — остальное удалится каскадно
    QSqlQuery query(db);
    query.prepare("DELETE FROM groups WHERE name = :g");
    query.bindValue(":g", groupName);

    return query.exec();
}
