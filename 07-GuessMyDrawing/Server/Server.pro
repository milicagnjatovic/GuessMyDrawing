QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TARGET = Server
TEMPLATE = app

SOURCES += \
    main.cpp \
    server.cpp \
    room.cpp \
    servermainwindow.cpp\
    servermessageparser.cpp \
    thread.cpp

HEADERS += \
    ServerMessageEnum.h \
    server.h \
    room.h \
    servermainwindow.h \
    servermessageparser.h \
    thread.h

FORMS += \
    servermainwindow.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CMakeLists.txt
