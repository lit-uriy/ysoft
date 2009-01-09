/** Реализация виджета.
 *	\file	yscitew.cpp
 */
#include "yscitew.h"

#include <QsciLexerCPP>
#include <QtGui>

YSciTEW::YSciTEW(QWidget* parent): QsciScintilla(parent)
{
/*

	this = new QsciScintilla(this);

	QHBoxLayout *layout = new QHBoxLayout;

	layout->addWidget(this);
	layout->setSpacing(0);
	layout->setMargin(0);

	setLayout(layout);
	
	
	

	connect(this, SIGNAL(textChanged()), this, SLOT(slotTextChanged()));
	*/
	this->setupDefaults();
	
	this->zoomOut(2);
	this->setCaretLineVisible(1);
	this->setCaretLineBackgroundColor(QColor(180,242,244,100));
	
}
/*

YSciTEW::~YSciTEW()
{
	//delete this;
	if(lexer)
		delete lexer;
}


void YSciTEW::slotTextChanged()
{
	this->setModified(true);
	//emit wasModified(mwidget->indexOf(this));
}

void YSciTEW::setInProject(bool is)
{
	isInProject = is;
}

bool YSciTEW::isPartOfProject() const
{
	return isInProject;
}
*/
void YSciTEW::setupDefaults()
{
	setupDefaultLexer();

	this->setFolding(QsciScintilla::BoxedTreeFoldStyle);

    //setup end-of-line mode
    #if defined Q_WS_X11
    this->setEolMode(QsciScintilla::EolUnix);
    #elif defined Q_WS_WIN
    this->setEolMode(QsciScintilla::EolWindows);
    #elif defined Q_WS_MAC
    this->setEolMode(QsciScintilla::EolMac);
    #endif

    //setup auto-indentation
    this->setAutoIndent(true);
    this->setIndentationGuides(true);
    this->setIndentationsUseTabs(true);
    this->setIndentationWidth(4);

    //setup margins
    this->setMarginsBackgroundColor(QColor(189, 178, 248));
    this->setMarginLineNumbers(1, true);
    this->setMarginWidth(1, QString("10000"));

    //setup brace matching
    this->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    this->setMatchedBraceBackgroundColor(Qt::yellow);
    this->setUnmatchedBraceForegroundColor(Qt::black);

    //setup autocompletion
    this->setAutoCompletionSource(QsciScintilla::AcsAll);
    this->setAutoCompletionCaseSensitivity(true);
    this->setAutoCompletionReplaceWord(true);
    this->setAutoCompletionShowSingle(true);
    this->setAutoCompletionThreshold(2);

    this->setUtf8(true);	
}

void YSciTEW::setupDefaultLexer()
{
	//if(lexer) delete lexer;

    lexer = new QsciLexerCPP(this);
    lexer->setFoldComments(true);
    lexer->setFoldAtElse(true);
    lexer->setFoldPreprocessor(true);

	#if defined Q_WS_WIN
    int font_id = QFontDatabase::addApplicationFont(":/res/fonts/COURI.TTF");
    lexer->setFont(QFont(QFontDatabase::applicationFontFamilies(font_id).first()));
    #elif defined Q_WS_X11
    lexer->setFont(QFont("Monospace"));
    #endif

	lexer->setAutoIndentStyle(QsciScintilla::AiOpening);

    //...

    this->setLexer(lexer);
}
/*
QsciLexerCPP* YSciTEW::pLexer() const
{
	return lexer;
}

QsciScintilla* YSciTEW::pEditor() const
{
	return this;
}


void YSciTEW::loadApi()
{

	QDir dir(QApplication::applicationDirPath());
	dir.cd("apis");
	qDebug() << "Absolute path of APIs directory: " + dir.absolutePath();
	QStringList lst = dir.entryList();
	qDebug() << "Loading APIs...";
	foreach(QString api_path, lst) {
		if(api_path!="." && api_path!="..") {
			api->load(dir.absolutePath() + "/" + api_path);
			qDebug() << "Current loaded API: " << api_path;
		}
	}
	qDebug() << "Preparing APIs...";
	api->prepare();
	//delete label;
	qDebug() << "API prepared!";
}

*/

