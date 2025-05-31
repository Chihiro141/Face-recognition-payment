#-------------------------------------------------
#
# Project created by QtCreator 2024-12-11T22:11:36
#
#-------------------------------------------------

QT       += core gui
QT       += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shibiepay
TEMPLATE = app
INCLUDEPATH += D:\opencv\opencv3.4-install\install\include
INCLUDEPATH += D:\opencv\opencv3.4-install\install\include\opencv
INCLUDEPATH += D:\opencv\opencv3.4-install\install\include\opencv2
LIBS += D:/opencv/opencv3.4-install/install/x86/mingw/lib/libopencv_*.a


SOURCES += main.cpp\
        mainwindow.cpp \
    zhuce.cpp \
    jiezhang.cpp \
    userdao.cpp \
    shibie.cpp \
    moneydata.cpp \
    chaxun.cpp

HEADERS  += mainwindow.h \
    zhuce.h \
    jiezhang.h \
    userdao.h \
    shibie.h \
    moneydata.h \
    chaxun.h

FORMS    += mainwindow.ui \
    zhuce.ui \
    jiezhang.ui \
    shibiejiesuan.ui \
    shibie.ui \
    chaxun.ui
CONFIG += c++11

RESOURCES += \
    image.qrc
