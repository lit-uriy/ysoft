/*!
 *	\file	mainwindow.cpp
 *	\brief	Реализация класса "MainWindow".
 */

#include <QtGui>

#include "mainwindow.h"
#include "bomparser.h"


MainWindow::MainWindow(QWidget* p_parent) : QWidget(p_parent)
{
	setupUi(this);
	
	root_path = "./";
	
	connect(btn_open, SIGNAL(clicked()), this, SLOT(slotOpenFileDialog()));
	connect(edt_path, SIGNAL(returnPressed()), this, SLOT(slotOpenFileQuick()));
    
	setWindowTitle(tr("Читатель BOM-файлов"));
}

void MainWindow::slotOpenFileDialog()
{
	file_name = QFileDialog::getOpenFileName(this,
							 tr("Открыть BOM-файл"),
							 root_path,
							 tr("BOM-файлы (*.bom);;Текстовые файлы (*.txt);;Все файлы (*)"));
	
	setCurrentPath(file_name);
	parseBom(file_name);
}


void MainWindow::slotOpenFileQuick()
{
  QFileInfo 	fi;
  
	file_name = edt_path->text();
	fi.setFile(file_name);
	if(!fi.exists())
	{
		QMessageBox::warning(this, tr("Предупреждение"),
                   tr("Файл не найден"),
                   QMessageBox::Ok);
		return;
	}
	
	setCurrentPath(file_name);
	// Анализируем bom-файл
	parseBom(file_name);
}

void MainWindow::setCurrentPath(QString f_name)
{
  QFileInfo fi;
  
	if(f_name.isEmpty()) return;
	
	edt_path->setText(f_name);
	fi.setFile(f_name);
	root_path = fi.absolutePath();

qDebug() << "File:" << f_name;
qDebug() << "Path:" << root_path;

}

void MainWindow::parseBom(QString f_name)
{
  BomParser	parser(f_name);
	
	parser.setDelimiter(edt_delim->text());
	parser.parse();
}


//===========================================================
//				Создание БД настроек приложения
//===========================================================
/*
bool  Session::CreateDb()
{
  QSqlQuery appdbquery(appdb);
  QString	querystr;
  QString	tmp;
  bool ok;
  
	// Создаем таблицу груп пользователей
	querystr=" \
CREATE TABLE PCB \
(  \
  F_ID			INTEGER	PRIMARY KEY AUTOINCREMENT,	 \
  F_REFDES		Text		 \
  F_REFDES		Text		 \
); \
";
	
	ok = appdbquery.exec(querystr);
	if (!ok)
	{
		QString qerr = appdb.lastError().text();
		appdb_msg_err = QObject::tr("Невозможно создать служебную БД.\n\rПричина: ")+qerr;
		return ok;
	}	

	// Заполняем таблицу груп пользователей	
	querystr="INSERT INTO APPGROUP (F_ID, F_GROUP) VALUES (:id, :group)";
	appdbquery.prepare(querystr);
	appdbquery.bindValue(":id", GID_ROOT); appdbquery.bindValue(":group", "root");
	appdbquery.exec();
	appdbquery.bindValue(":id", GID_ADMIN); appdbquery.bindValue(":group", "admin");
	appdbquery.exec();
	appdbquery.bindValue(":id", GID_USER); appdbquery.bindValue(":group", "user");
	ok = appdbquery.exec();	

	// Создаем таблицу пользователей
	
	tmp.setNum(GID_USER);
	querystr=" \
CREATE TABLE APPUSER \
(  \
  F_ID			INTEGER	PRIMARY KEY AUTOINCREMENT,	 \
  F_LOGIN		Text,		 \
  F_PSWD		Text,		 \
  F_GROUP		INTEGER DEFAULT " + tmp +",		 \
  F_FIRSTNAME	Text,		 \
  F_LASTNAME	Text		 \
); \
";

	ok = appdbquery.exec(querystr);

	if (!ok)
	{
		QString qerr = appdbquery.lastError().text();
		appdb_msg_err = QObject::tr("Невозможно создать служебную БД.\n\rПричина: ")+qerr;
		return ok;
	}	

	
	// Заполняем таблицу пользователей	
	querystr="\
INSERT INTO \
APPUSER (F_ID, F_LOGIN, F_PSWD, F_GROUP, F_FIRSTNAME, F_LASTNAME) \
VALUES (:id, :login, :paswd, :group, :firstname, :lastname)";
	appdbquery.prepare(querystr);
	appdbquery.bindValue(":id", GID_ROOT);	appdbquery.bindValue(":login", "root"); 
	appdbquery.bindValue(":paswd", "toor"); appdbquery.bindValue(":group", GID_ROOT);
	appdbquery.bindValue(":firstname", "root"); appdbquery.bindValue(":lastname", "root");
	appdbquery.exec();

	// Создаем таблицу прочих настроек
	querystr=" \
CREATE TABLE APPSETTINGS \
(  \
  F_ID			INTEGER	PRIMARY KEY AUTOINCREMENT,	 \
  F_TYPE		Text,		 \
  F_VALUE		Text		 \
); \
";
	
	ok = appdbquery.exec(querystr);
	if (!ok)
	{
		QString qerr = appdb.lastError().text();
		appdb_msg_err = QObject::tr("Невозможно создать служебную БД.\n\rПричина: ")+qerr;
		return ok;
	}	

	// Заполняем таблицу прочих настроек
	querystr="INSERT INTO APPSETTINGS (F_TYPE, F_VALUE) VALUES (:type, :value)";
	appdbquery.prepare(querystr);
	appdbquery.bindValue(":type", "db_driver");
	appdbquery.bindValue(":value", "");
	appdbquery.exec();
	appdbquery.bindValue(":type", "db_name");
	appdbquery.bindValue(":value", "");
	appdbquery.exec();
	appdbquery.bindValue(":type", "db_user_name");
	appdbquery.bindValue(":value", "");
	appdbquery.exec(); 
	appdbquery.bindValue(":type", "db_user_paswd");
	appdbquery.bindValue(":value", "");
	appdbquery.exec(); 
	appdbquery.bindValue(":type", "db_charset");
	appdbquery.bindValue(":value", "");
	appdbquery.exec();
	appdbquery.bindValue(":type", "style");
	appdbquery.bindValue(":value", "");
	appdbquery.exec(); 

	return ok;
}
*/

