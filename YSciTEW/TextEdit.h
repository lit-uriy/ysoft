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
#ifndef TEXTEDIT_H_
#define TEXTEDIT_H_

#include <QFrame>

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>

//class TabWidget;
class TextEdit : public QFrame {
	Q_OBJECT
	Q_PROPERTY(bool partOfProject READ isPartOfProject WRITE setInProject);
	
public:
	TextEdit(QWidget *parent=0);
	virtual ~TextEdit();
	
public:
	QsciScintilla *pEditor() const;
	void setInProject(bool is);
	bool isPartOfProject() const;
	void setupDefaultLexer();
	QsciLexerCPP *pLexer() const;
	void loadApi();
	
private:
	//TabWidget* mwidget;
	bool			isInProject;
	QsciLexerCPP	*lexer;
	QsciScintilla	*editor;
	QsciAPIs		*api;
	
private slots:
	void slotTextChanged();
	
public slots:
	void setupDefaults();
	
signals:
	void wasModified(int index);
};
#endif

