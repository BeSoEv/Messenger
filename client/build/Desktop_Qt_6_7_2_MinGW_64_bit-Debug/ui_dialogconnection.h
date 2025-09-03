/********************************************************************************
** Form generated from reading UI file 'dialogconnection.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONNECTION_H
#define UI_DIALOGCONNECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogConnection
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *ipEdit;
    QLabel *label_2;
    QLineEdit *portEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogConnection)
    {
        if (DialogConnection->objectName().isEmpty())
            DialogConnection->setObjectName("DialogConnection");
        DialogConnection->resize(400, 300);
        verticalLayout = new QVBoxLayout(DialogConnection);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(DialogConnection);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        ipEdit = new QLineEdit(DialogConnection);
        ipEdit->setObjectName("ipEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, ipEdit);

        label_2 = new QLabel(DialogConnection);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        portEdit = new QLineEdit(DialogConnection);
        portEdit->setObjectName("portEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, portEdit);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(DialogConnection);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(DialogConnection);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DialogConnection, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DialogConnection, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DialogConnection);
    } // setupUi

    void retranslateUi(QDialog *DialogConnection)
    {
        DialogConnection->setWindowTitle(QCoreApplication::translate("DialogConnection", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DialogConnection", "IP", nullptr));
        label_2->setText(QCoreApplication::translate("DialogConnection", "Port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogConnection: public Ui_DialogConnection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONNECTION_H
