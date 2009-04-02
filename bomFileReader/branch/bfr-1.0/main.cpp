/*!
 \file main.cpp
 \brief Основной файл программы.
 */

#include <QApplication>
#include <QtGui>
#include <QTextCodec>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
//    Q_INIT_RESOURCE(mdi);

  QDir			dir_plugin;	// каталог плагинов
  QStyle	   *pStyle;		// стиль ПО
  QString		locale;		// язык локали
  QTranslator  *qttr;		// переводчик программы
  QStringList 	list_path;	// Список путей
  
	QApplication app(argc, argv);

	// Устанавливаем кодеки
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));// без этой кодировки с БД проблема
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); // Для функций перевода tr()

	// Устанавливаем свойства программы (понадобится для настроек)
	QCoreApplication::setOrganizationName(QObject::tr("ЗАО \"ННН\""));
	QCoreApplication::setApplicationName(QObject::tr("ЭСТОП АСУ"));

	// устанавливаем путь к плагинам (добавим каталог бинаря)
	dir_plugin = QDir(app.applicationDirPath()+"/plugins/");
	list_path << dir_plugin.absolutePath() << app.libraryPaths ();
	app.setLibraryPaths(list_path); 

	// Устанавливаем стили
	pStyle = QStyleFactory::create("Cleanlooks");//windowsxp Plastique windows
	QApplication::setStyle(pStyle);
	app.setPalette(pStyle->standardPalette());

	// Устанавливаем превод библиотек Qt
	locale = QLocale::system().name();	// запрос языка (например: "ru")
	qttr = new QTranslator; 
	qttr->load(QString("qt_") + locale); // загрузка файла qt_*.qm
	app.installTranslator(qttr);         // устанока переводчика	
	qDebug() << "Main: " << QDateTime::currentDateTime() << "\n\r";

	MainWindow mainWin;

	mainWin.resize(750, 550);
	mainWin.show();

    return app.exec();
}
