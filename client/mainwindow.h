#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <registration.h>
#include <chatwindow.h>
#include "socketmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    SocketManager* getSocketManager() const;
    ~MainWindow();

private slots:
    void on_connectButton_triggered();
    void on_enterButton_clicked();

    void on_reggButton_clicked();
    void onMessageReceived(const QString &message);


private:
    Ui::MainWindow *ui;
    Registration *windowReg = nullptr;
    ChatWindow *windowChat = nullptr;
    SocketManager *socketManager = nullptr;
    QString currentLogin;
};
#endif // MAINWINDOW_H
