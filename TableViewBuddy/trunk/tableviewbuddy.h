/*!
 *	\file	tableviewbuddy.h
 *	\brief	Интерфейс класса "TableViewBuddy".
 */
#include <QObject>
class QString;
class QTableView;
class QAction;

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
