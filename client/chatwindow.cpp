#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QTime>
#include <QMessageBox>
#include "mainwindow.h"
#include "addusersgroup.h"

ChatWindow::ChatWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,1);
    ui->splitter->setStretchFactor(2,3);
}

ChatWindow::ChatWindow(const QString &login, QWidget *parent)
    :QMainWindow(parent)
    , ui(new Ui::ChatWindow)
{
    currentUser = login;
    currentReceiver = "";
    ui->setupUi(this);
    setWindowTitle(login);
    ui->stackedWidget->setCurrentIndex(0);
    ui->usersEdit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->groupsEdit->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,1);
    ui->splitter->setStretchFactor(2,3);
    userModel1 = new QStringListModel(this);
    userModel2 = new QStringListModel(this);
    groupModel = new QStringListModel(this);
    ui->usersEdit->setModel(userModel1);
    ui->groupsEdit->setModel(groupModel);
    loadUserAndGroupLists();
    connect(&SocketManager::instance(), &SocketManager::messageReceived, this, [this](const QString &msg) {
        qDebug() << msg;
        if (msg.startsWith("NEW_USER|||")) {
            loadUserAndGroupLists();
            // QString newUser = msg.section("|||", 1);
            // if (!users.contains(newUser)) {
            //     users.append(newUser);
            //     userModel->setStringList(users);
            // }
        }
        if (msg.startsWith("DIALOG_WITH|||")) {
            QStringList lines = msg.mid(QString("DIALOG_WITH|||").length()).split("###");

            ui->persChatEdit->clear();
            //QMessageBox::information(lines[0]);
            for (const QString &line : lines) {
                QStringList parts = line.split("||");
                //if (parts.size() != 4) continue;

                QString sender = parts[0];
                QString time = parts[1];
                QString text = parts[2];
                bool me = (sender == currentUser);
                QTextCursor cursor = ui->persChatEdit->textCursor();
                cursor.movePosition(QTextCursor::End);

                QTextBlockFormat format;
                format.setAlignment(me ? Qt::AlignRight : Qt::AlignLeft);
                cursor.insertBlock(format);

                QString html = "<b>" + (me ? "Я" : sender) + "</b> (" + time + "):<br>" + text;
                cursor.insertHtml(html);
                cursor.insertBlock();
                ui->persChatEdit->moveCursor(QTextCursor::End);
                //addMessage(sender, text, time, me);
                // Визуально отделим свои и чужие сообщения
                // if (sender == currentUser) {
                //      ui->persChatEdit->append("<div align='right'><b>Я</b> (" + time + "):<br>" + text + "</div>");
                // } else {
                //     ui->persChatEdit->append("<div align='left'><b>" + sender + "</b> (" + time + "):<br>" + text + "</div>");
                // }
            }

            // Перейдём на вкладку переписки (если есть QStackedWidget)
            //ui->stackedWidget->setCurrentIndex(1);
        }
        if (msg.startsWith("SEND_LS|||")){
            QStringList parts = msg.split("|||");
                //QString sender = parts[0];
                QString time = parts[2];
                QString text = parts[3];
                QTextCursor cursor = ui->persChatEdit->textCursor();
                cursor.movePosition(QTextCursor::End);

                QTextBlockFormat format;
                format.setAlignment(Qt::AlignRight);
                cursor.insertBlock(format);

                QString html = "<b>Я</b> (" + time + "):<br>" + text;
                cursor.insertHtml(html);
                cursor.insertBlock();
                ui->persChatEdit->moveCursor(QTextCursor::End);


            }
        if (msg.startsWith("INBOX|||")) {
            QStringList parts = msg.split("|||");
            QString sender = parts[1];
            QString time = parts[2];
            QString text = parts[3];
            QTextCursor cursor = ui->persChatEdit->textCursor();
            cursor.movePosition(QTextCursor::End);

            QTextBlockFormat format;
            format.setAlignment(Qt::AlignLeft);
            cursor.insertBlock(format);

            QString html = "<b>" + sender + "</b> (" + time + "):<br>" + text;
            cursor.insertHtml(html);
            cursor.insertBlock();
            ui->persChatEdit->moveCursor(QTextCursor::End);

        }
        if(msg.contains("GROUP_ADDED")){
            //QMessageBox::information(this, "ss", "group_added");
            loadUserAndGroupLists();
        }
        if (msg.startsWith("SEND_GROUP|||")){
            QStringList parts = msg.split("|||");
            //QString sender = parts[0];
            QString time = parts[2];
            QString text = parts[3];
            QTextCursor cursor = ui->groupChatEdit->textCursor();
            cursor.movePosition(QTextCursor::End);

            QTextBlockFormat format;
            format.setAlignment(Qt::AlignRight);
            cursor.insertBlock(format);

            QString html = "<b>Я</b> (" + time + "):<br>" + text;
            cursor.insertHtml(html);
            cursor.insertBlock();
            ui->groupChatEdit->moveCursor(QTextCursor::End);
        }
        if (msg.startsWith("GROUP_DIALOG|||")) {
            QStringList lines = msg.mid(QString("GROUP_DIALOG|||").length()).split("###");

            ui->groupChatEdit->clear();
            //QMessageBox::information(lines[0]);
            for (const QString &line : lines) {
                QStringList parts = line.split("||");
                //if (parts.size() != 4) continue;

                QString sender = parts[0];
                QString time = parts[1];
                QString text = parts[2];
                bool me = (sender == currentUser);
                QTextCursor cursor = ui->groupChatEdit->textCursor();
                cursor.movePosition(QTextCursor::End);

                QTextBlockFormat format;
                format.setAlignment(me ? Qt::AlignRight : Qt::AlignLeft);
                cursor.insertBlock(format);

                QString html = "<b>" + (me ? "Я" : sender) + "</b> (" + time + "):<br>" + text;
                cursor.insertHtml(html);
                cursor.insertBlock();
                ui->groupChatEdit->moveCursor(QTextCursor::End);
            }
        }
        if (msg.startsWith("INBOX_GROUP|||")) {
            QStringList parts = msg.split("|||");
            QString sender = parts[1];
            QString time = parts[2];
            QString text = parts[3];
            QTextCursor cursor = ui->groupChatEdit->textCursor();
            cursor.movePosition(QTextCursor::End);

            QTextBlockFormat format;
            format.setAlignment(Qt::AlignLeft);
            cursor.insertBlock(format);

            QString html = "<b>" + sender + "</b> (" + time + "):<br>" + text;
            cursor.insertHtml(html);
            cursor.insertBlock();
            ui->groupChatEdit->moveCursor(QTextCursor::End);

        }
        if (msg.startsWith("GROUP_USERS|||")){

            QStringList users = msg.mid(QString("GROUP_DIALOG|||").length()-1).split("||");
            userModel2->setStringList(users);
            ui->groupUsers->setModel(userModel2);
        }
        if (msg.contains("GROUP_DELETED")){
            loadUserAndGroupLists();
        }
        if (msg.startsWith("USER_ADDED")){
            QString command = "GET_GROUP_USERS " + currentGroup;
            SocketManager::instance().sendMessage(command);
            //loadUserAndGroupLists();
            useradd->close();
        }
        if (msg.contains("ERROR: NOT CREATOR")){
            QMessageBox::information(this, "Оповещение", "Вы не создатель группы");
            useradd->close();
        }
        if (msg.contains("ERROR: ALREADY ADDED")){
            QMessageBox::information(this, "Оповещение", "Пользователь уже состоит в группе");
            useradd->close();
        }
        if (msg.contains("USER_REMOVED")){
            QString command = "GET_GROUP_USERS " + currentGroup;
            SocketManager::instance().sendMessage(command);
            //loadUserAndGroupLists();
            userdel->close();
        }
        if(msg.contains("ERROR: CREATOR")){
            QMessageBox::information(this, "Оповещение", "Владелец группы не может удалить себя");
            userdel->close();
        }


    });
    connect(ui->usersEdit, &QListView::clicked,
            this, &ChatWindow::onUserClicked);
    connect(ui->groupsEdit, &QListView::clicked,
            this, &ChatWindow::onGroupClicked);
    connect(ui->groupUsers, &QListView::clicked,
            this, &ChatWindow::onUserClicked);

}
void ChatWindow::addMessage(const QString& sender, const QString& message, const QString& time, bool isMe) {
    //QString time = QTime::currentTime().toString("hh:mm");

    QString align = isMe ? "right" : "left";
    QString bubbleColor = isMe ? "#d0f0ff" : "#e8e8e8";
    QString nameColor = isMe ? "#007acc" : "#444444";

    QString html = QString(R"(
        <div style="text-align: %1; margin: 6px;">
            <div style="display: inline-block; background-color: %2; padding: 8px 12px; border-radius: 12px; max-width: 60%%;">
                <div style="font-size: 10pt; font-weight: bold; color: %3;">%4</div>
                <div style="font-size: 8pt; color: gray; text-align: right;">%5</div>
                <div style="font-size: 11pt; color: black;">%6</div>
            </div>
        </div>
    )")
                       .arg(align)
                       .arg(bubbleColor)
                       .arg(nameColor)
                       .arg(sender)
                       .arg(time)
                       .arg(message.toHtmlEscaped());

    ui->persChatEdit->append(html);
}

void ChatWindow::setUserList(const QStringList &users)
{
    userModel1->setStringList(users);
}

void ChatWindow::setGroupList(const QStringList &groups)
{
    groupModel->setStringList(groups);
}

QStringList ChatWindow::getAllUsers() const
{
    return userModel1->stringList();
}


ChatWindow::~ChatWindow() {
    // Получаем указатель на MainWindow через родителя
    MainWindow* mainWindow = qobject_cast<MainWindow*>(parent());

    if (mainWindow) {
        SocketManager* manager = mainWindow->getSocketManager();  // Используем геттер
        if (manager) {
            manager->disconnectFromServer();
        }
    }
    delete ui;
    this->show();
}

void ChatWindow::on_sendButton_clicked()
{   if(!currentGroup.isEmpty()){
        //QMessageBox::information(this, "d", "if");
        QString message = ui->messageEdit->toPlainText().trimmed();
        if(!message.isEmpty()){
            QString command = "SEND_TO_GROUP " + currentGroup + " " + message;
            //QMessageBox::information(this, "d", command);
            SocketManager::instance().sendMessage(command);
            ui->messageEdit->clear();
        }
    }
    else  if (!currentReceiver.isEmpty()){
        QString message = ui->messageEdit->toPlainText().trimmed();
        if (!message.isEmpty()) {
            QString command = "SEND_TO_USER " + currentReceiver + " " + message;
            SocketManager::instance().sendMessage(command);
            ui->messageEdit->clear();
        }
    }

}

void ChatWindow::loadUserAndGroupLists()
{
    // Запрос всех пользователей
    SocketManager::instance().sendMessage("GET_USERS");

    // Запрос групп текущего пользователя
    SocketManager::instance().sendMessage("GET_GROUPS " + currentUser);
}

void ChatWindow::onUserClicked(const QModelIndex &index)
{
    ui->stackedWidget->setCurrentIndex(0);
    QString receiver = userModel1->data(index, Qt::DisplayRole).toString();
    if (receiver == currentUser) return;  // не открываем чат с собой
    ui->persChatEdit->clear();
    // Сохраним, с кем сейчас открыт диалог
    currentReceiver = receiver;
    currentGroup = "";
    //QMessageBox::information(this,"q", currentUser+"  "+currentReceiver);

    // Отправим команду серверу на получение диалога
    QString command = "GET_DIALOG_WITH " + receiver;
    SocketManager::instance().sendMessage(command);
}

void ChatWindow::onGroupClicked(const QModelIndex &index)
{
    QString group_toOpen = groupModel->data(index, Qt::DisplayRole).toString();
    ui->groupUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    currentGroup = group_toOpen;
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabText(0, "Чат");
    ui->tabWidget->setTabText(1, "Пользователи");
    ui->tabWidget->setTabText(2, "Настройки");
    ui->groupChatEdit->clear();
    currentReceiver = "";
    QString command = "GET_GROUP_MESSAGES " + group_toOpen;
    SocketManager::instance().sendMessage(command);
    command = "GET_GROUP_USERS " + currentGroup;
    SocketManager::instance().sendMessage(command);
}

void ChatWindow::on_createGroupBut_clicked()
{
    addGroupDialWindow = new CreateGrouDialog(this);
    addGroupDialWindow->setUserList(getAllUsers());
    addGroupDialWindow->show();
}


void ChatWindow::on_tabWidget_currentChanged(int index)
{
    //
}


void ChatWindow::on_delGroupButton_clicked()
{
    QString command = "DELETE_GROUP " + currentGroup;
    SocketManager::instance().sendMessage(command);
}


void ChatWindow::on_addParticipBut_clicked()
{
    useradd = new addUsersGroup;
    useradd->setUserList(currentGroup, getAllUsers());
    useradd->show();
}


void ChatWindow::on_delParticip_clicked()
{
    userdel = new delusergroup;
    userdel->setUserList(currentGroup, userModel2->stringList());
    userdel->show();
}

