#ifndef DELUSERGROUP_H
#define DELUSERGROUP_H

#include <QDialog>

namespace Ui {
class delusergroup;
}

class delusergroup : public QDialog
{
    Q_OBJECT

public:
    explicit delusergroup(QWidget *parent = nullptr);
    void setUserList(const QString &group, const QStringList &users);
    ~delusergroup();

private slots:
    void on_deluserBut_clicked();

private:
    Ui::delusergroup *ui;
    QString currentGroup;
};

#endif // DELUSERGROUP_H
