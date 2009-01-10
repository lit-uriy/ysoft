
TEMPLATE = app
TARGET = tst



# Input
#HEADERS += class.h
#SOURCES += class.cpp
SOURCES += main.cpp

#========= Dependency ==============
#		--- Qt ---
QT -= gui
#QT += xml

#=========== Config ================
CONFIG += debug_and_release build_all

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