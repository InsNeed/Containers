#-------------------------------------------------
#
# Project created by QtCreator 2023-12-09T20:54:56
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

RC_FILE += icon_config.rc

TARGET = serverTcp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    1.txt \
    db.txt \
    icon_config.rc

RESOURCES += \
    res.qrc
