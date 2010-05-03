#-------------------------------------------------
#
# Project created by QtCreator 2010-04-12T22:08:41
#
#-------------------------------------------------

QT       += core gui

TARGET = qtagger
TEMPLATE = app

OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/tag.cpp \
    src/trackfileitem.cpp \
    src/trackmodel.cpp \
    src/qtagger.cpp \
    src/tagaudio.cpp \
    src/aboutdialog.cpp \
    src/configdialog.cpp \
    src/config.cpp

HEADERS  += src/mainwindow.h \
    src/tag.h \
    src/trackfileitem.h \
    src/trackmodel.h \
    src/qtagger.h \
    src/tagaudio.h \
    src/aboutdialog.h \
    src/configdialog.h \
    src/config.h

FORMS    += src/mainwindow.ui \
    src/aboutdialog.ui \
    src/configdialog.ui
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += taglib

    # select prefix
    isEmpty( PREFIX ):PREFIX = /usr
    else:PREFIX = $${PREFIX}
    PREFIXSTR = '\\"$${PREFIX}\\"'
    DEFINES += PREFIX=\"$${PREFIXSTR}\"
}

OTHER_FILES += \
    CMakeLists.txt \
    qtagger.rc

RESOURCES += \
    qtagger.qrc

win32 {
    RC_FILE = qtagger.rc
    INCLUDEPATH += src/common/include
    LIBS += src/common/taglib-1.6.1-bin/lib/libtag.dll.a
}
