/********************************************************************************
** Form generated from reading UI file 'addusersgroup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDUSERSGROUP_H
#define UI_ADDUSERSGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addUsersGroup
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QPushButton *addUserBut;

    void setupUi(QDialog *addUsersGroup)
    {
        if (addUsersGroup->objectName().isEmpty())
            addUsersGroup->setObjectName("addUsersGroup");
        addUsersGroup->resize(400, 300);
        gridLayout = new QGridLayout(addUsersGroup);
        gridLayout->setObjectName("gridLayout");
        listWidget = new QListWidget(addUsersGroup);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);

        addUserBut = new QPushButton(addUsersGroup);
        addUserBut->setObjectName("addUserBut");

        gridLayout->addWidget(addUserBut, 1, 0, 1, 1);


        retranslateUi(addUsersGroup);

        QMetaObject::connectSlotsByName(addUsersGroup);
    } // setupUi

    void retranslateUi(QDialog *addUsersGroup)
    {
        addUsersGroup->setWindowTitle(QCoreApplication::translate("addUsersGroup", "Dialog", nullptr));
        addUserBut->setText(QCoreApplication::translate("addUsersGroup", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addUsersGroup: public Ui_addUsersGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDUSERSGROUP_H
