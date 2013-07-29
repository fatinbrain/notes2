#-------------------------------------------------
#
# Project created by QtCreator 2013-07-29T08:34:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = notes2
TEMPLATE = app


SOURCES += main.cpp\
        notes2.cpp \
    noterecord.cpp \
    notesbase.cpp \
    newnotedialog.cpp

HEADERS  += notes2.h \
    noterecord.h \
    notesbase.h \
    newnotedialog.h

FORMS    += notes2.ui \
    newnotedialog.ui

RESOURCES += \
    notes2.qrc
