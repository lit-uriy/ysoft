TARGET = recod

HEADERS += app.h 
SOURCES += main.cpp app.cpp

DEPENDPATH += .
INCLUDEPATH += .

CONFIG += console
QT -=  gui
#QT += xml sql


# Make version
# SVNVERSION = $$system(svn info -r HEAD . | grep 'Changed\ Rev' | cut -b 19-)

 message($$system(svn info -r HEAD . ))

# message($$system(svn info -r HEAD . | grep 'Changed\ Rev' | cut -b 19-))
# !isEmpty(VERSION){
# VERSION = 0.1.$${VERSION}
# message($${VERSION})
# }


VERSION = 0.1.25

VERSTR = '\\"$${VERSION}\\"'  # place quotes around the version string
DEFINES += SW_VERSION=\"$${VERSTR}\" # create a VER macro containing the version string


