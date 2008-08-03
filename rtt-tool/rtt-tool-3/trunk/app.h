/*!
 *	\file	app.h
 *	\brief	Интерфейс класса консольного приложения.
 */

#include <qmap.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qlist.h>
#include <qtextstream.h>
#include <qdir.h>



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
 *	\fn		parseCmdLine
 *	\brief	Анализатор параметров командной строки.
 */
    void parseCmdLine();

/*!
 *	\fn		validateArgs
 *	\brief	Функция проверки параметров командной строки.
 */
    void validateArgs();

/*!
 *	\fn		displayHelp
 *	\brief	Функция отображающая справку по командной строке.
 */
    bool displayHelp();


    enum NameType {
	File,
	Dir
    };

    NameType nameType( const QString& proFileName );
    bool isDone();
    bool isOk();
private:

/*!
 *	\var	dict
 *	\brief	.
 */
    QMap<QString,QString> dict;
	
    QStringList licensedModules;
    QStringList allSqlDrivers;
    QStringList allConfigs;
    QStringList disabledModules;
    QStringList enabledModules;
    QStringList modules;

    QStringList opts;	// Опции командной строки
	
    QStringList qmakeConfig;
    QStringList qtConfig;

    QStringList qmakeSql;
    QStringList qmakeSqlPlugins;

    QStringList qmakeStyles;
    QStringList qmakeStylePlugins;

    QStringList qmakeFormatPlugins;

    QStringList qmakeVars;
    QStringList qmakeDefines;
    //  makeList[0] for qt and qtmain
    //  makeList[1] for subdirs and libs
    //  makeList[2] for the rest
    QList<MakeItem*> makeList[3];
    QStringList qmakeIncludes;
    QStringList qmakeLibs;

    QMap<QString,QString> licenseInfo;
    QString outputLine;

    QTextStream outStream;
    QString sourcePath, buildPath;
    QDir sourceDir, buildDir;

    // Variables for usage output
    int optionIndent;
    int descIndent;
    int outputWidth;



    void desc(const char *description, int startingAt = 0, int wrapIndent = 0);
    void desc(const char *option, const char *description, bool skipIndent = false, char fillChar = '.');
    void desc(const char *mark_option, const char *mark, const char *option, const char *description, char fillChar = '.');
};


