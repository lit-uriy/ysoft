#include <QLibraryInfo>

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStringList>

#include <iostream>



#include "tsreader.h"
#include "dbconnect.h"
#include "ticket.h"



//=====================================================
//		Тело программы
//=====================================================
int main(int argc, char *argv[])
{
  QDir		tsdir;
  QFile 	tsfile;
  QString	tsname;
  bool		ok;
  QStringList list;
  
	
	tsname = "assistant_ru.ts"; // linguist_ru.ts qt_ru.ts
	tsdir = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
	tsfile.setFileName(tsdir.absolutePath() + "/" + tsname);
	qDebug() << "TS File: " << tsfile.fileName() << "\n\r";
	
    tsfile.open( QIODevice::ReadOnly);
	// Читаем список секций из ts-файла
    ok = GetListFrom(&tsfile, list);
	tsfile.close();
	if (!ok)
		return 1;
	
	ok = OpenDb();
	if (!ok)
		return 1;
	
	ok = CreateTickets(list, tr("Qt Designer"), tr("Перевод TS-файлов"), tsname);
	if (!ok)
		return 1;	

	return 0;
}
