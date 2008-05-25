#include <QCoreApplication>

#include <QTextCodec>
#include <QLibraryInfo>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStringList>



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
  QString	component;
  QString	milestone;
  QString	dbname;
  bool		ok;
  QStringList list;
  QCoreApplication app(argc, argv);
  
	// Устанавливаем кодеки
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	
	dbname = "trac.db";
	tsname = "linguist_ru.ts"; // "assistant_ru.ts" "qt_ru.ts"  
	component = tr("ts Qt Linguist"); // tr("ts Qt Assistant"); tr("ts Qt") 
	milestone = tr("Перевод TS-файлов");
	
	tsdir = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
	tsfile.setFileName(tsdir.absolutePath() + "/" + tsname);
	qDebug() << "TS File: " << tsfile.fileName() << "\n\r";
	
    tsfile.open( QIODevice::ReadOnly);
	// Читаем список секций из ts-файла
	qDebug() << "---------- Read sections from *.ts ----------" << "\n\r";
    ok = GetListFrom(&tsfile, list);
	tsfile.close();
	if (!ok)
		return 1;

	// Открываем БД
	qDebug() << "---------- Open Db ----------" << "\n\r";
	ok = OpenDb(dbname);
	if (!ok)
		return 1;

	// Создаем тикеты
	qDebug() << "---------- Create tickets ----------" << "\n\r";
	ok = CreateTickets(list, component, milestone, tsname);
	if (!ok)
		return 1;	
	
	qDebug() << "---------- End of Programm ----------" << "\n\r";
	//return 0;
	return app.exec();
}
