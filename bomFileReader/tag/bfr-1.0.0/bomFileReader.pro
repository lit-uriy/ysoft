TARGET = bfr
TEMPLATE = app

#  -- Debug/release build --
CONFIG += debug_and_release build_all




#=========== Files =================
HEADERS       += mainwindow.h \
				bomparser.h \
				dbhandle.h


SOURCES       += mainwindow.cpp \
				bomparser.cpp \
				dbhandle.cpp

SOURCES       += main.cpp

#RESOURCES     = mdi.qrc

FORMS		+=	mainwindow.ui
			

#========= Dependency ==============
#	--- Qt ---
QT += sql

#	--- External ---


#======== Translation ===============
#TRANSLATIONS	= app_ru.ts

#=========== Config ================


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



