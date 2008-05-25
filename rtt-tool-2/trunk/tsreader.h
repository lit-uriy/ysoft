#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QStringList>
#include <QString>



//=====================================================
//		Получим список секций ts-файла
//=====================================================
bool GetListFrom(QFile *tsfile, QStringList &list)
{
  int	errorLine;
  int	errorColumn;
  bool	ok = false;  
  QDomDocument	doc;
  QString		errorStr;
	
	ok = doc.setContent( tsfile, true, &errorStr, &errorLine, &errorColumn);
    if (!ok) 
    {
        return ok;
    }

    QDomElement root = doc.firstChildElement("TS");
    QDomElement context = root.firstChildElement("context");
    QString		szValue = context.nodeValue();

    for(; !context.isNull(); context = context.nextSiblingElement("context")) 
    {
        QDomElement name = context.firstChildElement( "name");
        QString szName = name.nodeName();
		QString szValue = name.text();
        list.append( szValue);
		qDebug() << "See section: " << szValue << "\n\r";
    } 

    return ok;
}
