#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <creategroudialog.h>
#include <addusersgroup.h>
#include "delusergroup.h"
namespace Ui {
class ChatWindow;
}

class ChatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    explicit ChatWindow(const QString &login, QWidget *parent = nullptr);
    void loadUserAndGroupLists();
    void addMessage(const QString& sender, const QString& message, const QString& time, bool isMe);
    void setUserList(const QStringList &users);
    void setGroupList(const QStringList &groups);
    QStringList getAllUsers() const;
    ~ChatWindow();

private slots:
    void on_sendButton_clicked();
    void onUserClicked(const QModelIndex &index);
    void onGroupClicked(const QModelIndex &index);

    void on_createGroupBut_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_delGroupButton_clicked();

    void on_addParticipBut_clicked();

    void on_delParticip_clicked();

private:
    Ui::ChatWindow *ui;
    CreateGrouDialog *addGroupDialWindow = nullptr;
    addUsersGroup *useradd = nullptr;
    delusergroup * userdel = nullptr;
    QString currentUser;
    QStringListModel *userModel1;
    QStringListModel *userModel2;
    QStringListModel *groupModel;
    QString currentReceiver;
    QString currentGroup;
};

#endif // CHATWINDOW_H
