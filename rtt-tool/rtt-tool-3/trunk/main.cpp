/*!
 \file	main.cpp
 \brief Программа перекодировки текстовых файлов (*.h и *.cpp) из UI.
 
 Эта программа генерирует файлы исходников из файлов *.ui,
 используя множественное наследование классов.
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

//#include "uireader.h"
//#include "codegenerator.h"

const char * SW_VERSION = "0.1.0";


void showHelp(const char *appName)
{
    fprintf(stderr, "File reencodder %s\n"
			"This program reencoded text files\n\n", SW_VERSION);

    fprintf(stderr, "Usage: %s options\n\n"
            "  -h, --help                      Display this help and exit.\n"
            "  -v, --version                   Display version.\n"
			"  -s, --source=<file,codec>       Input file and codec.\n"
			"  -d, --destination=<file,codec>  Output file and codec.\n"
            "\n", appName);
}


bool argparse(int argc, char *argv[], QMap<QString,QString> &dict)
{
  int 			argcnt = 0;
  int			i = 0;
  QStringList	opts;  
  QStringList	list;
  
    for ( i = 1; i < argc; i++ )
    {
		opts += argv[ i ];
	}
	argcnt = opts.size();
	dict["EXIT"] = "no";
	
    if (argcnt < 1) // если нет аргументов
	{
		showHelp(argv[0]);
		return 1;	
	}
	else if (opts.contains("-h") || opts.contains("--help"))
	{
		showHelp(argv[0]);
		dict["EXIT"] = "yes";
		return 0;
	}
	else if (opts.contains("-v") || opts.contains("--version"))
	{
		dict["EXIT"] = "yes";
		fprintf(stderr, "File reencodder %s\n", SW_VERSION);
		return 0;
	}
	
	i = 0;
	while (i < argcnt) 
	{
		QString str = opts.at(i);
		qDebug() << "Parametr No" << i <<  "= " << opts.at(i) << "\t" ;
		
		if (str.contains("-s=")||str.contains("--source="))	// Входной файл
		{
			list.clear();
			list = str.split(QRegExp("[=,]"));
			if (list.size() < 3)
			{
				showHelp(argv[0]);
				return 1;
			}
			dict.insert("SrcFile", list.at(1));
			dict.insert("SrcCodec", list.at(2));
			qDebug() << list << "\n\r";
		}
		else if (str.contains("-d=")||str.contains("--destination="))	// Выходной файл
		{
			list.clear();
			list = str.split(QRegExp("[=,]"));
			if (list.size() < 3)
			{
				showHelp(argv[0]);
				return 1;
			}			
			dict.insert("DstFile", list.at(1));
			dict.insert("DstCodec", list.at(2));
			qDebug() << list << "\n\r";
		}
		else
		{
            showHelp(argv[0]);
            return 1;
        }
		i++;
	} 	
	return 0;
}



int main(int argc, char *argv[])
{

/*  QString		filename;
  QString		classname;
  QString		parentname;
  QString		opt;*/
  QFileInfo		fi;
  QMap<QString,QString> dict;  
  

	
	if (argparse(argc, argv, dict) || (dict["EXIT"] == "yes"))
	{
		return 1;
	}
	
	QCoreApplication app(argc, argv);
    
	// Проверим введенные параметры
	if (!(dict.contains("SrcFile") && dict.contains("DstFile")))// все ли данные введены
		return 1;
	
	fi.setFile(dict["SrcFile"]);
	if (fi.isFile())
	{
		qDebug() << dict["SrcFile"] << " - is file" << "\n\r";
	}
	else if (fi.isDir())
	{
		qDebug() << dict["SrcFile"] << " - is dir" << "\n\r";
	}
	else
	{
		qDebug() << dict["SrcFile"] << " - is not file or dir" << "\n\r";
		return 1;
	}
	
	fi.setFile(dict["DstFile"]);
	if (fi.isFile())
	{
		qDebug() << dict["DstFile"] << " - is file" << "\n\r";
	}
	else if (fi.isDir())
	{
		qDebug() << dict["DstFile"] << " - is dir" << "\n\r";
	}
	else
	{
		qDebug() << dict["DstFile"] << " - is not file or dir" << "\n\r";
		return 1;
	}	

/*
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
