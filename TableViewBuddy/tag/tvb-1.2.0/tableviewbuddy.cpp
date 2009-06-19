/**	\file	tableviewbuddy.cpp
 *	\brief	Класс-партнёр для табличного представления (Qt4).
 *	\author	Литкевич Юрий (lit-uriy@yandex.ru).
 *	Этот класс задуман для расширения возможностей табличного представления
 *	наиболее распространёнными функциями. Такими как копирование, форматирование таблицы и др.
 **********************************************
 *	EN: 
 *	Class-buddy for table view (Qt4).
 *	Author:	Yuriy Litkevich (lit-uriy@yandex.ru).
 *	This class is conceived for the extension of possibilities of a table view
 *	by the most used functions. Such as copying, formatting of the table view, etc.
 */
#include <QTableView>
#include <QtDebug>
#include <QAction>
#include <QApplication>
#include <QClipboard>

#include "tableviewbuddy.h"

inline void initMyResource(){ Q_INIT_RESOURCE(tableviewbuddy); }

TableViewBuddy::TableViewBuddy(QTableView *tv): QObject(tv)
{
	view = tv;
	// RU: !!!!!!!!! Меняет политику контекстного меню представления !!!!!!!!!!!
	// EN: !!!!!!!!! Changes context menu policy policy of the table view !!!!!!!!!!!
	view->setContextMenuPolicy(Qt::ActionsContextMenu);

	initMyResource();
	
	actionCopy = new QAction(this);
	actionCopy->setIcon (QIcon(":/images/edit_copy.png"));
	actionCopy->setText(tr("&Copy"));
	actionCopy->setShortcut(tr("Ctrl+C"));
	actionCopy->setStatusTip(tr("Copy selected cells"));
	connect(actionCopy, SIGNAL(triggered()),
			 this,		SLOT(slotCopy()));
	
	view->addAction(actionCopy);
}


void TableViewBuddy::slotCopy()
{
	QApplication::clipboard()->setText(copy());
}


QString TableViewBuddy::copy()
{
  QModelIndex	index;
  unsigned int	minrow, mincolumn;
  unsigned int	maxrow, maxcolumn;
  unsigned int	i, j;
  QString		str;


	// Ищем минимумы и максимумы
	const QItemSelection ranges = view->selectionModel()->selection();
	// используем только первую выделенную область
	minrow = ranges.at(0).top();
	mincolumn = ranges.at(0).left();
	maxrow = ranges.at(0).bottom();
	maxcolumn = ranges.at(0).right();

	qDebug() << "Copy, FROM" << QString("(%1,%2)").arg(minrow).arg(mincolumn)
			 << "TO" << QString("(%1,%2)").arg(maxrow).arg(maxcolumn);
	
	// Само копирование
	for (i=minrow; i <= maxrow; ++i)
	{
		if (i>minrow)
			str += "\n";
		for (j=mincolumn; j <= maxcolumn; ++j)
		{
			if (j>mincolumn)
				str += "\t";
			index = view->model()->index(i, j, QModelIndex());
			QString t = view->model()->data(index).toString();
			str += t;
		}
	}
	qDebug() << "Copy:\n" << str;
	return str;
	//QApplication::clipboard()->setText(str);
}

