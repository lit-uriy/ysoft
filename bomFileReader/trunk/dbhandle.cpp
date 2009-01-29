/*!
 *	\file	dbhandle.cpp
 *	\brief	Реализация класса "DbHanle".
 */
#include <QObject>
#include <QtSql>
#include "dbhandle.h"

DbHanle::DbHanle(QString db_name)
{
	connect_ok = true;
	db = QSqlDatabase::addDatabase("QSQLITE","appdb");
	db.setDatabaseName(db_name);
	// Открываем БД
	if (!db.open())
	{
		QString qerr = db.lastError().text();
		qDebug() << QObject::tr("Невозможно открыть БД.\n\rПричина: ")+qerr;
		connect_ok = false;
	}
}

void DbHanle::createTable(QStringList lst)
{
  QSqlQuery q(db);
  QString	qstr;
  QString	tmp;
  bool ok;

	fields = lst;
	// Создаем таблицу на основе полей bom-файла
	qstr="CREATE TABLE PCB \
(  \
  F_ID			INTEGER	PRIMARY KEY AUTOINCREMENT";
  
	foreach(QString str, lst)
	{
		tmp = ",\n" + str + " Text";
		qstr += tmp;
	}
	qstr += ");";
	
	ok = q.exec(qstr);
	if (!ok)
	{
		QString qerr = q.lastError().text();
		qDebug() << QObject::tr("Невозможно создать таблицу.\n\rПричина: ")+qerr;
		connect_ok = false;
	}	
	qDebug() << "DbHanle::" << qstr;
}


void DbHanle::insert(QStringList lst)
{
  QSqlQuery q(db);
  QString	qstr;
  QString	tmp1, tmp2;
  bool 		ok;

	if(fields.size() != lst.size())
	{
		qDebug() << "DbHanle, fields.size() != lst.size()";
	}

	// Заполняем таблицу данными
	tmp1 = fields.join(", ");
	tmp2 = lst.join(", ");

	qstr = "INSERT INTO PCB (" + tmp1 + ") VALUES (" + tmp2 + ")";
	
	ok = q.exec(qstr);
	if (!ok)
	{
		QString qerr = q.lastError().text();
		qDebug() << QObject::tr("Невозможно записать в таблицу.\n\rПричина: ")+qerr;
		connect_ok = false;
	}	
	qDebug() << "DbHanle::" << qstr;
}

/*
SELECT (ComponentName || '--' || Value), count (ComponentName || Value )
FROM PCB
GROUP BY (ComponentName || Value)


*/