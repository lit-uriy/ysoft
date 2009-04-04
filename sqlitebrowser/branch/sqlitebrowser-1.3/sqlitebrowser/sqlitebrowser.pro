QT += qt3support

TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

HEADERS	+= sqlitebrowsertypes.h \
	sqlitedb.h \
	sqlbrowser_util.h

SOURCES	+= browsermain.cpp \
	sqlitedb.cpp \
	sqlbrowser_util.c

#The following line was changed from FORMS to FORMS3 by qt3to4
FORMS3	= aboutform.ui \
	addfieldform.ui \
	addfieldtypeform.ui \
	choosetableform.ui \
	createindexform.ui \
	createtableform.ui \
	deleteindexform.ui \
	deletetableform.ui \
	editfieldform.ui \
	editform.ui \
	edittableform.ui \
	exporttablecsvform.ui \
	findform.ui \
	form1.ui \
	importcsvform.ui \
	renametableform.ui \
	sqllogform.ui

IMAGES	= images/create_index.png \
	images/create_table.png \
	images/delete_index.png \
	images/delete_table.png \
	images/icone16.png \
	images/log.png \
	images/modify_table.png \
	images/new.png \
	images/open.png \
	images/revert.png \
	images/save.png \
	images/searchfind.png \
	images/whatis.png

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  LIBS += ./sqlite_source/libsqlite_source.a
}
win32 {
  RC_FILE = winapp.rc
  #For MingW
  LIBS	+= sqlite_source/release/libsqlite_source.a
  #For MSVC
  #LIBS	+= sqlite_source/release/sqlite_source.lib
}
mac {
  RC_FILE = macapp.icns
  LIBS	+= -framework Carbon ./sqlite_source/libsqlite_source.a
  QMAKE_INFO_PLIST = app.plist
}


#The following line was inserted by qt3to4
QT +=  
#The following line was inserted by qt3to4
CONFIG += uic3

