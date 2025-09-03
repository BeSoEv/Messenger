#ifndef CREATEGROUDIALOG_H
#define CREATEGROUDIALOG_H

#include <QDialog>

namespace Ui {
class CreateGrouDialog;
}

class CreateGrouDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateGrouDialog(QWidget *parent = nullptr);
    void setUserList(const QStringList &users);
    ~CreateGrouDialog();

private slots:
    void on_finisGroupBut_clicked();


private:
    Ui::CreateGrouDialog *ui;
};

#endif // CREATEGROUDIALOG_H
