#ifndef HANDLER_H
#define HANDLER_H

#include <QString>
#include "DatabaseManager.h"
#include "OnlineManager.h"
#include <QStringList>
#include <QDateTime>
#include <WinSock2.h>

QString handleCommand(const QString &request, DatabaseManager& db, QString &currentUser, SOCKET clientSocket, OnlineManager &onlineManager);

#endif // HANDLER_H
