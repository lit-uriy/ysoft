/*!
 \file	main.cpp
 \brief Программа генерации исходников (*.h и *.cpp) из UI.
 
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

#include "uireader.h"
#include "codegenerator.h"

const char * SW_VERSION = "0.1.0";


void showHelp(const char *appName)
{
    fprintf(stderr, "Yurik's Code Generator %s\n", SW_VERSION);

    fprintf(stderr, "Usage: %s [options] <file.ui>\n\n"
            "  -h, --help                display this help and exit\n"
            "  -v, --version             display version\n"
            "\n", appName);
}

int main(int argc, char *argv[])
{
  int arg = 1;
  QString	filename;
  QString	classname;
  QString	parentname;
  
	while (arg < argc) 
	{
        QString opt = QString::fromLocal8Bit(argv[arg]);
		QRegExp rx("*.ui");
		rx.setPatternSyntax(QRegExp::Wildcard);
		
        if (opt == QLatin1String("-h") || opt == QLatin1String("--help"))
		{
            showHelp(argv[0]);
            return 0;
        }
		else if (opt == QLatin1String("-v") || opt == QLatin1String("--version"))
		{
			
            fprintf(stderr, "Yurik's Code Generator %s\n", SW_VERSION);
            return 0;
        }
		else if (rx.exactMatch(opt))
		{
			qDebug() << "Parametr : " << opt << "\n\r";
			filename = opt;
			break;
        }
		else
		{
            showHelp(argv[0]);
            return 1;
        }
        ++arg;		
	} 

  QCoreApplication app(argc, argv);

	if (!GetClassName(filename, classname, parentname))
	{
		qDebug() << "Error in GetClassName";
		return 1;
	}
	
	GenerateCode(filename, classname, parentname);

	


	
    return 0;
}
