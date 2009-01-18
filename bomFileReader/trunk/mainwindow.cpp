/*!
 *	\file	mainwindow.cpp
 *	\brief	Реализация класса "MainWindow".
 */

#include <QtGui>

#include "mainwindow.h"
#include "bomparser.h"


MainWindow::MainWindow(QWidget* p_parent) : QWidget(p_parent)
{
	setupUi(this);
	
	root_path = "./";
	
	connect(btn_open, SIGNAL(clicked()), this, SLOT(slotOpenFileDialog()));
	connect(edt_path, SIGNAL(returnPressed()), this, SLOT(slotOpenFileQuick()));
    
	setWindowTitle(tr("Читатель BOM-файлов"));
}

void MainWindow::slotOpenFileDialog()
{
	file_name = QFileDialog::getOpenFileName(this,
							 tr("Открыть BOM-файл"),
							 root_path,
							 tr("BOM-файлы (*.bom);;Текстовые файлы (*.txt);;Все файлы (*)"));
	
	setCurrentPath(file_name);
	parseBom(file_name);
}


void MainWindow::slotOpenFileQuick()
{
  QFileInfo fi;
  
	file_name = edt_path->text();
	fi.setFile(file_name);
	if(!fi.exists())
	{
		QMessageBox::warning(this, tr("Предупреждение"),
                   tr("Файл не найден"),
                   QMessageBox::Ok);
		return;
	}
	setCurrentPath(file_name);
	parseBom(file_name);
}

void MainWindow::setCurrentPath(QString f_name)
{
  QFileInfo fi;

	if(f_name.isEmpty()) return;
	
	edt_path->setText(f_name);
	fi.setFile(f_name);
	root_path = fi.absolutePath();

qDebug() << "File:" << f_name;
qDebug() << "Path:" << root_path;
}

void MainWindow::parseBom(QString f_name)
{
  BomParser	parser(f_name);
	
	parser.setDelimiter(edt_delim->text());
	parser.parse();
}


