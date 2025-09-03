#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogconnection.h"
#include <QMessageBox>
#include <socketmanager.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&SocketManager::instance(), &SocketManager::messageReceived,
            this, &MainWindow::onMessageReceived);
}

SocketManager *MainWindow::getSocketManager() const
{
    return socketManager;
}

MainWindow::~MainWindow()
{
    if (socketManager) {
        socketManager->disconnectFromServer();  // Закрываем соединение
    }
        delete ui;
}

void MainWindow::on_connectButton_triggered() {
    DialogConnection dlg(this);

    dlg.setSocketManager(&SocketManager::instance());

    if (dlg.exec() == QDialog::Accepted) {
        connect(&SocketManager::instance(), &SocketManager::messageReceived,
                this, [this](const QString &msg) {
                    //QMessageBox::information(this, "Сообщение от сервера", msg);
                });

        //QMessageBox::information(this, "Успешно", "Подключено к серверу.");
        //ui->loginGroupBox->setVisible(true);
    } else {
        //QMessageBox::warning(this, "Отклонено", "Подключение отменено.");
    }
}

void MainWindow::on_enterButton_clicked()
{
    QString login = ui->loginEdit->text().trimmed();
    QString password = ui->passwEdit->text().trimmed();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин и пароль.");
        return;
    }

    currentLogin = login;  // сохраняем логин текущего пользователя
    QString command = "LOGIN " + login + " " + password;

    SocketManager::instance().sendMessage(command);

    //отправляем серверу запрос на вход для этого пользователя
    //QMessageBox::information(this, "Вход", "Выполнен");//для тестов чисто
    //открываем страницу пользователя
    //windowChat = new ChatWindow();
    //windowChat->show();
    //this->hide();

}


void MainWindow::on_reggButton_clicked()
{
    windowReg = new Registration(this);
    windowReg->show();
}

void MainWindow::onMessageReceived(const QString &message)
{
    QString trimmed = message.trimmed();

    if (trimmed == "REGISTERED") {
        //QMessageBox::information(this, "Регистрация", "Регистрация прошла успешно! Теперь вы можете войти.");
        return;
    }

    if (trimmed == "ERROR: регистрация не удалась") {
        //QMessageBox::critical(this, "Ошибка", "Регистрация не удалась. Логин уже занят или ошибка сервера.");
        return;
    }

    if (trimmed == "LOGIN_OK") {
        //QMessageBox::information(this, "Вход", "Вход выполнен успешно!");

        windowChat = new ChatWindow(currentLogin);
        windowChat->show();
        this->hide();
        return;
    }

    if (trimmed == "LOGIN_FAILED") {
        QMessageBox::warning(this, "Ошибка входа", "Неверный логин или пароль.");
        return;
    }

    if (trimmed.startsWith("USERS_LIST|||")) {
        QStringList users = trimmed.mid(QString("USERS_LIST|||").length()).trimmed().split("||");

        // Передача в ChatWindow — если у тебя есть указатель на него
        if (windowChat)
            windowChat->setUserList(users);
    }

    if (trimmed.startsWith("GROUPS_LIST|||")) {
        QStringList groups = trimmed.mid(QString("GROUPS_LIST|||").length()).trimmed().split("||");

        if (windowChat)
            windowChat->setGroupList(groups);
    }
    //if()

    // Остальные сообщения (если будут)
    qDebug() << "[INFO] Сообщение от сервера:" << trimmed;

}

