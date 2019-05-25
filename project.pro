#-------------------------------------------------
#
# Project created by QtCreator 2019-05-23T14:54:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp\
        sender.cpp\
        reciver.cpp

HEADERS  += dialog.h\
            sender.h\
            reciver.h

FORMS    += dialog.ui

CONFIG += c++11 strict_c++
