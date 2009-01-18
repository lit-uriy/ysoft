/*!
 *	\file	bomparser.cpp
 *	\brief	Реализация класса "BomParser".
 */

#include <QtGui>

#include "bomparser.h"


BomParser::BomParser(QString f_name):file_name(f_name)
{
	
	//qDebug() << QFileInfo(f).completeBaseName();
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
	
	ok = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (!ok)
	{
		qDebug() << "Error open file";
		return;
	}
	
	incodec = QTextCodec::codecForLocale();
	in.setCodec(incodec);
	
	qDebug() << "====================== BOM ======================";
	while (!in.atEnd())
	{
		QString line = in.readLine();
		processLine(line);
	}	
	/**/
}

void BomParser::processLine(QString line)
{
  QStringList	lst;
  QTextStream	out(stdout);

	lst = line.split(delimiter);
	out << "line: |";
	foreach(QString str, lst)
	{
		out << "\t" << str << "\t|";
	}
	out << endl;

}
