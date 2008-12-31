/***************************************************************************
 *   Copyright (C) 2008 by Anatoliy Radchenko                              *
 *   anatox91@yandex.ru                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "TextEdit.h"
#include <QtGui>
//#include "TabWidget.h"
TextEdit::TextEdit(QWidget* parent): QFrame(parent), isInProject(false), lexer(0)
{
	//mwidget = qobject_cast<TabWidget*>(parent);

	editor = new QsciScintilla(this);
	/**/
	QHBoxLayout *layout = new QHBoxLayout;

	layout->addWidget(editor);
	layout->setSpacing(0);
	layout->setMargin(0);

	setLayout(layout);
	
	
	setupDefaults();

	connect(editor, SIGNAL(textChanged()), this, SLOT(slotTextChanged()));
	editor->zoomOut(2);
	editor->setCaretLineVisible(1);
	editor->setCaretLineBackgroundColor(QColor(180,242,244,100));
	//...
}


TextEdit::~TextEdit()
{
	//delete editor;
	if(lexer)
		delete lexer;
}


void TextEdit::slotTextChanged()
{
	editor->setModified(true);
	//emit wasModified(mwidget->indexOf(this));
}

void TextEdit::setInProject(bool is)
{
	isInProject = is;
}

bool TextEdit::isPartOfProject() const
{
	return isInProject;
}

void TextEdit::setupDefaults()
{
	setupDefaultLexer();

	editor->setFolding(QsciScintilla::BoxedTreeFoldStyle);

    //setup end-of-line mode
    #if defined Q_WS_X11
    editor->setEolMode(QsciScintilla::EolUnix);
    #elif defined Q_WS_WIN
    editor->setEolMode(QsciScintilla::EolWindows);
    #elif defined Q_WS_MAC
    editor->setEolMode(QsciScintilla::EolMac);
    #endif

    //setup auto-indentation
    editor->setAutoIndent(true);
    editor->setIndentationGuides(true);
    editor->setIndentationsUseTabs(true);
    editor->setIndentationWidth(15);

    //setup margins
    editor->setMarginsBackgroundColor(QColor(189, 178, 248));
    editor->setMarginLineNumbers(1, true);
    editor->setMarginWidth(1, QString("10000"));

    //setup brace matching
    editor->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    editor->setMatchedBraceBackgroundColor(Qt::yellow);
    editor->setUnmatchedBraceForegroundColor(Qt::black);

    //setup autocompletion
    editor->setAutoCompletionSource(QsciScintilla::AcsAll);
    editor->setAutoCompletionCaseSensitivity(true);
    editor->setAutoCompletionReplaceWord(true);
    editor->setAutoCompletionShowSingle(true);
    editor->setAutoCompletionThreshold(2);

    editor->setUtf8(true);	
}

void TextEdit::setupDefaultLexer()
{
	if(lexer)
		delete lexer;

    lexer = new QsciLexerCPP(this);
    lexer->setFoldComments(true);
    lexer->setFoldAtElse(true);
    lexer->setFoldPreprocessor(true);
/**/
	#if defined Q_WS_WIN
    int font_id = QFontDatabase::addApplicationFont(":/res/fonts/COURI.TTF");
    lexer->setFont(QFont(QFontDatabase::applicationFontFamilies(font_id).first()));
    #elif defined Q_WS_X11
    lexer->setFont(QFont("Monospace"));
    #endif

	lexer->setAutoIndentStyle(QsciScintilla::AiOpening);

    //...

    editor->setLexer(lexer);
}

QsciLexerCPP* TextEdit::pLexer() const
{
	return lexer;
}

QsciScintilla* TextEdit::pEditor() const
{
	return editor;
}






