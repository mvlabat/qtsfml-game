#-------------------------------------------------
#
# Project created by QtCreator 2015-05-22T19:06:00
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
        qsfmlcanvas.cpp \
    engine.cpp \
    gameobject.cpp \
    level.cpp \
    gamedata.cpp \
    gamesettings.cpp \
    gamehero.cpp \
    renderableobject.cpp \
    controls.cpp \
    fonts.cpp \
    system.cpp \
    camera.cpp

HEADERS  += qsfmlcanvas.h \
    engine.h \
    gameobject.h \
    binarysearchtree.h \
    level.h \
    gamedata.h \
    gamesettings.h \
    gamehero.h \
    renderableobject.h \
    controls.h \
    fonts.h \
    system.h \
    camera.h

LIBS += -lsfml-audio\
        -lsfml-graphics\
        -lsfml-window\
        -lsfml-network\
        -lsfml-system

DISTFILES += \
    font.ttf \
    molfar.png
