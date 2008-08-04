/*!
 *	\file	app.h
 *	\brief	Интерфейс класса консольного приложения.
 */

#include <qmap.h>
//#include <qstring.h>
#include <qstringlist.h>
#include <qlist.h>
#include <qtextstream.h>
#include <qdir.h>

class QString;

/*!
 *	\class	App
 *	\brief	Класс консольного приложения.
 */
class App
{
public:
    App( int& argc, char** argv );
    ~App();


/*!
 *	\fn		ParseCmdLine
 *	\brief	Анализатор параметров командной строки.
 */
    void ParseCmdLine();

/*!
 *	\fn		ValidateArgs
 *	\brief	Функция проверки параметров командной строки.
 */
    bool IsGoodArgs();

/*!
 *	\fn		DisplayHelp
 *	\brief	Функция отображающая справку по командной строке.
 */
    void DisplayHelp();

/*!
 *	\fn		DisplayRev
 *	\brief	Функция отображающая версию программы.
 */
	void DisplayRev();

/*!
 *	\fn		IsReqInfo
 *	\brief	Функция проверки требуется ли отобразить версию или справку.
 */
	bool IsReqInfo();
   

private:

/*!
 *	\var	dict
 *	\brief	Словарь параметров.
 *
 *	["CMD"]			- Имя прокраммы
 *	["EXIT"]		= no, yes, error	- выйти из программы? (нет, да, из-за ошибки)
 *	["HELP"]		= no, yes			- отобразить справку? (нет, да)
 *	["SrcName"]		- Имя исходного файла/каталога
 *	["SrcCodec"]	- Имя исходной кодировки
 *	["SrcType"]		- Тип исходного объекта
 *	["DstName"]		- Имя целевого файла/каталога
 *	["DstCodec"]	- Имя целевой кодировки
 */
    QMap<QString,QString> dict;

/*!
 *	\var	opts
 *	\brief	Опции командной строки.
 */
    QStringList opts;
	

};


