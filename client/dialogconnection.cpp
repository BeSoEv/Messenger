#include "dialogconnection.h"
#include "ui_dialogconnection.h"
#include <QMessageBox>

DialogConnection::DialogConnection(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogConnection)
{
    ui->setupUi(this);
}

const QString DialogConnection::getIp()
{
    return ui->ipEdit->text();
}

const int DialogConnection::getPort()
{
    return ui->portEdit->text().toInt();
}

void DialogConnection::setIp(QString addressName)
{
    ui->ipEdit->setText(addressName);
}

void DialogConnection::setPort(int port)
{
    ui->portEdit->setText(QString::number(port));
}

void DialogConnection::on_buttonBox_accepted()
{
    //QMessageBox::information(this, "Подключение", "Подключение выполнено");//для тестов чисто
    //тут надо отправлять серверу запрос на подключение и получать ответ
    QString host = ui->ipEdit->text().trimmed();
    quint16 port = ui->portEdit->text().toUShort();
    if (!socketManager) {
        QMessageBox::warning(this, "Ошибка", "Менеджер сокета не задан.");
        return;
    }
    if (socketManager->connectToServer(host, port)) {
        QMessageBox::information(this, "Успех", "Подключение установлено!");
        accept();  // Закрываем диалог с кодом OK
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к серверу.");
        reject();
    }
    //if(ok){
    //QMessageBox::information(this, "Подключение", "Подключение выполнено");}
    //else {QMessageBox::warning(this, "Предупреждение", "");}
    //example
    // socket->connectToHost(ip, port);
    // if (!socket->waitForConnected(3000)) {
    //     QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к серверу.");
    // } else {
    //     QMessageBox::warning(this, "Ошибка", query.lastError().text())
    // }
}

void DialogConnection::setSocketManager(SocketManager *manager) {
    socketManager = manager;
}

DialogConnection::~DialogConnection()
{
    delete ui;
}



