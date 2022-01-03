QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = Application
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvasserializer.cpp \
    chooseword.cpp \
    main.cpp \
    mainwindow.cpp \
    canvas.cpp \
    client.cpp \
    messageparser.cpp \
    popup.cpp \
    settings.cpp \
    existingrooms.cpp \
    game.cpp

HEADERS += \
    MessageReceivedEnum.h \
    MessageType.h \
    canvas.h \
    canvasserializer.h \
    chooseword.h \
    client.h \
    mainwindow.h \
    existingrooms.h \
    game.h \
    messageparser.h \
    popup.h \
    settings.h \


FORMS += \
    chooseword.ui \
    existingrooms.ui \
    game.ui \
    mainwindow.ui \
    popup.ui \
    settings.ui



# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    CMakeLists.txt

RESOURCES += \
    guess.qrc \
    pctr2.qrc
