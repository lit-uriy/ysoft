TARGET		  = yscitew
TAMPLATE	  = app


HEADERS       = yscitew.h \
				mainwindow.h

SOURCES       = yscitew.cpp \
				mainwindow.cpp

SOURCES      += main.cpp
				
RESOURCES     = application.qrc

#	  --- External ---

USELIBDIR       = D:/libs/QScintilla-gpl-2.3p1_static/QScintilla
include($$USELIBDIR/qscintilla.pri)


#=========== Yura Config ================
#CONFIG += debug_and_release build_all
CONFIG  	+= release

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
message(TARGET = $$TARGET)
#=========== Yura Config ================
