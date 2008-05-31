TEMPLATE	= app
QT		+= xml
CONFIG		+= console

SOURCES		= main.cpp

#SOURCES		+= domparser.cpp
HEADERS		+=	uireader.h \
				codegenerator.h

RESOURCES += ycg.qrc
