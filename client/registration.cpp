#include "registration.h"
#include "ui_registration.h"
#include <QMessageBox>
#include "socketmanager.h"

Registration::Registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_finishRegButton_clicked()
{
    QString name1 = ui->name1->text().trimmed();
    QString name2 = ui->name2->text().trimmed();
    QString name3 = ui->name3->text().trimmed();
    QString login = ui->loginReg->text().trimmed();
    QString password = ui->passReg->text().trimmed();
    QString password_2 = ui->pass2Reg->text().trimmed();

    if (name1.isEmpty() ||name2.isEmpty() ||name3.isEmpty() ||
        login.isEmpty() || password.isEmpty() || password_2.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля.");
        return;
    }

    if (password != password_2){
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают.");
        return;
    }
    QString full_name = name1 + " " + name2 + " " + name3;
    QString command = "REGISTER " + full_name + " " + login + " " + password;

    // Отправляем команду серверу
    SocketManager::instance().sendMessage(command);

    accept();  // Закрываем диалог регистрации
}


