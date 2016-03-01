#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T19:56:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4):
QT += widgets
QT+= network

TARGET = TelephoneBook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        json.cpp

HEADERS  += mainwindow.h\
            json.h

FORMS    += mainwindow.ui

LIBS    += -lqjson

CONFIG += mobility
MOBILITY = 

