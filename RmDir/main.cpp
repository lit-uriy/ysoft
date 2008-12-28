#include <QCoreApplication>
#include <QtCore>

bool deleteDir(QDir dir, QString indent)
{
  QStringList	lst;
  QString		path;
  QTextStream	out(stdout);
  QTextCodec	*concodec = QTextCodec::codecForName("CP866");		// Кодек для консоли
  bool			res = true;
  
	out.setCodec(concodec);
	path = dir.canonicalPath();

	
	
	out << indent << path << endl;
	indent.replace("+--", "|  ");
	
	
	// Список всех файлов
	lst = dir.entryList(QDir::Files/*, QDir::Name|QDir::LocaleAware|QDir::IgnoreCase*/); //QDir::Dirs
	//out << "==== Delete File =====" << endl;
	foreach(QString str, lst)
	{
		out << indent << "|    " << str;
		// Удаляем файл
		res = QFile::remove(path + "/" + str);
		if (!res)
		{
			out << " - Error" << endl;
			return res;
		}
		out << " - Ok" << endl;
	}

	// Список всех каталогов
	lst = dir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot, QDir::Name|QDir::LocaleAware|QDir::IgnoreCase); //QDir::Dirs
	//out << "==== Delete Dir =====" << endl;
	foreach(QString str, lst)
	{
		QDir indir(path + "/" + str);
		res = deleteDir(indir, indent + "+--");
		if (!res)
			return res;
	}
	
	// Удаляем текущий каталог
	out << indent << "-> " << path;
	res = dir.rmdir(path);
	if (!res)
	{
		out << " - Error" << endl;
		return res;
	}
	out << " - Ok" << endl;
	out << indent  << endl;	
	
	return res;
}


int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  QString		path;
  QStringList	args;
  QDir			dir;
  
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
	args = QCoreApplication::arguments();
	
	if (args.size() >= 2)
		path = QDir::fromNativeSeparators(args.at(1));
	else
		path = QDir::currentPath();
	
	dir.setPath(path);
	
	if (!dir.exists())
	{
		qDebug() << "Dir:" << path << "NOT exist";
		return 1;
	}
	qDebug() << "App dir:" << QCoreApplication::applicationDirPath();
	qDebug() << "Current dir:" << dir.canonicalPath();
	qDebug() << "============================================";
	if (!deleteDir(dir, ""))
	{
		qDebug() << "Error on delete dir:" << dir.canonicalPath();
		return 1;
	}

   return 0;
}
