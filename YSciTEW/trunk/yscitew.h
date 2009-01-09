/** Интерфейс виджета.
 *	\file	yscitew.h
 */
#ifndef YSCITEW_H_
#define YSCITEW_H_

#include <QFrame>

#include <QsciScintilla>

//#include <Qsci/qsciapis.h>

class QsciLexerCPP;

class YSciTEW : public QsciScintilla
{

public:
	YSciTEW(QWidget *parent=0);
	
	void setupDefaults();
	void setupDefaultLexer();
	
private:
	QsciLexerCPP	*lexer;

};
#endif // YSCITEW_H_

