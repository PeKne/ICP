#-------------------------------------------------
#
# Project created by QtCreator 2018-05-03T12:13:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlockEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    editormainwindow.cpp \
    editor.cpp \
    port.cpp \
    connections.cpp \
    block.cpp

HEADERS  += mainwindow.h \
    editormainwindow.h \
    block.h \
    editor.h \
    connections.h \
    port.h

FORMS += \
    mainwindow.ui
