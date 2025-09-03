#include "handler.h"

QString handleCommand(const QString &request, DatabaseManager& db, QString &currentUser, SOCKET clientSocket,
                      OnlineManager &onlineManager) {
    QString trimmed = request.trimmed();
    QStringList parts = trimmed.split(' ', Qt::SkipEmptyParts);

    if (parts.isEmpty()) {
        return "ERROR: пустая команда\n";
    }

    QString command = parts[0].toUpper();
    qDebug() << trimmed;
    if (command == "REGISTER") {
        if (parts.size() != 6) {

            return "ERROR: формат — REGISTER фамилия имя отчество login password.\n";
        }

        QString name = parts[1] + " " + parts[2] + " " + parts[3];
        QString login = parts[4];
        QString password = parts[5];

        if (db.registerUser(name, login, password)) {
            // отправляем уведомление всем, кроме себя
            QString notice = "NEW_USER|||" + login;
            onlineManager.broadcastToAllExcept(login, notice);
            qDebug() << "new user: " << login;
            return "REGISTERED\n";
        }
        else {
            return "ERROR: регистрация не удалась\n";
        }
    }


    if (command == "LOGIN") {
        if (parts.size() != 3) {
            return "ERROR: формат — LOGIN login password\n";
        }
        QString login = parts[1];
        QString password = parts[2];
        if (db.loginUser(login, password)) {
            currentUser = login;
            onlineManager.loginUser(currentUser, clientSocket);
            qDebug() << "user online: " << login;
            return "LOGIN_OK\n";
        } else {
            return "ERROR: неверный логин или пароль\n";
        }
    }

    if (currentUser.isEmpty()) {
        return "ERROR: вы не вошли в систему\n";
    }

    if (command == "SEND_TO_USER") {
        if (parts.size() < 3) {
            return "ERROR: формат — SEND_TO_USER login сообщение\n";
        }

        QString receiver = parts[1];
        QString message = parts.mid(2).join(" ");  // всё, что после логина — это сообщение

        if (db.sendPrivateMessage(currentUser, receiver, message)) {
            QString formatted = currentUser + "|||" +
                                QDateTime::currentDateTime().toString(Qt::ISODate) +
                                "|||" + message;

            onlineManager.sendToUser(receiver, formatted);
            return "SEND_LS|||" + formatted + "\n";
        }
        else {
            return "ERROR_LS\n";
        }
    }

    if (command == "GET_MESSAGES_FROM") {
        if (parts.size() != 2) {
            return "ERROR: формат — GET_MESSAGES_FROM login\n";
        }

        QString sender = parts[1];
        QStringList messages = db.getMessagesFrom(sender, currentUser);

        if (messages.isEmpty()) {
            return "Нет сообщений от " + sender + "\n";
        }

        return messages.join("\n") + "\n";  // объединяем все строки в одну
    }

    if (command == "GET_DIALOG_WITH") {
        if (parts.size() != 2) {
            return "ERROR: формат — GET_DIALOG_WITH login\n";
        }

        QString partner = parts[1];
        QStringList dialog = db.getDialogWith(currentUser, partner);

        if (dialog.isEmpty()) {
            return "DIALOG|||EMPTY\n";
        }

        return "DIALOG_WITH|||" + dialog.join("###") + "\n";
    }

    if (command == "GET_USERS") {
        QStringList users = db.getAllUserLogins();

        if (users.isEmpty()) {
            return "USERS_LIST|||EMPTY\n";
        }

        return "USERS_LIST|||" + users.join("||") + "\n";
    }

    if (command == "GET_GROUPS") {
        if (currentUser.isEmpty()) {
            return "ERROR: пользователь не авторизован\n";
        }

        QStringList groups = db.getGroupsForUser(currentUser);

        if (groups.isEmpty()) {
            return "GROUPS_LIST|||EMPTY\n";
        }
        return "GROUPS_LIST|||" + groups.join("||") + "\n";
    }


    // if (command == "CREATE_GROUP") {
    //     if (parts.size() < 2) {
    //         return "ERROR: формат — CREATE_GROUP имя_группы [логины]\n";
    //     }

    //     QString group = parts[1];
    //     if (db.createGroup(group, currentUser)) {
    //         return "Группа создана\n";
    //     } else {
    //         return "ERROR: группа уже существует\n";
    //     }

    // }
    if (command == "CREATE_GROUP") {
        if (parts.size() < 2) {
            return "ERROR: формат — CREATE_GROUP имя_группы [логины]\n";
        }

        QString group = parts[1];
        qDebug() << "parts: " << parts[1];

        if (!db.createGroup(group, currentUser)) {
            return "ERROR: группа уже существует\n";
        }

        // Добавляем остальных участников (parts[2] и далее)
        for (int i = 2; i < parts.size(); ++i) {
            QString loginToAdd = parts[i];
            if (loginToAdd != currentUser) {  // не добавлять себя повторно
                db.addUserToGroup(group, currentUser, loginToAdd);
            }
        }
        onlineManager.broadcastToAllExcept(currentUser, "GROUP_ADDED");
        return "GROUP_ADDED\n";
    }

    if (command == "ADD_TO_GROUP") {
        if (parts.size() < 3) {
            return "ERROR: формат — ADD_TO_GROUP имя_группы логины\n";
        }

        QString group = parts[1];
        QStringList members = db.getGroupUsers(group, currentUser);
        //QString loginToAdd = parts[2];
        for(int i = 2; i < parts.size(); ++i){
            QString loginToAdd = parts[i];
            if (loginToAdd != currentUser){
                QString res = db.addUserToGroup(group, currentUser, loginToAdd);
                qDebug() << res;
                if (res == "true") {
                    onlineManager.broadcastToGroup(members, "", "USER_ADDED");
                    return "USER_ADDED\n";
                } else if (res == "not_creator" ){
                    return "ERROR: NOT CREATOR\n";
                } else if(res == "already_here"){
                    return "ERROR: ALREADY ADDED\n";
                } else{
                    return "ERROR: WHILE ADDING TO GROUP\n";
                }
            }
            else{
                return "ERROR: ALREADY ADDED\n";
            }
        }

    }

    if (command == "REMOVE_FROM_GROUP") {
        if (parts.size() < 3) {
            return "ERROR: формат — REMOVE_FROM_GROUP имя_группы логин\n";
        }

        QString group = parts[1];
        QStringList members = db.getGroupUsers(group, currentUser);
        for(int i=2; i<parts.size(); ++i){
            QString loginToDel = parts[i];
            if(loginToDel != currentUser){
                QString res = db.removeUserFromGroup(group, currentUser, loginToDel);
                if (res == "true"){
                    onlineManager.broadcastToGroup(members, "", "USER_REMOVED");
                    return "USER_REMOVED\n";
                } else if (res == "not_creator"){
                    return "ERROR: NOT CREATOR\n";
                } else{
                    return "ERROR: WHILE REMOVING FROM GROUP\n";
                }
            }
            else{
                return "ERROR: CREATOR";
            }
        }
        // QString loginToRemove = parts[2];
        // QStringList members = db.getGroupUsers(group, currentUser);
        // if (db.removeUserFromGroup(group, currentUser, loginToRemove)) {
        //     onlineManager.broadcastToGroup(members, "", "USER_DELETED");
        //     return "USER_DELETED\n";
        // } else {
        //     return "ERROR: не удалось удалить (возможно, вы не создатель или пытаетесь удалить себя)\n";
        // }
    }

    if (command == "SEND_TO_GROUP") {
        if (parts.size() < 3) {
            return "ERROR: формат — SEND_TO_GROUP имя_группы сообщение\n";
        }

        QString group = parts[1];
        QString text = parts.mid(2).join(" ");

        if (db.sendGroupMessage(group, currentUser, text)) {
            QString formatted = currentUser + "|||" +
                                QDateTime::currentDateTime().toString(Qt::ISODate) +
                                "|||" + text;

            QStringList groupUsers = db.getGroupUsers(group, currentUser);

            onlineManager.broadcastToGroup(groupUsers, currentUser, "INBOX_GROUP|||" + formatted);
            return "SEND_GROUP|||" + formatted + "\n";
        } else {
            return "ERROR: вы не состоите в этой группе\n";
        }
    }

    if (command == "GET_GROUP_MESSAGES") {
        if (parts.size() != 2) {
            return "ERROR: формат — GET_GROUP_MESSAGES имя_группы\n";
        }

        QString group = parts[1];
        QStringList messages = db.getGroupMessages(group, currentUser);

        if (messages.isEmpty()) {
            return "GROUP_DIALOG_EMPTY\n";
        }

        return "GROUP_DIALOG|||" + messages.join("###") + "\n";
    }

    if (command == "GET_GROUP_USERS") {
        if (parts.size() != 2) {
            return "ERROR: формат — GET_GROUP_USERS имя_группы\n";
        }

        QString group = parts[1];
        QStringList members = db.getGroupUsers(group, currentUser);

        if (members.isEmpty()) {
            return "ERROR: вы не состоите в этой группе или группа пуста\n";
        }

        return "GROUP_USERS|||" + members.join("||") + "\n";
    }

    if (command == "DELETE_GROUP") {
        if (parts.size() != 2) return "ERROR: формат — DELETE_GROUP имя_группы\n";

        QString group = parts[1];
        QStringList members = db.getGroupUsers(group, currentUser);

        if (db.deleteGroup(group, currentUser)) {
            // сообщим всем участникам группы
            QString notice = "GROUP_DELETED";
            onlineManager.broadcastToGroup(members, "", notice); // всем без исключения
            return "GROUP_DELETED\n";
        } else {
            return "ERROR: вы не создатель или группа не существует\n";
        }
    }



    return "ERROR: неизвестная команда\n";
}
