#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QDebug>



//=====================================================
//		Установим соединение с БД
//=====================================================
bool OpenDb(QString dbname)
{
  bool ok;
  
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
	ok = db.open();
    if (!ok)
	{
		qDebug() << "OpenDb: " << db.lastError().text() << "\n\r";
		return ok;
    }
    return ok;
}

