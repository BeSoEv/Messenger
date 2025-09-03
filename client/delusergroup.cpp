#include "delusergroup.h"
#include "ui_delusergroup.h"
#include "socketmanager.h"

delusergroup::delusergroup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::delusergroup)
{
    ui->setupUi(this);
}

void delusergroup::setUserList(const QString &group, const QStringList &users)
{
    currentGroup = group;
    ui->listWidget->clear();
    ui->listWidget->addItems(users);
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
}

delusergroup::~delusergroup()
{
    delete ui;
}

void delusergroup::on_deluserBut_clicked()
{
    QList<QListWidgetItem*> selectedItems = ui->listWidget->selectedItems();

    QStringList selectedUsers;
    for (QListWidgetItem *item : selectedItems) {
        selectedUsers << item->text();
    }

    QString command = "REMOVE_FROM_GROUP " + currentGroup + " " + selectedUsers.join(" ");
    SocketManager::instance().sendMessage(command);
}

