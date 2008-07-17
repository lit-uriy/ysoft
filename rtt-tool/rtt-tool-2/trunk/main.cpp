#include <QCoreApplication>

#include <QTextCodec>
#include <QLibraryInfo>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStringList>
#include <QList>
#include <QPair>


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
  
  typedef QPair<QString, QString> SPair;
  
  QStringList	list;
  //SPair			pair;
  QList<SPair>	listpair;
  
  QCoreApplication app(argc, argv);
  
	// Устанавливаем кодеки
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	
	tsdir = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
	dbname = "trac.db";
	milestone = tr("Перевод TS-файлов");

	// Свяжем названия файлов с компонентами
	/*
	pair.first("linguist_ru.ts"); pair.second(tr("ts Qt Linguist"));
	listpair.append(pair);
	pair.insert("assistant_ru.ts"); pair.second(tr("ts Qt Assistant"));
	listpair.append(pair);
	pair.insert("qt_ru.ts"); pair.second(tr("ts Qt"));
	listpair.append(pair);
	*/

	listpair.append(SPair("linguist_ru.ts",tr("ts Qt Linguist")));
	listpair.append(SPair("assistant_ru.ts",tr("ts Qt Assistant")));
	listpair.append(SPair("qt_ru.ts",tr("ts Qt")));
	
	/*
	tsname = "linguist_ru.ts"; // "assistant_ru.ts" "qt_ru.ts"  
	component = tr("ts Qt Linguist"); // tr("ts Qt Assistant"); tr("ts Qt")
	*/
	foreach (SPair pair, listpair)
	{
		tsname = pair.first;
		component = pair.second;
		list.clear();
		// 
		tsfile.setFileName(tsdir.absolutePath() + "/" + tsname);
		qDebug() << "TS File: " << tsfile.fileName() << "\n\r";
		qDebug() << "Component: " << component << "\n\r";
		
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
	}
	
	qDebug() << "---------- End of Programm ----------" << "\n\r";
	return 0;
	//return app.exec();
}
