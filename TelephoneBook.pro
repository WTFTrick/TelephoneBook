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

HEADERS  += mainwindow.h\

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

