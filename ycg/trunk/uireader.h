#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QStringList>
#include <QString>



//=====================================================
//		Получим список секций ts-файла
//=====================================================
bool GetClassName(const QString &filename, QString &classname, QString &parentname)
{
  int		errorLine;
  int		errorColumn;
  bool		ok = false;  
  QFile		uifile(filename);
  QString	errorStr;

  QDomDocument	doc;
  
	qDebug() << uifile.fileName() << "\n\r";
	if (!uifile.exists())
		return ok;
	
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
		
		qDebug() << "classname: " << classname << "\n\r";
		qDebug() << "parentname: " << parentname << "\n\r";
		
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
