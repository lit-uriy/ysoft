TARGET = tsreader

HEADERS += tsreader.h dbconnect.h ticket.h
SOURCES += main.cpp

DEPENDPATH += .
INCLUDEPATH += .

CONFIG += console
QT -=  gui
QT += xml sql


