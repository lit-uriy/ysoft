# -------------------------------------------------
# Project created by QtCreator 2008-12-28T09:04:02
# -------------------------------------------------
QT += svg
CONFIG += release
#CONFIG += static
	
TARGET = Clocks
TEMPLATE = app
SOURCES += main.cpp \
    abstractclock.cpp \
    simpleclock.cpp \
    digitalclock.cpp \
    mainview.cpp \
    worldclock.cpp \
    clockmanager.cpp \
    buttonitem.cpp \
    astronomicalclock.cpp
HEADERS += mainview.h \
    clockmanager.h \
    abstractclock.h \
    buttonitem.h \
    astronomicalclock.h \
    worldclock.h \
    simpleclock.h \
    digitalclock.h
#RESOURCES = images.qrc


DESTDIR     = ./build
OBJECTS_DIR = ./build/obj
UI_DIR      = ./build/uic
MOC_DIR     = ./build/moc
RCC_DIR		= ./build/rcc


CONFIG (debug, debug|release) {
	OBJECTS_DIR  = $$join(OBJECTS_DIR,,,d)
	TARGET       = $$join(TARGET,,,d)
	CONFIG      += console
}