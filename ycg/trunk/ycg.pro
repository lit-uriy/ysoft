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



#===================================
CONFIG (release, debug|release) {
	message(=================== BUILD FOR RELEASE ==================)
	message(EXTLIBPATH = $$EXTLIBPATH)
	message(LIBS = $$LIBS)
	message(Qt's = $$QT)
	message(CONFIG's = $$CONFIG)	
	OBJECTS_DIR = release/obj
	UI_DIR      = release/uic
	MOC_DIR     = release/moc
	RCC_DIR		= release/rcc
}

CONFIG (debug, debug|release) {
	message(=================== BUILD FOR DEBUG ====================)
	message(EXTLIBPATH = $$EXTLIBPATH)
	message(LIBS = $$LIBS)
	message(Qt's = $$QT)
	message(CONFIG's = $$CONFIG)
	OBJECTS_DIR = debug/obj
	UI_DIR      = debug/uic
	MOC_DIR     = debug/moc
	RCC_DIR		= debug/rcc	
}
