/*!
 *	\file	dbhandle.h
 *	\brief	Интерфейс класса "DbHanle".
 */

#ifndef DBHANDLE_H
#define DBHANDLE_H

#include <QSqlDatabase>
class QString;
class QStringList;
class QSqlDatabase;

/**	Класс BomParser является ... .
 * 	Этот класс ...
 */
class DbHanle
{
public:
    DbHanle(QString db_name);

	bool isOpen(){return connect_ok;}
	void createTable(QStringList lst);
	void insert(QStringList lst);

private:
	QSqlDatabase	db;
	QStringList		fields;
	bool			connect_ok;
};

#endif //DBHANDLE_H




