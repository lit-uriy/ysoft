/*!
 *	\file	App.cpp
 *	\brief	Реализация класса консольного приложения.
 */
#include "app.h"



#include <QtCore>



App::App( int& argc, char** argv )
{
  int i;

	dict["CMD"] = argv[ 0 ];

	for ( i = 1; i < argc; i++ )
		opts += argv[ i ];
}

//----------------------------------------------------------------------------------
App::~App()
{
}


//----------------------------------------------------------------------------------
void App::ParseCmdLine()
{
  int 			argcnt = opts.size();
  int 			i = 0;
  QStringList	list;
	
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
		return;
	}
	else if (opts.contains("-v") || opts.contains("--version"))
	{
		dict["HELP"] = "no";
		dict["EXIT"] = "yes";
		return;
	}
	
	// Проверяем остальные аргументы
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
				dict["EXIT"] = "error";
				fprintf(stderr, "Too few args\n");
				return;
			}
			dict["SrcName"] = list.at(1);
			dict["SrcCodec"] = list.at(2);
			qDebug() << list << "\n\r";
		}
		else if (str.contains("-d") || str.contains("--destination"))	// Выходной файл
		{
			list.clear();
			list = str.split(QRegExp("[=,]"));
			if (list.size() < 3)
			{
				dict["EXIT"] = "error";
				fprintf(stderr, "Too few args\n");
				return;
			}			
			dict["DstName"] = list.at(1);
			dict["DstCodec"] = list.at(2);
			qDebug() << list << "\n\r";
		}
		else
		{
			dict["EXIT"] = "error";
			fprintf(stderr, "Unknown args\n");
			return;
        }
		i++;
	} 	
}

//----------------------------------------------------------------------------------
bool App::IsGoodArgs()
{
  QFileInfo	fis;
  QFileInfo	fid;
  bool		ok = false;
  
	if (dict["EXIT"] == "error")
	{
		DisplayHelp();
		return ok;
	}

	
	// Проверим остальные аргументы
	
	if (dict.contains("SrcName") && dict.contains("DstName"))// все ли данные введены ?
	{
		fis.setFile(dict["SrcName"]);
		fid.setFile(dict["DstName"]);
		
		if (fis.isFile())
		{
			qDebug() << dict["SrcName"] << " - is file" << "\n\r";
			dict.insert("SrcType", "file");
			
			if (!fid.isFile())
			{
				qDebug() << "both source and destination must be file or dir" << "\n\r";
			}
			else
			{
				ok = true;
			}
		}
		else if (fis.isDir())
		{
			qDebug() << dict["SrcName"] << " - is dir" << "\n\r";
			dict.insert("SrcType", "dir");
			
			if (!fid.isDir())
			{
				qDebug() << "both source and destination must be file or dir" << "\n\r";
			}
			else
			{
				ok = true;
			}		
		}
		else 
		{
			qDebug() << dict["SrcName"] << " - is not file or dir" << "\n\r";
		}
	}
	else
	{
		fprintf(stderr, "Too few args\n");
	}
	
	if (!ok)
		DisplayHelp();

	return ok;
}

//----------------------------------------------------------------------------------
void App::DisplayHelp()
{

	fprintf(stderr, "\nFile reencodder %s\n"
					"This program reencoded text files\n\n", SW_VERSION);
	
	fprintf(stderr, "Usage: %s options\n\n"
					"  -h, --help                      Display this help and exit.\n"
					"  -v, --version                   Display version.\n"
					"  -s, --source=<file,codec>       Input file and codec.\n"
					"  -d, --destination=<file,codec>  Output file and codec.\n"
					"\n", qPrintable(dict["CMD"]));

}

//----------------------------------------------------------------------------------
void App::DisplayRev()
{
	fprintf(stderr, "File reencodder %s\n", SW_VERSION);
}

//----------------------------------------------------------------------------------
bool App::IsReqInfo()
{
	if (dict["EXIT"] == "yes")
	{
		if (dict["HELP"] == "yes")
		{
			DisplayHelp();
		}
		else
		{
			DisplayRev();
		}
		return 1;
	}
	
	return 0;
}


