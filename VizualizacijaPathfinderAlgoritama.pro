#-------------------------------------------------
#
# Project created by QtCreator 2022-06-03T11:46:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VizualizacijaPathfinderAlgoritama
TEMPLATE = app


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        sources/main.cpp \
        sources/mainwindow.cpp \
        sources/algoritmi.cpp \
        sources/popup.cpp \
        sources/qrightclickbutton.cpp

HEADERS += \
        headers/mainwindow.h \
        headers/algoritmi.h \
        headers/qrightclickbutton.h \
        headers/popup.h

FORMS += \
        forms/mainwindow.ui \
        forms/popup.ui
