#-------------------------------------------------
#
# Project created by QtCreator 2016-07-24T08:37:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtExperiment
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spritesheetmodel.cpp \
    spritesheetscene.cpp \
    boxattributewidget.cpp \
    boxlistwidget.cpp \
    animationdrawerwidget.cpp

HEADERS  += mainwindow.h \
    spritesheetmodel.h \
    spritesheetscene.h \
    boxattributewidget.h \
    boxlistwidget.h \
    animationdrawerwidget.h

FORMS    += mainwindow.ui
