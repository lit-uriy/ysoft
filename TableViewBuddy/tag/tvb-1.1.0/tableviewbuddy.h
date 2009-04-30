/**	\file	tableviewbuddy.h
 *	\brief	Класс-партнёр для табличного представления (Qt4).
 *	\author	Литкевич Юрий (lit-uriy@yandex.ru).
 *	Этот класс задуман для расширения возможностей табличного представления
 *	наиболее распространёнными функциями. Такими как копирование, форматирование таблицы и др.
 **********************************************
 *	Class-buddy for table view (Qt4).
 *	Author:	Yuriy Litkevich (lit-uriy@yandex.ru).
 *	This class is conceived for the extension of possibilities of table view
 *	by the most used functions. Such as copying, formatting of the table view, etc.
 */
#include <QObject>
class QString;
class QTableView;
class QAction;


	// RU: !!!!!!!!! Меняет политику контекстного меню представления !!!!!!!!!!!
	// EN: !!!!!!!!! Changes context menu policy policy of the table view !!!!!!!!!!!
class TableViewBuddy: public QObject
{
    Q_OBJECT
public:
	TableViewBuddy(QTableView *tv);

public slots:
	void slotCopy();
	
protected:
	QString copy();
	
protected:
	QAction 	*actionCopy;
	QTableView	*view;

};


