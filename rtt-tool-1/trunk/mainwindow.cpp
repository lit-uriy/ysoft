/*!
 *	\file mainwindow.cpp
 *	\brief Реализация класса "Главного окна программы".
 */

#include <QtGui>

#include "mainwindow.h"


MainWindow::MainWindow()
{

  
	child = new Child;

	setCentralWidget(child);
	dirOpen = new QDir;
/*
    mdiArea = new QMdiArea;
    
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)), this, SLOT(updateMenus()));
    
	windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget *)), this, SLOT(setActiveSubWindow(QWidget *)));
*/
    createActions();	// Создаем действия
    createMenus();		// Создаем меню
    createToolBars();	// Создаем панель инструментов
    createStatusBar();	// Создаем панель статуса

	//updateMenus();		// Обновляем меню
    //readSettings();		// Читаем настройки (из реестра)
	

    setWindowTitle(tr("Список файлов"));
}

MainWindow::~MainWindow()
{

	delete child;
}



/*=====================================================================
				Создание действий
  ===================================================================*/
void MainWindow::createActions()
{
	// Меню файл
	/*
    newAct = new QAction(QIcon(":/images/new.png"), tr("&Новый"), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Создать новый файл"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));
	*/
    //actOpenDir = new QAction(QIcon(":/images/open.png"), tr("Открыть &каталог..."), this);
	actOpenDir = new QAction(QIcon(":/images/docFolder.png"), tr("Открыть &каталог..."), this);
    actOpenDir->setShortcut(tr("Ctrl+K"));
    actOpenDir->setStatusTip(tr("Открыть каталог с html файлами"));
    connect(actOpenDir, SIGNAL(triggered()), this, SLOT(SlotOpenDir()));
	
    //actOpenDb = new QAction(QIcon(":/images/open.png"), tr("Открыть &БД..."), this);
	actOpenDb = new QAction(QIcon(":/images/db.png"), tr("Открыть &БД..."), this);
    actOpenDb->setShortcut(tr("Ctrl+B"));
    actOpenDb->setStatusTip(tr("Открыть базу данных"));
    connect(actOpenDb, SIGNAL(triggered()), this, SLOT(SlotOpenDb()));	
	
    //actOpenTs = new QAction(QIcon(":/images/open.png"), tr("Открыть &TS-файл..."), this);
	actOpenTs = new QAction(QIcon(":/images/doc.png"), tr("Открыть &TS-файл..."), this);
    actOpenTs->setShortcut(tr("Ctrl+T"));
    actOpenTs->setStatusTip(tr("Открыть TS-файл"));
    connect(actOpenTs, SIGNAL(triggered()), this, SLOT(SlotOpenTs()));	
	/*
    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Сохранить"), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setStatusTip(tr("Сохранить документ на диск"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Сохранить &как..."), this);
    saveAsAct->setStatusTip(tr("Сохранить документ под другим именем"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
	*/
    actExit = new QAction(tr("В&ыход"), this);
    actExit->setShortcut(tr("Ctrl+Q"));
    actExit->setStatusTip(tr("Выход из программы"));
    connect(actExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

	// Меню Правка
/*    cutAct = new QAction(QIcon(":/images/cut.png"), tr("&Вырезать"), this);
    cutAct->setShortcut(tr("Ctrl+X"));
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Копировать"), this);
    copyAct->setShortcut(tr("Ctrl+C"));
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/paste.png"), tr("Вст&авить"), this);
    pasteAct->setShortcut(tr("Ctrl+V"));
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

	// Меню Оператор
    actLogin = new QAction(tr("Войти..."), this);
    actLogin->setStatusTip(tr("Войти в систему с определенным именем"));
    connect(actLogin, SIGNAL(triggered()), this, SLOT(login()));
	
	actLogout = new QAction(tr("Выйти"), this);
    actLogout->setStatusTip(tr("Выйти из системы"));
    connect(actLogout, SIGNAL(triggered()), this, SLOT(logout()));
	
	// Меню Окна
    closeAct = new QAction(tr("&Закрыть"), this);
    closeAct->setShortcut(tr("Ctrl+F4"));
    closeAct->setStatusTip(tr("Закрыть активное окно"));
    connect(closeAct, SIGNAL(triggered()),
            mdiArea, SLOT(closeActiveSubWindow()));

    closeAllAct = new QAction(tr("Закрыть все"), this);
    closeAllAct->setStatusTip(tr("Закрыть все окна"));
    connect(closeAllAct, SIGNAL(triggered()),
            mdiArea, SLOT(closeAllSubWindows()));

    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));
    connect(tileAct, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));

    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));
    connect(cascadeAct, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));

    nextAct = new QAction(tr("Ne&xt"), this);
    nextAct->setStatusTip(tr("Move the focus to the next window"));
    connect(nextAct, SIGNAL(triggered()),
            mdiArea, SLOT(activateNextSubWindow()));

    previousAct = new QAction(tr("Pre&vious"), this);
    previousAct->setStatusTip(tr("Move the focus to the previous "
                                 "window"));
    connect(previousAct, SIGNAL(triggered()),
            mdiArea, SLOT(activatePreviousSubWindow()));

    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);

	// Меню Справка
    aboutAct = new QAction(tr("&О программе"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("О библиотеке &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
*/
}

/*=====================================================================
				Создание Меню
  ===================================================================*/
void MainWindow::createMenus()
{
    // Меню файл
	menuFile = menuBar()->addMenu(tr("&Файл"));
//    menuFile->addAction(newAct);
    menuFile->addAction(actOpenDir);
    menuFile->addAction(actOpenDb);
    menuFile->addAction(actOpenTs);
	menuFile->addSeparator();
	menuFile->addAction(actExit);
	/*
	// Меню Правка
    menuEdit = menuBar()->addMenu(tr("&Правка"));
    menuEdit->addAction(cutAct);
    menuEdit->addAction(copyAct);
    menuEdit->addAction(pasteAct);
	
	// Меню Вид
	//menuView = menuBar()->addMenu(tr("&Вид"));
	
	// Меню Оператор
	menuOperator = menuBar()->addMenu(tr("Опе&ратор"));
	menuOperator->addAction(actLogin);
	menuOperator->addAction(actLogout);
	
 	// Меню Настройка
    //menuSetting = menuBar()->addMenu(tr("&Настройка"));
    //settingMenu->addAction(cutAct);
    //settingMenu->addAction(copyAct);
    //settingMenu->addAction(pasteAct);

	// Меню окно
	menuWindow = menuBar()->addMenu(tr("&Окно"));
    updateWindowMenu();
    connect(menuWindow, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    menuBar()->addSeparator();
	
	// Меню Справка
    menuHelp = menuBar()->addMenu(tr("&Справка"));
    menuHelp->addAction(aboutAct);
    menuHelp->addAction(aboutQtAct);
*/
}

/*=====================================================================
				Создание панели инструментов
  ===================================================================*/
void MainWindow::createToolBars()
{
    ToolBarFile = addToolBar(tr("Файл"));
    //ToolBarFile->addAction(newAct);
    ToolBarFile->addAction(actOpenDir);
    ToolBarFile->addAction(actOpenDb);
	ToolBarFile->addAction(actOpenTs);
/*
    ToolBarEdit = addToolBar(tr("Правка"));
    ToolBarEdit->addAction(cutAct);
    ToolBarEdit->addAction(copyAct);
    ToolBarEdit->addAction(pasteAct);
*/
}

/*=====================================================================
				Создание строки статуса
  ===================================================================*/
void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Готов"));
}




/*===================================================================
				Обновление меню
=====================================================================
void MainWindow::updateMenus()
{
  bool hasMdiChild;
  bool hasSelection;
  
	hasMdiChild = (activeMdiChild() != 0);
	hasSelection = (activeMdiChild() && activeMdiChild()->textCursor().hasSelection());
  
	switch(userID)
	{
		case UIDroot:
		{
			
		}
		case UIDadmin:
		{
			
		}
		case UIDnnn:
		{
			
		}
		case UIDeng:
		{
			
		}
		default:
		{
			
			saveAct->setEnabled(hasMdiChild);
			saveAsAct->setEnabled(hasMdiChild);
			pasteAct->setEnabled(hasMdiChild);
			closeAct->setEnabled(hasMdiChild);
			closeAllAct->setEnabled(hasMdiChild);
			tileAct->setEnabled(hasMdiChild);
			cascadeAct->setEnabled(hasMdiChild);
			nextAct->setEnabled(hasMdiChild);
			previousAct->setEnabled(hasMdiChild);
			separatorAct->setVisible(hasMdiChild);
			
			cutAct->setEnabled(hasSelection);
			copyAct->setEnabled(hasSelection);
		}
	}
	
	
}*/


/*===================================================================
				Обработка события closeEvent
=====================================================================
void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (activeMdiChild())
	{
        event->ignore();
		//QMessageBox::about(this, tr("MainWindow::closeEvent"), tr("activeMdiChild()==true"));
    }
	else
	{
		//QMessageBox::about(this, tr("MainWindow::closeEvent"), tr("activeMdiChild()==false"));
        writeSettings();
        event->accept();
    }
}*/




/*===================================================================
				
=====================================================================
void MainWindow::updateWindowMenu()
{
    menuWindow->clear();
    menuWindow->addAction(closeAct);
    menuWindow->addAction(closeAllAct);
    menuWindow->addSeparator();
    menuWindow->addAction(tileAct);
    menuWindow->addAction(cascadeAct);
    menuWindow->addSeparator();
    menuWindow->addAction(nextAct);
    menuWindow->addAction(previousAct);
    menuWindow->addAction(separatorAct);

    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    separatorAct->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); ++i) {
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i)->widget());
		
        QString text;
        if (i < 9)
		{
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->userFriendlyCurrentFile());
        }
		else
		{
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->userFriendlyCurrentFile());
        }
        QAction *action  = menuWindow->addAction(text);
        action->setCheckable(true);
        action ->setChecked(child == activeMdiChild());
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
}*/


/*=====================================================================
				Создание дочернего окна
  ===================================================================
MdiChild *MainWindow::createMdiChild()
{
    MdiChild *child = new MdiChild;
    mdiArea->addSubWindow(child);

    connect(child, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(child, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));

    return child;
}
*/



/*=====================================================================
				Обработка действий
  ===================================================================

//	Файл->Новый
void MainWindow::newFile()
{
    MdiChild *child = createMdiChild();
    child->newFile();
    child->show();
}
//	Файл->Открыть	
void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        QMdiSubWindow *existing = findMdiChild(fileName);
        if (existing) {
            mdiArea->setActiveSubWindow(existing);
            return;
        }

        MdiChild *child = createMdiChild();
        if (child->loadFile(fileName)) {
            statusBar()->showMessage(tr("Файл загружен"), 2000);
            child->show();
        } else {
            child->close();
        }
    }
}
*/
//	Файл->Открыть Каталог	
void MainWindow::SlotOpenDir()
{
  QFileDialog::Options	options;
  QString				caption;
  QString				dir;
  QString				filter;
  QString				selectedFilter;
	
	
	options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
	//options |= QFileDialog::DontUseNativeDialog;
	
	caption = tr("QFileDialog::getExistingDirectory()");
	
	if (dirOpen->path().isEmpty())
	{
		dir = QString();//tr();
	}
	else
	{
		dir = dirOpen->path();
	}
	
	QString dirname = QFileDialog::getExistingDirectory(this,
							 caption,
							 dir,
							 options);
	
	if (!dirname.isEmpty())
	{
		//QMessageBox::information(this, tr("Информация"), tr("Каталог пуст"));
		dirOpen->setPath(dirname);
		statusBar()->showMessage(dirname);
		ReadFilesFromDir();
	}
	else
	{
		statusBar()->showMessage(tr("Готов"));
	}
	
}

//	Файл->Открыть БД	
void MainWindow::SlotOpenDb()
{
/*
  QFileDialog::Options	options;
  QString				caption;
  QString				dir;
  QString				filter;
  QString				selectedFilter;
	
	
	options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
	//options |= QFileDialog::DontUseNativeDialog;
	
	caption = tr("QFileDialog::getExistingDirectory()");
	
	if (dirOpen->path().isEmpty())
	{
		dir = QString();//tr();
	}
	else
	{
		dir = dirOpen->path();
	}
	
	QString dirname = QFileDialog::getExistingDirectory(this,
							 caption,
							 dir,
							 options);
	
	if (!dirname.isEmpty())
	{
		//QMessageBox::information(this, tr("Информация"), tr("Каталог пуст"));
		dirOpen->setPath(dirname);
		statusBar()->showMessage(dirname);
		ReadFiles();
	}
	else
	{
		statusBar()->showMessage(tr("Готов"));
	}
*/	
}


//	Файл->Открыть TS-файл	
void MainWindow::SlotOpenTs()
{
/*
  QFileDialog::Options	options;
  QString				caption;
  QString				dir;
  QString				filter;
  QString				selectedFilter;
	
	
	options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
	//options |= QFileDialog::DontUseNativeDialog;
	
	caption = tr("QFileDialog::getExistingDirectory()");
	
	if (dirOpen->path().isEmpty())
	{
		dir = QString();//tr();
	}
	else
	{
		dir = dirOpen->path();
	}
	
	QString dirname = QFileDialog::getExistingDirectory(this,
							 caption,
							 dir,
							 options);
	
	if (!dirname.isEmpty())
	{
		//QMessageBox::information(this, tr("Информация"), tr("Каталог пуст"));
		dirOpen->setPath(dirname);
		statusBar()->showMessage(dirname);
		ReadFiles();
	}
	else
	{
		statusBar()->showMessage(tr("Готов"));
	}
*/	
}


/*
//	Файл->Сохранить	
void MainWindow::save()
{
    if (activeMdiChild() && activeMdiChild()->save())
        statusBar()->showMessage(tr("Файл сохранен"), 2000);
}
//	Файл->Сохранить как	
void MainWindow::saveAs()
{
    if (activeMdiChild() && activeMdiChild()->saveAs())
        statusBar()->showMessage(tr("Файл сохранен"), 2000);
}

//	Правка->Вырезать	
void MainWindow::cut()
{
    if (activeMdiChild())
        activeMdiChild()->cut();
}
//	Правка->Копировать	
void MainWindow::copy()
{
    if (activeMdiChild())
        activeMdiChild()->copy();
}
//	Правка->Вставить	
void MainWindow::paste()
{
    if (activeMdiChild())
        activeMdiChild()->paste();
}

//	Оператор->Вход	
void MainWindow::login()
{
   QMessageBox::about(this, tr("Вход"),
            tr("Здесь должен быть диалог для ввода <B>Имени пользователя</B> "
               "и П<B>ароля</B>"));
}
//	Оператор->Выход	
void MainWindow::logout()
{
   QMessageBox::about(this, tr("Выход"),
            tr("Вы вышли из системы"));
}
//	Справка->О программе	
void MainWindow::about()
{
   QMessageBox::about(this, tr("О программе"),
            tr("The <b>MDI</b> example demonstrates how to write multiple "
               "document interface applications using Qt."));
}
*/

/*=====================================================================
				Чтение содержимого каталога
  ===================================================================*/
void MainWindow::ReadFilesFromDir()
{
  QStringList		filelist;
  QDir::Filters		filtres;
  QStringList		nameFilters;
  QDir::SortFlags	sort;

	filtres = QDir::Files;
	sort = QDir::Name | QDir::IgnoreCase | QDir::LocaleAware;
	nameFilters << "*.html" << "*.ts";
	
	filelist = dirOpen->entryList(nameFilters, filtres, sort);
	
	child->clear();
	child->addItems(filelist);
}

/*=====================================================================
				Чтение настроек
  ===================================================================
void MainWindow::readSettings()
{
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos);
    resize(size);
}*/
/*=====================================================================
				Запись настроек
  ===================================================================
void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());	// здесь касяк, надо нетолько размер запоминать но и состояние развернуто или нет
}

MdiChild *MainWindow::activeMdiChild()
{
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0;
}

QMdiSubWindow *MainWindow::findMdiChild(const QString &fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    foreach (QMdiSubWindow *window, mdiArea->subWindowList()) {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return 0;
}

void MainWindow::switchLayoutDirection()
{
    if (layoutDirection() == Qt::LeftToRight)
        qApp->setLayoutDirection(Qt::RightToLeft);
    else
        qApp->setLayoutDirection(Qt::LeftToRight);
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}*/
