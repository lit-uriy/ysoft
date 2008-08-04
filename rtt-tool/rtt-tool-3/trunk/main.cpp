/*!
 \file	main.cpp
 \brief Программа перекодировки текстовых файлов.
 
 Эта программа перекодирует текстовые файлы.
 */
#include <QCoreApplication>
#include <QDebug>
#include <QStringList>
//#include <QRegExp>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QTextCodec>
#include <iostream>

#include "app.h"
//#include "codegenerator.h"





int main(int argc, char *argv[])
{
	
	App app(argc, argv);
	
	app.ParseCmdLine();
	
	if (!app.IsGoodArgs())
	{
		return 1;
	}
	
	if(app.IsReqInfo())
	{
		return 0;
	}
/*	
	// Проверим введенные параметры
	if (!(dict.contains("SrcName") && dict.contains("DstName")))// все ли данные введены ?
		return 1;
	
	fi.setFile(dict["SrcName"]);
	if (fi.isFile())
	{
		qDebug() << dict["SrcName"] << " - is file" << "\n\r";
		dict.insert("SrcType", "file");
	}
	else if (fi.isDir())
	{
		qDebug() << dict["SrcName"] << " - is dir" << "\n\r";
		dict.insert("SrcType", "dir");
	}
	else
	{
		qDebug() << dict["SrcName"] << " - is not file or dir" << "\n\r";
		return 1;
	}
	
	fi.setFile(dict["DstName"]);
	if (fi.isFile())
	{
		qDebug() << dict["DstName"] << " - is file" << "\n\r";
		dict.insert("DstType", "dir");
	}
	else if (fi.isDir())
	{
		qDebug() << dict["DstName"] << " - is dir" << "\n\r";
		dict.insert("DstType", "dir");
	}
	else
	{
		qDebug() << dict["DstName"] << " - is not file or dir" << "\n\r";
		return 1;
	}	


	if (!GetClassName(filename, classname, parentname))
	{
		qDebug() << "Error in GetClassName";
		return 1;
	}
	
	if(!GenerateCode(filename, classname, parentname))
	{
		qDebug() << "Error in GenerateCode";
		return 1;
	}
*/	
    return 0;
}
