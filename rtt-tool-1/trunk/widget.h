/*!
 \file mdichild.h
 \brief Интерфейс класса "Дочернего окна программы".
 */
#ifndef WIDGET_H
#define WIDGET_H

#include <QListWidget>


/*!
 *	\class MdiChild
 *	\brief Класс дочернего окна.
 */
class Child : public QListWidget
{
    Q_OBJECT

public:
    Child(QListWidget *p_parent=0);
/*
    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile() { return curFile; }
*/
protected:
/*
    void closeEvent(QCloseEvent *event);
*/
private slots:
   // void documentWasModified();

private:
/*
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;
    bool isUntitled;
*/
};

#endif // WIDGET_H
