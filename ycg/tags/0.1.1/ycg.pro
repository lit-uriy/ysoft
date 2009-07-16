TEMPLATE	= app
TARGET 		= ycg


SOURCES		= main.cpp

HEADERS		+=	uireader.h \
				codegenerator.h

RESOURCES	+= ycg.qrc


#========= Dependency ==============
#		--- Qt ---
QT -= gui
QT += xml




#=========== Config ================
CONFIG 		+= debug_and_release build_all
CONFIG	    += console

DESTDIR     = ./build
OBJECTS_DIR = ./build/obj
UI_DIR      = ./build/uic
MOC_DIR     = ./build/moc
RCC_DIR		= ./build/rcc


CONFIG (debug, debug|release) {
	OBJECTS_DIR  = $$join(OBJECTS_DIR,,,d)
	TARGET       = $$join(TARGET,,,d)
}
