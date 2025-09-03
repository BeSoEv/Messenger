/********************************************************************************
** Form generated from reading UI file 'creategroudialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEGROUDIALOG_H
#define UI_CREATEGROUDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateGrouDialog
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *group_nameEdit;
    QLabel *label_2;
    QListWidget *userListWidget;
    QPushButton *finisGroupBut;

    void setupUi(QDialog *CreateGrouDialog)
    {
        if (CreateGrouDialog->objectName().isEmpty())
            CreateGrouDialog->setObjectName("CreateGrouDialog");
        CreateGrouDialog->resize(526, 392);
        gridLayout = new QGridLayout(CreateGrouDialog);
        gridLayout->setObjectName("gridLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(CreateGrouDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        group_nameEdit = new QLineEdit(CreateGrouDialog);
        group_nameEdit->setObjectName("group_nameEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, group_nameEdit);

        label_2 = new QLabel(CreateGrouDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        userListWidget = new QListWidget(CreateGrouDialog);
        userListWidget->setObjectName("userListWidget");

        formLayout->setWidget(1, QFormLayout::FieldRole, userListWidget);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        finisGroupBut = new QPushButton(CreateGrouDialog);
        finisGroupBut->setObjectName("finisGroupBut");

        gridLayout->addWidget(finisGroupBut, 1, 0, 1, 1);


        retranslateUi(CreateGrouDialog);

        QMetaObject::connectSlotsByName(CreateGrouDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateGrouDialog)
    {
        CreateGrouDialog->setWindowTitle(QCoreApplication::translate("CreateGrouDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CreateGrouDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        label_2->setText(QCoreApplication::translate("CreateGrouDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\203\321\207\320\260\321\201\321\202\320\275\320\270\320\272\320\276\320\262", nullptr));
        finisGroupBut->setText(QCoreApplication::translate("CreateGrouDialog", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateGrouDialog: public Ui_CreateGrouDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEGROUDIALOG_H
