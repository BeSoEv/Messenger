QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
LIBS += -lws2_32
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addusersgroup.cpp \
    chatwindow.cpp \
    creategroudialog.cpp \
    delusergroup.cpp \
    dialogconnection.cpp \
    main.cpp \
    mainwindow.cpp \
    registration.cpp \
    socketmanager.cpp

HEADERS += \
    addusersgroup.h \
    chatwindow.h \
    creategroudialog.h \
    delusergroup.h \
    dialogconnection.h \
    mainwindow.h \
    registration.h \
    socketmanager.h

FORMS += \
    addusersgroup.ui \
    chatwindow.ui \
    creategroudialog.ui \
    delusergroup.ui \
    dialogconnection.ui \
    mainwindow.ui \
    registration.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
