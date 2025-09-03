/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QListView *usersEdit;
    QLabel *label;
    QWidget *layoutWidget1;
    QFormLayout *formLayout_2;
    QListView *groupsEdit;
    QLabel *label_3;
    QPushButton *createGroupBut;
    QWidget *chatContainer;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QStackedWidget *stackedWidget;
    QWidget *persChatBox;
    QGridLayout *gridLayout_2;
    QTextBrowser *persChatEdit;
    QWidget *groupChatBox;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *chat;
    QGridLayout *gridLayout_5;
    QTextBrowser *groupChatEdit;
    QWidget *participants;
    QGridLayout *gridLayout_4;
    QListView *groupUsers;
    QPushButton *addParticipBut;
    QPushButton *delParticip;
    QWidget *settings;
    QGridLayout *gridLayout_6;
    QPushButton *delGroupButton;
    QSpacerItem *verticalSpacer;
    QSplitter *splitter_3;
    QTextEdit *messageEdit;
    QPushButton *sendButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName("ChatWindow");
        ChatWindow->resize(800, 600);
        centralwidget = new QWidget(ChatWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName("layoutWidget");
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        usersEdit = new QListView(layoutWidget);
        usersEdit->setObjectName("usersEdit");
        usersEdit->setEnabled(true);

        formLayout->setWidget(1, QFormLayout::SpanningRole, usersEdit);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::SpanningRole, label);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName("layoutWidget1");
        formLayout_2 = new QFormLayout(layoutWidget1);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setHorizontalSpacing(7);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        groupsEdit = new QListView(layoutWidget1);
        groupsEdit->setObjectName("groupsEdit");

        formLayout_2->setWidget(1, QFormLayout::SpanningRole, groupsEdit);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");
        label_3->setLineWidth(1);

        formLayout_2->setWidget(0, QFormLayout::SpanningRole, label_3);

        createGroupBut = new QPushButton(layoutWidget1);
        createGroupBut->setObjectName("createGroupBut");

        formLayout_2->setWidget(2, QFormLayout::SpanningRole, createGroupBut);

        splitter->addWidget(layoutWidget1);
        chatContainer = new QWidget(splitter);
        chatContainer->setObjectName("chatContainer");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chatContainer->sizePolicy().hasHeightForWidth());
        chatContainer->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(chatContainer);
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 0, -1, -1);
        label_4 = new QLabel(chatContainer);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        stackedWidget = new QStackedWidget(chatContainer);
        stackedWidget->setObjectName("stackedWidget");
        persChatBox = new QWidget();
        persChatBox->setObjectName("persChatBox");
        gridLayout_2 = new QGridLayout(persChatBox);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setHorizontalSpacing(7);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        persChatEdit = new QTextBrowser(persChatBox);
        persChatEdit->setObjectName("persChatEdit");

        gridLayout_2->addWidget(persChatEdit, 0, 0, 1, 1);

        stackedWidget->addWidget(persChatBox);
        groupChatBox = new QWidget();
        groupChatBox->setObjectName("groupChatBox");
        gridLayout_3 = new QGridLayout(groupChatBox);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(groupChatBox);
        tabWidget->setObjectName("tabWidget");
        chat = new QWidget();
        chat->setObjectName("chat");
        gridLayout_5 = new QGridLayout(chat);
        gridLayout_5->setObjectName("gridLayout_5");
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        groupChatEdit = new QTextBrowser(chat);
        groupChatEdit->setObjectName("groupChatEdit");

        gridLayout_5->addWidget(groupChatEdit, 0, 0, 1, 1);

        tabWidget->addTab(chat, QString());
        participants = new QWidget();
        participants->setObjectName("participants");
        gridLayout_4 = new QGridLayout(participants);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        groupUsers = new QListView(participants);
        groupUsers->setObjectName("groupUsers");

        gridLayout_4->addWidget(groupUsers, 0, 0, 1, 1);

        addParticipBut = new QPushButton(participants);
        addParticipBut->setObjectName("addParticipBut");

        gridLayout_4->addWidget(addParticipBut, 1, 0, 1, 1);

        delParticip = new QPushButton(participants);
        delParticip->setObjectName("delParticip");

        gridLayout_4->addWidget(delParticip, 2, 0, 1, 1);

        tabWidget->addTab(participants, QString());
        settings = new QWidget();
        settings->setObjectName("settings");
        gridLayout_6 = new QGridLayout(settings);
        gridLayout_6->setObjectName("gridLayout_6");
        delGroupButton = new QPushButton(settings);
        delGroupButton->setObjectName("delGroupButton");

        gridLayout_6->addWidget(delGroupButton, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 1, 0, 1, 1);

        tabWidget->addTab(settings, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);

        stackedWidget->addWidget(groupChatBox);

        verticalLayout_2->addWidget(stackedWidget);

        splitter_3 = new QSplitter(chatContainer);
        splitter_3->setObjectName("splitter_3");
        splitter_3->setOrientation(Qt::Orientation::Horizontal);
        messageEdit = new QTextEdit(splitter_3);
        messageEdit->setObjectName("messageEdit");
        splitter_3->addWidget(messageEdit);
        sendButton = new QPushButton(splitter_3);
        sendButton->setObjectName("sendButton");
        splitter_3->addWidget(sendButton);

        verticalLayout_2->addWidget(splitter_3);

        verticalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(verticalLayout_2);

        splitter->addWidget(chatContainer);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        ChatWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ChatWindow);
        statusbar->setObjectName("statusbar");
        ChatWindow->setStatusBar(statusbar);

        retranslateUi(ChatWindow);

        stackedWidget->setCurrentIndex(1);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("ChatWindow", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\270", nullptr));
        label_3->setText(QCoreApplication::translate("ChatWindow", "\320\223\321\200\321\203\320\277\320\277\321\213", nullptr));
        createGroupBut->setText(QCoreApplication::translate("ChatWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        label_4->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(chat), QCoreApplication::translate("ChatWindow", "Tab 1", nullptr));
        addParticipBut->setText(QCoreApplication::translate("ChatWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        delParticip->setText(QCoreApplication::translate("ChatWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(participants), QCoreApplication::translate("ChatWindow", "Tab 2", nullptr));
        delGroupButton->setText(QCoreApplication::translate("ChatWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\263\321\200\321\203\320\277\320\277\321\203", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(settings), QCoreApplication::translate("ChatWindow", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatWindow", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
