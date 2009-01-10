#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>
#include <iostream>

const char * SW_VERSION = "0.1.0";

void showHelp(const char *appName)
{
    fprintf(stderr, "Yurik's Code Generator %s\n", SW_VERSION);

    fprintf(stderr, "Usage: %s [options] <file.ui>\n\n"
			"This program generates two files file.cpp and file.h\n"
			" for use Qt Designer file.ui with the multiple inheritance approach.\n\n"
            "  -h, --help                display this help and exit\n"
            "  -v, --version             display version\n"
            "\n", appName);
}


int main(int argc, char** argv)
{
  int arg = 0;
  QString	filename;
  QString	classname;
  QString	parentname;
  
  
	while (arg < argc) 
	{
        ++arg;	
        QString opt = QString::fromLocal8Bit(argv[arg]);
		QRegExp rx("*.mod");
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
	} 

  QCoreApplication app(argc, argv);

	/*
	ChekFileType(filename)
	*/
  QTextStream	stream;
  QFile			file(filename);
  bool			ok;
  char			rcode;
  unsigned char			code;
  uint			i;
  uint			format;
  QString		fstring;
  
	
	ok = file.open(QFile::ReadOnly);
	if (!ok)
	{
		qDebug() << "Unable to be open";
		return 1;
	}
	stream.setDevice(&file);
	i = file.read( &rcode, 1);
	if (i <= 0)
	{
		qDebug() << "Unable to be read";
		return 1;	
	}
	
	code = (unsigned char)rcode;
	i = (unsigned int)code;
	qDebug() << "First byte=" << QString::number(i, 16).toUpper();	
	/**/
	
	/**/
	if ((i == 0xF0) || (i == 0xF7) || (i == 0x01))		// Oberon File Format
	{
		format = 0;	
		qDebug() << "file into: Oberon File Format. Code=" << QString::number(i, 16).toUpper();									
	}
	else if (i == 0x3C)	// possibly an XML, check further
	{
		QRegExp rx;
		rx.setPattern("<?XML VERSION=*");
		rx.setPatternSyntax(QRegExp::Wildcard);
		
		// check IF just an XML or BB Format 
		stream.seek(0);
		fstring = stream.readLine();
		fstring = fstring.toUpper();
		qDebug() << "Reading string:" << fstring;
		
		if (fstring.contains(rx))
		{
			qDebug() << "file contains: <?XML VERSION=*";
			rx.setPattern("*<?BLUEBOTTLE FORMAT*");
			fstring = stream.readLine();
			fstring = fstring.toUpper();
			qDebug() << "Reading string:" << fstring;
			
			if (fstring.contains(rx))
			{
				qDebug() << "file contains: *<?BLUEBOTTLE FORMAT*";
				qDebug() << "file into: Bluebottle File Format. Code=" << QString::number(i, 16).toUpper();
				format = 1;										// Bluebottle File Format
			}
			else
			{
				format = 2;										// XML - treat as UTF-8
				qDebug() << "file into: XML - treat as UTF-8";
			};
		}
		else
		{
			qDebug() << "file into: Text/Other - treat as UTF-8";
			format = 2;											// Text/Other - treat as UTF-8
		};		
	}
	else
	{														// Neither Oberon nor XML/BB
		format = 2;
		qDebug() << "file into: Neither Oberon nor XML/BB";
	};
	
	
    return 0;
}
