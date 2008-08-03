/*!
 *	\file	App.cpp
 *	\brief	Реализация класса консольного приложения.
 */
#include "app.h"



#include <QDate>
#include <qdir.h>
#include <qtemporaryfile.h>
#include <qstack.h>
#include <qdebug.h>
#include <qfileinfo.h>
#include <qtextstream.h>
#include <qregexp.h>
#include <qhash.h>

App::Configure( int& argc, char** argv )
{
	dict["CONFIGCMD"] = argv[ 0 ];

	for ( i = 1; i < argc; i++ )
		opts += argv[ i ];
}

App::~Configure()
{
}


/*

 */
void App::parseCmdLine()
{
	int argcnt = opts.size();
	int i = 0;
	
	dict["EXIT"] = "no";
	
    if (argcnt < 1) // если нет аргументов
	{
		dict["HELP"] = "yes";
		dict["EXIT"] = "error";
		return;
	}
	else if (opts.contains("-h") || opts.contains("--help"))
	{
		dict["HELP"] = "yes";
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
		
		if (str.contains("-s") || str.contains("--source"))	// Входной файл
		{
			list.clear();
			list = str.split(QRegExp("[=,]"));
			if (list.size() < 3)
			{
				showHelp(argv[0]);
				return 1;
			}
			dict.insert("SrcName", list.at(1));
			dict.insert("SrcCodec", list.at(2));
			qDebug() << list << "\n\r";
		}
		else if (str.contains("-d") || str.contains("--destination"))	// Выходной файл
		{
			list.clear();
			list = str.split(QRegExp("[=,]"));
			if (list.size() < 3)
			{
				showHelp(argv[0]);
				return 1;
			}			
			dict.insert("DstName", list.at(1));
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
}


void App::validateArgs()
{
	QStringList configs;
	// Validate the specified config

	allConfigs = QStringList() << "minimal" << "small" <<  "medium" << "large" << "full";

	QStringList::Iterator config;
	for ( config = allConfigs.begin(); config != allConfigs.end(); ++config )
	{
		configs += (*config) + "-config";
		if ( (*config) == dictionary[ "QCONFIG" ] )
			break;
	}
	if ( config == allConfigs.end() )
	{
		dictionary[ "HELP" ] = "yes";
		cout << "No such configuration \"" << qPrintable(dictionary[ "QCONFIG" ]) << "\"" << endl ;
	}
	else
		qmakeConfig += configs;
}


bool App::displayHelp()
{
	if ( dictionary[ "HELP" ] == "yes" )
	{
		fprintf(stderr, "File reencodder %s\n"
						"This program reencoded text files\n\n", SW_VERSION);
		
		fprintf(stderr, "Usage: %s options\n\n"
						"  -h, --help                      Display this help and exit.\n"
						"  -v, --version                   Display version.\n"
						"  -s, --source=<file,codec>       Input file and codec.\n"
						"  -d, --destination=<file,codec>  Output file and codec.\n"
						"\n", appName);
		
		return true;
	}
	return false;
}



bool App::isDone()
{
	return !dictionary["DONE"].isEmpty();
}

bool App::isOk()
{
	return (dictionary[ "DONE" ] != "error");
}

