/*!
 *	\file mainwindow.h
 *	\brief Интерфейс класса "Главного окна программы".
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "widget.h"

class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
class MdiChild;
class QSignalMapper;
class QDir;
class QStringList;
class QFile;



/*!
 *	\class MainWindow
 *	\brief Класс главного окна программы.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow();
	~MainWindow();
/*
protected:

    void closeEvent(QCloseEvent *event);
*/
private slots:

//    void newFile();
//    void open();
	void SlotOpenDir();
	void SlotOpenDb();
	void SlotOpenTs();
/*    void save();
    void saveAs();
	void login();
	void logout();
	void loginAnonymous();
    void cut();
    void copy();
    void paste();
    void about();
    void updateMenus();
    void updateWindowMenu();
    MdiChild *createMdiChild();
    void switchLayoutDirection();
    void setActiveSubWindow(QWidget *window);
*/
private:


    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
/*	
    void readSettings();
    void writeSettings();
*/
	void ReadFilesFromDir();
	void ReadTsFile(QFile *tsfile);

	Child	*child;
/*	
    MdiChild *activeMdiChild();
    QMdiSubWindow *findMdiChild(const QString &fileName);
	
    QMdiArea 		*mdiArea;
    QSignalMapper	*windowMapper;
	
	int	userID;
*/	
	QDir	*dirOpen;


    // Меню
	QMenu	*menuFile;
/*	
    QMenu	*menuEdit;
	QMenu	*menuView;
	QMenu	*menuOperator;
	QMenu	*menuSetting;
    QMenu	*menuWindow;
    QMenu	*menuHelp;
*/	
	// Панели инструментов
    QToolBar *ToolBarFile;
//    QToolBar *ToolBarEdit;
	
	// Действия
		// Файл
//    QAction	*newAct;
    QAction	*actOpenDir;
	QAction	*actOpenDb;
	QAction	*actOpenTs;
    //QAction *saveAct;
    //QAction *saveAsAct;
    QAction *actExit;	
/*	
	QAction *actLogin;
	QAction *actLogout;	
	

    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *separatorAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
*/
};

#endif
