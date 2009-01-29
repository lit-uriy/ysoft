/*!
 *	\file	bomparser.cpp
 *	\brief	Реализация класса "BomParser".
 */

#include <QtGui>

#include "bomparser.h"
#include "dbhandle.h"


BomParser::BomParser(QString f_name):file_name(f_name)
{

}


void BomParser::setDelimiter(QString delim)
{
	delimiter = delim;
}


void BomParser::parse()
{
  bool			ok;
  QFile 		file(file_name);
  QTextStream	in(&file);
  QTextCodec 	*incodec;
  QFileInfo 	fi;
  QString		dbname;
  QString		path;
  
	
	ok = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (!ok)
	{
		qDebug() << "Error open file";
		return;
	}
//-----------------
	
	// Проверим наличие файла БД
	fi.setFile(file_name);
	path = fi.path();
		qDebug() << "BomParser::Path" << path;
	dbname = path +  QDir::separator()  + fi.completeBaseName() + ".db"; // Имя файла БД
		qDebug() << "BomParser::DB name" << dbname;	
	fi.setFile(dbname);
	if (fi.exists())
	{
		QMessageBox::critical(0, QObject::tr("Ошибка"),
								 QObject::tr("Файл БД %1,\nуже существует"));
		return;
		
	}

	// Создаем БД и соеденяемся с ней
	db = new DbHanle(dbname);
	if (!db->isOpen())
	{
		QMessageBox::critical(0, QObject::tr("Ошибка"),
								 QObject::tr("Невозможно открыть БД"));
	}  

//-----------------
	nol = 0;
	find_first = true;
	
	incodec = QTextCodec::codecForLocale();
	in.setCodec(incodec);
	
	qDebug() << "====================== BOM ======================";
	while (!in.atEnd())
	{
		QString line = in.readLine();
		++nol;
		processLine(line);
	}	

}


void BomParser::processLine(QString line)
{
  QStringList	lst;
  QTextStream	out(stdout);

	out << "line: |";
	if (line.isEmpty())
	{
		out << endl;
		return;
	}
	
	lst = line.split(delimiter);
	if (find_first)
	{
		find_first = false;
		db->createTable(lst);
	}
	else
	{
		db->insert(lst);
	}
	
	foreach(QString str, lst)
	{
		out << "\t" << str << "\t|";
	}
	out << endl;

}
