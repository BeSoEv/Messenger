#include "creategroudialog.h"
#include "ui_creategroudialog.h"
#include "chatwindow.h"
#include <QMessageBox>
#include "socketmanager.h"
CreateGrouDialog::CreateGrouDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateGrouDialog)
{
    ui->setupUi(this);
}

void CreateGrouDialog::setUserList(const QStringList &users)
{
    ui->userListWidget->clear();
    ui->userListWidget->addItems(users);
    ui->userListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
}

CreateGrouDialog::~CreateGrouDialog()
{
    delete ui;
}

void CreateGrouDialog::on_finisGroupBut_clicked()
{
    QString groupName = ui->group_nameEdit->text().trimmed();
    QList<QListWidgetItem*> selectedItems = ui->userListWidget->selectedItems();

    QStringList selectedUsers;
    for (QListWidgetItem *item : selectedItems) {
        selectedUsers << item->text();  // логины
    }

    if (groupName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите название группы");
        return;
    }

    QString command = "CREATE_GROUP " + groupName + " " + selectedUsers.join(" ");
    QMessageBox::information(this, "send", command);
    SocketManager::instance().sendMessage(command);

    accept();  // Закрываем диалог регистрации
}

