TARGET		  = qscite
TAMPLATE	  = app


HEADERS       = TextEdit.h
#HEADERS      += TextEdit.h

SOURCES       = TextEdit.cpp
#SOURCES      += TextEdit.cpp

SOURCES      += main.cpp
				
RESOURCES     = application.qrc

#	  --- External ---

USELIBDIR       = D:/libs/QScintilla-gpl-2.3
include($$USELIBDIR/qscintilla.pri)


#=========== Yura Config ================
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
message(TARGET = $$TARGET)
#=========== Yura Config ================
