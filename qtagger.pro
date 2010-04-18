#-------------------------------------------------
#
# Project created by QtCreator 2010-04-12T22:08:41
#
#-------------------------------------------------

QT       += core gui

TARGET = qtagger
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/tag.cpp \
    src/trackfileitem.cpp \
    src/trackmodel.cpp \
    src/qtagger.cpp \
    src/tagaudio.cpp \
    src/aboutdialog.cpp

HEADERS  += src/mainwindow.h \
    src/tag.h \
    src/trackfileitem.h \
    src/trackmodel.h \
    src/qtagger.h \
    src/tagaudio.h \
    src/aboutdialog.h

FORMS    += src/mainwindow.ui \
    src/aboutdialog.ui

CONFIG += link_pkgconfig
PKGCONFIG += taglib
