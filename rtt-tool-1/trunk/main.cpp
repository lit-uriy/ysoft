/*!
 \file main.cpp
 \brief Основной файл программы.
 */

#include <QApplication>
#include <QTextCodec>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(mdi);

	QApplication app(argc, argv);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));// //UTF-8 Windows-1251
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); // Для функций перевода tr()

	QCoreApplication::setOrganizationName(QObject::tr("ЗАО \"ННН\""));
	QCoreApplication::setApplicationName(QObject::tr("ЭСТОП"));
	
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
