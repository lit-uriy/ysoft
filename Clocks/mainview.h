/**
 *   Copyright 2008 by Thomas Moenicke < tm at php-qt.org >
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QGraphicsView>

class QGraphicsItem;
class QGraphicsPixmapitem;
class ClockManager;

class MainView : public QGraphicsView
{
public:
    MainView( QGraphicsScene * scene, QWidget * parent = 0  );

    void setClockManager( ClockManager* manager );
    void setBackground( QGraphicsPixmapItem* background );
    void triggerElementPositioning();

protected:
    void mouseDoubleClickEvent ( QMouseEvent * event );
    void resizeEvent ( QResizeEvent * event );

private:
    ClockManager* m_manager;
    QGraphicsPixmapItem* m_background;
};

#endif // MAINVIEW_H
