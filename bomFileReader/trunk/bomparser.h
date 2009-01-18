/*!
 *	\file	bomparser.h
 *	\brief	Интерфейс класса "BomParser".
 */
#ifndef BOMPARSER_H
#define BOMPARSER_H

#include <QObject>

/**	Класс BomParser является ... .
 * 	Этот класс ...
 */
class BomParser
{
//    Q_OBJECT

public:
    BomParser(QString f_name);

	void setDelimiter(QString delim);
	void parse();
/*
private slots:
	void slotOpenFileDialog();
	void slotOpenFileQuick();
*/
private:
	void processLine(QString line);


private:
	QString delimiter;
	QString file_name;

};

#endif //BOMPARSER_H

