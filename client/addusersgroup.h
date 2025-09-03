#ifndef ADDUSERSGROUP_H
#define ADDUSERSGROUP_H

#include <QDialog>

namespace Ui {
class addUsersGroup;
}

class addUsersGroup : public QDialog
{
    Q_OBJECT

public:
    explicit addUsersGroup(QWidget *parent = nullptr);
    void setUserList(const QString &group, const QStringList &users);
    ~addUsersGroup();

private slots:
    void on_addUserBut_clicked();

private:
    Ui::addUsersGroup *ui;
    QString currentGroup;

};

#endif // ADDUSERSGROUP_H
