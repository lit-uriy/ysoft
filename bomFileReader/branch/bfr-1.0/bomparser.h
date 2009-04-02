/*!
 *	\file	bomparser.h
 *	\brief	Интерфейс класса "BomParser".
 */
#ifndef BOMPARSER_H
#define BOMPARSER_H


class DbHanle;

/**	Класс BomParser является ... .
 * 	Этот класс ...
 */
class BomParser
{
public:
    BomParser(QString f_name);

	void setDelimiter(QString delim);
	void parse();

private:
	void processLine(QString line);


private:
	unsigned int	nol; // number of line
	bool			find_first;
	QString 		delimiter;
	QString 		file_name;
	DbHanle			*db;
	

};

#endif //BOMPARSER_H

