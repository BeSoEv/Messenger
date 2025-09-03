#ifndef DIALOGCONNECTION_H
#define DIALOGCONNECTION_H

#include <QDialog>
#include "SocketManager.h"

namespace Ui {
class DialogConnection;
}

class DialogConnection : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnection(QWidget *parent = nullptr);
    const QString getIp();
    const int getPort();
    void setIp(QString addressName);
    void setPort(int port);
    void setSocketManager(SocketManager *manager);
    ~DialogConnection();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogConnection *ui;
    SocketManager *socketManager = nullptr;
};

#endif // DIALOGCONNECTION_H
