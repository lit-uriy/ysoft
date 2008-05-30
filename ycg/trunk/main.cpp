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
/*
#define VERSION_MAJOR	0
#define VERSION_MINOR	1
#define VERSION_PATCH	0

using namespace std;

const QString _SW_VERSION =	QString::number(VERSION_MAJOR) + \
							"." + \
							QString::number(VERSION_MINOR) + \
							"." + \
							QString::number(VERSION_PATCH);					


const char * SW_VERSION = _SW_VERSION.toAscii();//.data()
*/
const char * SW_VERSION = "0.1.0";


void showHelp(const char *appName)
{
//    fprintf(stderr, "Qt User Interface Compiler version %s\n", SWVER);
//    if (error)
//        fprintf(stderr, "%s: %s\n", appName, error);

    fprintf(stderr, "Usage: %s [options] <file.ui>\n\n"
            "  -h, --help                display this help and exit\n"
            "  -v, --version             display version\n"
            "  -u <file.ui>              generate code from <file.ui>\n"
            "  -c <UIClassName>          generate code for <UIClassName>\n"
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
            //driver.option().dependencies = true;
        }/*
		else if (opt == QLatin1String("-o") || opt == QLatin1String("-output"))
		{
            ++arg;
            if (!argv[arg])
			{
                showHelp(argv[0]);
                return 1;
            }
            //driver.option().outputFile = QFile::decodeName(argv[arg]);
        }
		else if (opt == QLatin1String("-p") || opt == QLatin1String("-no-protection"))
		{
            //driver.option().headerProtection = false;
        }
		else if (opt == QLatin1String("-n") || opt == QLatin1String("-no-implicit-includes"))
		{
            //driver.option().implicitIncludes = false;
        }
		else if (opt == QLatin1String("-postfix"))
		{
            ++arg;
            if (!argv[arg])
			{
                showHelp(argv[0]);
                return 1;
            }
            //driver.option().postfix = QLatin1String(argv[arg]);
        }
		else if (opt == QLatin1String("-3"))
		{
            ++arg;
            if (!argv[arg])
			{
                showHelp(argv[0]);
                return 1;
            }
            //driver.option().uic3 = QFile::decodeName(argv[arg]);
        }
		else if (opt == QLatin1String("-tr") || opt == QLatin1String("-translate"))
		{
            ++arg;
            if (!argv[arg])
			{
                showHelp(argv[0]);
                return 1;
            }
            //driver.option().translateFunction = QLatin1String(argv[arg]);
        }
		else if (opt == QLatin1String("-g") || opt == QLatin1String("-generator"))
		{
            ++arg;
            if (!argv[arg])
			{
                showHelp(argv[0]);
                return 1;
            }
            QString name = QString::fromLocal8Bit(argv[arg]).toLower ();
            //driver.option().generator = (name == QLatin1String ("java")) ? Option::JavaGenerator : Option::CppGenerator;
        }
		else if (!fileName)
		{
            fileName = argv[arg];
        }*/
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
	

	


	
    return 0;//app.exec();
}
