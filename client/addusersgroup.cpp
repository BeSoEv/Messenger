#include "addusersgroup.h"
#include "ui_addusersgroup.h"
#include "socketmanager.h"

addUsersGroup::addUsersGroup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addUsersGroup)
{
    ui->setupUi(this);
}

void addUsersGroup::setUserList(const QString &group, const QStringList &users)
{
    currentGroup = group;
    ui->listWidget->clear();
    ui->listWidget->addItems(users);
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
}

addUsersGroup::~addUsersGroup()
{
    delete ui;
}

void addUsersGroup::on_addUserBut_clicked()
{
    QList<QListWidgetItem*> selectedItems = ui->listWidget->selectedItems();

    QStringList selectedUsers;
    for (QListWidgetItem *item : selectedItems) {
        selectedUsers << item->text();
    }

    QString command = "ADD_TO_GROUP " + currentGroup + " " + selectedUsers.join(" ");
    SocketManager::instance().sendMessage(command);
}

