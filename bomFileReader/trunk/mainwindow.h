/*!
 *	\file	mainwindow.h
 *	\brief	Интерфейс класса "MainWindow".
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

/**	Класс MainWindow является ... .
 * 	Этот класс ...
 */
class MainWindow : public QWidget, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *p_parent = 0);

private slots:
	void slotOpenFileDialog();
	void slotOpenFileQuick();

private:
	void setCurrentPath(QString f_name);
	void parseBom(QString f_name);


private:
	QString file_name;
	QString root_path;
};

#endif //MAINWINDOW_H

