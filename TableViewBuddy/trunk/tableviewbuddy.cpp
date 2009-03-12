/*!
 *	\file	tableviewbuddy.cpp
 *	\brief	Реализация класса "TableViewBuddy".
 */

#include <QTableView>
#include <QtDebug>
#include <QAction>
#include <QApplication>
#include <QClipboard>

#include "tableviewbuddy.h"


TableViewBuddy::TableViewBuddy(QTableView *tv): QObject(tv)
{
	view = tv;
	actionCopy = new QAction(view);
	actionCopy->setText(tr("&Copy"));
	actionCopy->setShortcut(tr("Ctrl+C"));
	view->addAction(actionCopy);
	connect(actionCopy, SIGNAL(triggered()),
			 this,		SLOT(slotCopy()));
	

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

