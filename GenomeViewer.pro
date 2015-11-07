#-------------------------------------------------
#
# Project created by QtCreator 2015-11-07T12:25:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GenomeViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    genome.cpp

HEADERS  += mainwindow.h \
    genome.h

FORMS    += mainwindow.ui
