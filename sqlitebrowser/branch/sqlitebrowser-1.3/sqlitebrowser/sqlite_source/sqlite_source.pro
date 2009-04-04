SOURCES	+= alter.c \
	analyze.c \
	attach.c \
	auth.c \
	btree.c \
	build.c \
	callback.c \
	complete.c \
	date.c \
	delete.c \
	experimental.c \
	expr.c \
	func.c \
	hash.c \
	insert.c \
	legacy.c \
	main.c \
	opcodes.c \
	os_unix.c \
	os_win.c \
	os.c \
	pager.c \
	parse.c \
	pragma.c \
	prepare.c \
	printf.c \
	random.c \
	select.c \
	table.c \
	tokenize.c \
	trigger.c \
	update.c \
	utf.c \
	util.c \
	vacuum.c \
	vdbe.c \
	vdbeapi.c \
	vdbeaux.c \
	vdbefifo.c \
	vdbemem.c \
	where.c
HEADERS	+= btree.h \
	config.h \
	hash.h \
	keywordhash.h \
	opcodes.h \
	os.h \
	os_common.h \
	os_unix.h \
	os_win.h \
	pager.h \
	parse.h \
	sqlite3.h \
	sqliteInt.h \
	vdbe.h \
	vdbeInt.h
unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}
mac {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
  DEFINES += HAVE_USLEEP=1
  QMAKE_CC = gcc-3.3
  QMAKE_CXX = g++-3.3
  QMAKE_LINK = $$QMAKE_CXX
}
TEMPLATE	=lib
CONFIG	+= qt warn_on release staticlib
LANGUAGE	= C
#DEFINES -= UNICODE
DEFINES += NDEBUG THREAD_SAFE=1 TEMP_STORE=2
#The following line was inserted by qt3to4
QT +=  qt3support 
