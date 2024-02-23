QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += PRECOMPILED_HEADER
PRECOMPILED_HEADER = stdafx.h

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
MOC_DIR = ./build/debug
RCC_DIR = ./build/debug
UI_DIR = ./build/debug
OBJECTS_DIR = ./build/debug
DESTDIR = ./bin/debug
}else{
MOC_DIR = ./build/release
RCC_DIR = ./build/release
UI_DIR = ./build/release
OBJECTS_DIR = ./build/release
DESTDIR = ./bin/release
}

SOURCES += \
    MainHead.cpp \
    TcpClientView.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainHead.h \
    MainWindow.h \
    TcpClientView.h

FORMS += \
    MainWindow.ui \
    TcpClientView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
