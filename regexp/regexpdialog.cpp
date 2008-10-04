

#include <QtGui>

#include "regexpdialog.h"

RegExpDialog::RegExpDialog(QWidget *parent)
    : QDialog(parent)
{

	// Шаблон
    patternComboBox = new QComboBox;
    patternComboBox->setEditable(true);
    patternComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    patternLabel = new QLabel(tr("&Шаблон:"));
    patternLabel->setBuddy(patternComboBox);

    escapedPatternLineEdit = new QLineEdit;
    escapedPatternLineEdit->setReadOnly(true);
    QPalette palette = escapedPatternLineEdit->palette();
    palette.setBrush(QPalette::Base,
                     palette.brush(QPalette::Disabled, QPalette::Base));
    escapedPatternLineEdit->setPalette(palette);

    escapedPatternLabel = new QLabel(tr("Экранированный шаблон:"));
    escapedPatternLabel->setBuddy(escapedPatternLineEdit);
	
	// Тип синтаксиса
    syntaxComboBox = new QComboBox;
    syntaxComboBox->addItem(tr("Регулярное выражение v1"), QRegExp::RegExp);
    syntaxComboBox->addItem(tr("Регулярное выражение v2"), QRegExp::RegExp2);
    syntaxComboBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    syntaxComboBox->addItem(tr("Фиксированная строка"), QRegExp::FixedString);

    syntaxLabel = new QLabel(tr("Синтаксис шаблона:"));
    syntaxLabel->setBuddy(syntaxComboBox);
	
    caseSensitiveCheckBox = new QCheckBox(tr("Учитывать регистр"));
    caseSensitiveCheckBox->setChecked(true);
    minimalCheckBox = new QCheckBox(tr("Минимум"));
	btn = new QPushButton (tr("Пуск!"));

    QHBoxLayout *checkBoxLayout = new QHBoxLayout;
    checkBoxLayout->addWidget(caseSensitiveCheckBox);
    checkBoxLayout->addWidget(minimalCheckBox);
    checkBoxLayout->addStretch(1);
	checkBoxLayout->addWidget(btn);
	
	
	// Поле входного и выходного текста
	splitter = new QSplitter(this);
	splitter->setOrientation(Qt::Vertical);
	
	// Поле входного текста
	infr = new QWidget(splitter);
	
    QHBoxLayout *inLayout = new QHBoxLayout(infr);
	inLayout->setContentsMargins(0, 0, 0, 0);
	inLayout->setSpacing (10);
	
    intextlbl = new QLabel(tr("Входной текст:"));	//intextlbl = new QLabel(infr);
	inLayout->addWidget(intextlbl);

#ifdef INMULTYLINE		
	intext = new QTextEdit(infr);
	intext->setAcceptRichText (false);
#else
	intext = new QComboBox(infr);
	intext->setEditable(true);
#endif

	inLayout->addWidget(intext);
	
	splitter->addWidget(infr);
	

	// Поле выходного текста
	outfr = new QWidget(splitter);
	
	QHBoxLayout *outLayout = new QHBoxLayout(outfr);
	outLayout->setContentsMargins(0, 0, 0, 0);
	outLayout->setSpacing (10);
	
    outtextlbl = new QLabel(tr("Выходной текст:"));
	outLayout->addWidget(outtextlbl);
	

#ifdef OUTMULTYLINE		
	outtext = new QTextEdit(infr);
	outtext->setAcceptRichText (false);
#else
	outtext = new QComboBox(infr);
#endif

	outLayout->addWidget(outtext);
	
	splitter->addWidget(outfr);

	// Поле счетчика совпадений
	cntLabel = new QLabel(tr("Счетчик совпадений:"));
    cntEdit = new QLineEdit;
    cntEdit->setReadOnly(true);
	
	// Прочие поля
    indexLabel = new QLabel(tr("Индекс соответствия:"));
    indexEdit = new QLineEdit;
    indexEdit->setReadOnly(true);

    matchedLengthLabel = new QLabel(tr("Длинна соответствия:"));
    matchedLengthEdit = new QLineEdit;
    matchedLengthEdit->setReadOnly(true);

    for (int i = 0; i < MaxCaptures; ++i) {
        captureLabels[i] = new QLabel(tr("Захват %1:").arg(i));
        captureEdits[i] = new QLineEdit;
        captureEdits[i]->setReadOnly(true);
    }
    captureLabels[0]->setText(tr("Соответствие:"));

    QGridLayout *mainLayout = new QGridLayout;
	
    mainLayout->addWidget(patternLabel, 0, 0);			mainLayout->addWidget(patternComboBox, 0, 1);
    mainLayout->addWidget(escapedPatternLabel, 1, 0);	mainLayout->addWidget(escapedPatternLineEdit, 1, 1);
    mainLayout->addWidget(syntaxLabel, 2, 0);			mainLayout->addWidget(syntaxComboBox, 2, 1);
    
	mainLayout->addLayout(checkBoxLayout, 3, 0, 1, 2);
	mainLayout->addWidget(splitter, 4, 0, 1, 3);
	
	mainLayout->addWidget(cntLabel, 5, 0);				mainLayout->addWidget(cntEdit, 5, 1);
    mainLayout->addWidget(indexLabel, 6, 0);			mainLayout->addWidget(indexEdit, 6, 1);
    mainLayout->addWidget(matchedLengthLabel, 7, 0);	mainLayout->addWidget(matchedLengthEdit, 7, 1);
	
	
	int nextwgt=1+mainLayout->rowCount();
    for (int j = 0; j < MaxCaptures; ++j)
	{
        
		mainLayout->addWidget(captureLabels[j], nextwgt + j, 0);
        mainLayout->addWidget(captureEdits[j], nextwgt + j, 1);
    }
	
	mainLayout->addItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding), 7 +MaxCaptures+1, 0);
	
    setLayout(mainLayout);



    patternComboBox->addItem(tr("[A-Za-z_]+([A-Za-z_0-9]*)"));
#ifdef INMULTYLINE	
	intext->setPlainText(tr("(10 + delta4) * 32"));
#else
    intext->addItem(tr("(10 + delta4) * 32"));
#endif

    connect(btn, SIGNAL(clicked()), this, SLOT(refresh()));
#ifdef INMULTYLINE	    
	connect(intext, SIGNAL(textChanged()), this, SLOT(refresh()));
#else
	connect(intext, SIGNAL(editTextChanged(const QString &)), this, SLOT(refresh()));
#endif
	connect(caseSensitiveCheckBox, SIGNAL(toggled(bool)), this, SLOT(refresh()));
    connect(minimalCheckBox, SIGNAL(toggled(bool)), this, SLOT(refresh()));
    connect(syntaxComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(refresh()));
	
    setWindowTitle(tr("RegExp"));
    
    refresh();
}

void RegExpDialog::refresh()
{
  QString pattern;
  QString text;
  QString escaped;
  QRegExp rx;
  Qt::CaseSensitivity cs = Qt::CaseInsensitive;
  QRegExp::PatternSyntax syntax;
	  

	setUpdatesEnabled(false);

	outtext->clear();

    pattern = patternComboBox->currentText();
#ifdef INMULTYLINE		
    text = intext->toPlainText();
#else
	text = intext->currentText();
#endif

	
	rx.setPattern(pattern);
    escaped = pattern;
    escaped.replace("\\", "\\\\");
    escaped.replace("\"", "\\\"");
    escaped.prepend("\"");
    escaped.append("\"");
    escapedPatternLineEdit->setText(escaped);
    
    if (caseSensitiveCheckBox->isChecked())
        cs = Qt::CaseSensitive;
	
    rx.setCaseSensitivity(cs);
    rx.setMinimal(minimalCheckBox->isChecked());
    
	syntax = QRegExp::PatternSyntax(syntaxComboBox->itemData(syntaxComboBox->currentIndex()).toInt());
    rx.setPatternSyntax(syntax);

    QPalette palette = patternComboBox->palette();
    if (!rx.isValid())
	{
		palette.setColor(QPalette::Text, Qt::red);
    }
	else
	{
        palette.setColor(QPalette::Text, intext->palette().color(QPalette::Text));
		
		
		
		
		indexEdit->setText(QString::number(rx.indexIn(text)));
		matchedLengthEdit->setText(QString::number(rx.matchedLength()));
		
		for (int i = 0; i < MaxCaptures; ++i)
		{
			captureLabels[i]->setEnabled(i <= rx.numCaptures());
			captureEdits[i]->setEnabled(i <= rx.numCaptures());
			captureEdits[i]->setText(rx.cap(i));
			
		}
		
	/* 
		QMessageBox::information(this, tr("Слот"),
									tr("Мы в слоте\r\n")+text,
									QMessageBox::Ok);	
	*/	

		
		QString tmpstr;//
		QStringList	list;//

		int pos = 0;
		int mch = 0;
		int capcnt = 0;
		while (pos >= 0)
		{
			pos = rx.indexIn(text, pos);
			
			//outtext->append(rx.cap(0));
			//list << rx.cap(0);
			mch = rx.matchedLength();
			
			if(mch > 0)
			{
				capcnt++;
				outtext->setPlainText(outtext->toPlainText()+rx.cap(0)+"\r\n");
			}
			/**/
			/*
			if(pos >= -1)
				capcnt++;
			
			QMessageBox::information(this, tr("Слот"),
										tr("Мы в слоте\r\n")+QString("pos=%1, mach=%2").arg(pos).arg(mch),
										QMessageBox::Ok);
			*/
			
			pos += mch;
			if (!pos) break;
		}	
		cntEdit->setText(QString::number(capcnt));
	/*
		QStringList::iterator it = list.begin();
		while (it != list.end())
		{
			tmpstr+=(*it);
			//outtext->setPlainText((*it)+"\n\r");+"\n\r"
			outtext->setPlainText(outtext->toPlainText()+(*it));
			++it;
		}

		QMessageBox::information(this, tr("Слот"),
									tmpstr,
									QMessageBox::Ok);	
	*/	
		
	

    }

	
	patternComboBox->setPalette(palette);
    setUpdatesEnabled(true);
}
