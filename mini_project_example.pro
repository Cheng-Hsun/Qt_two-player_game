#-------------------------------------------------
#
# Project created by QtCreator 2015-04-28T17:36:41
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
DESTDIR   = $$PWD
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mini_project_example
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    easymusic.cpp \
    form.cpp \
    role1.cpp \
    role2.cpp \
    weapon1.cpp \
    login.cpp \
    win.cpp \
    head.cpp

HEADERS  += mainwindow.h \
    easymusic.h \
    form.h \
    role1.h \
    role2.h \
    weapon1.h \
    login.h \
    win.h \
    head.h

RESOURCES += \
    resource.qrc

DISTFILES +=

FORMS += form.ui
