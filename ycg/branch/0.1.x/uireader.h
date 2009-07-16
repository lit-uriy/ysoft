#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QStringList>
#include <QString>



//=====================================================
//		
//=====================================================
bool GetClassName(const QString &filename, QString &classname, QString &parentname)
{
  int		errorLine;
  int		errorColumn;
  bool		ok = false;  
  QFile		uifile(filename);
  QString	errorStr;

  QDomDocument	doc;
  
	if (!uifile.exists())
	{
		qDebug() << "UI file: " << uifile.fileName() << "is absent" << "\n\r";
		return ok;
	}
	
	uifile.open( QIODevice::ReadOnly);
	
	ok = doc.setContent( &uifile, true, &errorStr, &errorLine, &errorColumn);
    if (ok) 
    {
		QDomElement root = doc.firstChildElement("ui");
		QDomElement widget = root.firstChildElement("widget");
		
		parentname = widget.attribute("class");
		classname = widget.attribute("name");	
		if (parentname.isNull() || classname.isNull())
			ok = false;
		
		//qDebug() << "UI file classname: " << classname << "\n\r";
		//qDebug() << "UI file parentname: " << parentname << "\n\r";
		
    }
	else
	{
		qDebug() << "errorLine: " << errorLine << "\n\r";
		qDebug() << "errorColumn: " << errorColumn << "\n\r";	
		qDebug() << "errorStr: " << errorStr << "\n\r";		
	}
	uifile.close();
    return ok;
}
