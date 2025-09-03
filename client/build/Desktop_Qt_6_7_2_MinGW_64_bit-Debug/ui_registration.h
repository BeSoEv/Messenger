/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label_8;
    QLineEdit *name1;
    QLabel *label_9;
    QLineEdit *name2;
    QLabel *label_10;
    QLineEdit *name3;
    QLabel *label_11;
    QLineEdit *loginReg;
    QLabel *label_12;
    QLineEdit *passReg;
    QLabel *label_13;
    QLineEdit *pass2Reg;
    QPushButton *finishRegButton;

    void setupUi(QWidget *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName("Registration");
        Registration->resize(812, 544);
        widget = new QWidget(Registration);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(50, 30, 731, 441));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_8);

        name1 = new QLineEdit(widget);
        name1->setObjectName("name1");

        formLayout->setWidget(0, QFormLayout::FieldRole, name1);

        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_9);

        name2 = new QLineEdit(widget);
        name2->setObjectName("name2");

        formLayout->setWidget(1, QFormLayout::FieldRole, name2);

        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_10);

        name3 = new QLineEdit(widget);
        name3->setObjectName("name3");

        formLayout->setWidget(2, QFormLayout::FieldRole, name3);

        label_11 = new QLabel(widget);
        label_11->setObjectName("label_11");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_11);

        loginReg = new QLineEdit(widget);
        loginReg->setObjectName("loginReg");

        formLayout->setWidget(3, QFormLayout::FieldRole, loginReg);

        label_12 = new QLabel(widget);
        label_12->setObjectName("label_12");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_12);

        passReg = new QLineEdit(widget);
        passReg->setObjectName("passReg");
        passReg->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(4, QFormLayout::FieldRole, passReg);

        label_13 = new QLabel(widget);
        label_13->setObjectName("label_13");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_13);

        pass2Reg = new QLineEdit(widget);
        pass2Reg->setObjectName("pass2Reg");
        pass2Reg->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(5, QFormLayout::FieldRole, pass2Reg);

        finishRegButton = new QPushButton(widget);
        finishRegButton->setObjectName("finishRegButton");

        formLayout->setWidget(6, QFormLayout::SpanningRole, finishRegButton);


        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QWidget *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Form", nullptr));
        label_8->setText(QCoreApplication::translate("Registration", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217", nullptr));
        label_9->setText(QCoreApplication::translate("Registration", "\320\230\320\274\321\217", nullptr));
        label_10->setText(QCoreApplication::translate("Registration", "\320\236\321\202\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        label_11->setText(QCoreApplication::translate("Registration", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        label_12->setText(QCoreApplication::translate("Registration", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        label_13->setText(QCoreApplication::translate("Registration", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\320\265 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        finishRegButton->setText(QCoreApplication::translate("Registration", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
