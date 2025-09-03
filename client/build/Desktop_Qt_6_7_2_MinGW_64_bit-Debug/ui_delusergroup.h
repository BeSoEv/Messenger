/********************************************************************************
** Form generated from reading UI file 'delusergroup.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELUSERGROUP_H
#define UI_DELUSERGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_delusergroup
{
public:
    QGridLayout *gridLayout;
    QPushButton *deluserBut;
    QListWidget *listWidget;

    void setupUi(QDialog *delusergroup)
    {
        if (delusergroup->objectName().isEmpty())
            delusergroup->setObjectName("delusergroup");
        delusergroup->resize(400, 300);
        gridLayout = new QGridLayout(delusergroup);
        gridLayout->setObjectName("gridLayout");
        deluserBut = new QPushButton(delusergroup);
        deluserBut->setObjectName("deluserBut");

        gridLayout->addWidget(deluserBut, 1, 0, 1, 1);

        listWidget = new QListWidget(delusergroup);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);


        retranslateUi(delusergroup);

        QMetaObject::connectSlotsByName(delusergroup);
    } // setupUi

    void retranslateUi(QDialog *delusergroup)
    {
        delusergroup->setWindowTitle(QCoreApplication::translate("delusergroup", "Dialog", nullptr));
        deluserBut->setText(QCoreApplication::translate("delusergroup", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class delusergroup: public Ui_delusergroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELUSERGROUP_H
