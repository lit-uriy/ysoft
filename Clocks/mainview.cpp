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

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDebug>

#include "mainview.h"
#include "clockmanager.h"

MainView::MainView( QGraphicsScene * scene, QWidget * parent )
    : QGraphicsView( scene, parent )
{
    setRenderHint( QPainter::HighQualityAntialiasing );
}

void MainView::mouseDoubleClickEvent ( QMouseEvent * event )
{
    event->accept();

#ifdef DOUBLECLICK_ON_EXIT
    windowState() == Qt::WindowFullScreen
            ? setWindowState( Qt::WindowMaximized )
            : setWindowState( Qt::WindowFullScreen );

    triggerElementPositioning();
    QGraphicsView::mouseDoubleClickEvent(event);
#endif

}

void MainView::resizeEvent ( QResizeEvent * event )
{
    event->accept();
    triggerElementPositioning();
}

void MainView::triggerElementPositioning()
{
    Q_ASSERT( m_manager );

    // TODO on an external screen, this still tries to focus on the main screen
    QRectF centerRect = m_manager->boundingRect();
    centerRect.moveCenter( frameGeometry().center() );
    m_manager->setPos( centerRect.x(), centerRect.y() );

    const int height = frameGeometry().height();
    const int y = height / 100 * 75;
    m_manager->updateClockPositions();
    m_manager->setPos( centerRect.x(), y );

    m_background->setPos(0,0);
}

void MainView::setClockManager( ClockManager* manager )
{
    m_manager = manager;
}

void MainView::setBackground( QGraphicsPixmapItem* background )
{
    m_background = background;
}
