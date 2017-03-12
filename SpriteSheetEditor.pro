#-------------------------------------------------
#
# Project created by QtCreator 2016-07-24T08:37:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteSheetEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spritesheetmodel.cpp \
    spritesheetscene.cpp \
    boxattributewidget.cpp \
    animationdrawerwidget.cpp \
    animationdrawerwindow.cpp

HEADERS  += mainwindow.h \
    spritesheetmodel.h \
    spritesheetscene.h \
    boxattributewidget.h \
    animationdrawerwidget.h \
    animationdrawerwindow.h \
    SpriteSheet.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/3rdParty/boost_1_61_0/stage/x64/ -llibboost_serialization-vc140-mt-1_61
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/3rdParty/boost_1_61_0/stage/x64/ -llibboost_serialization-vc140-mt-gd-1_61

INCLUDEPATH += $$PWD/3rdParty/boost_1_61_0
DEPENDPATH += $$PWD/3rdParty/boost_1_61_0

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/3rdParty/boost_1_61_0/stage/x64/liblibboost_serialization-vc140-mt-1_61.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/3rdParty/boost_1_61_0/stage/x64/libboost_serialization-vc140-mt-gd-1_61.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/3rdParty/boost_1_61_0/stage/x64/libboost_serialization-vc140-mt-1_61.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/3rdParty/boost_1_61_0/stage/x64/libboost_serialization-vc140-mt-gd-1_61.lib
