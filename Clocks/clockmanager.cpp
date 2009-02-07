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
 *   along with this program. If not, see <http./images//www.gnu.org/licenses/>.
 **/

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSlider>
#include <QTimeLine>
#include <QTransform>
#include <QDesktopWidget>

#include "clockmanager.h"
#include "digitalclock.h"
#include "simpleclock.h"
#include "worldclock.h"
#include "astronomicalclock.h"

ClockManager::ClockManager(QGraphicsScene& scene, QGraphicsItem *parent) : QObject(),  QGraphicsItem( parent ),
    leftButton( QPixmap("./images/arrowLeft.png"), QPixmap("./images/glowLeft.png"), QPixmap("./images/shadowLeft.png"), this ),
    rightButton( QPixmap("./images/arrowRight.png"), QPixmap("./images/glowRight.png"), QPixmap("./images/shadowRight.png"), this ),
    middle( QPixmap("./images/middle.png") ),
    m_currentPos( 0 )
{
    rightButton.setPos( 425, 0 );
    connect( &leftButton, SIGNAL( clicked() ), this, SLOT( turnLeft() ) );
    connect( &rightButton, SIGNAL( clicked() ), this, SLOT( turnRight() ) );

    setAcceptHoverEvents( true );

    const QPointF scenePoint = mapFromScene( boundingRect().x(), boundingRect().y() );

    addClock( new SimpleClock, scene );
    addClock( new DigitalClock, scene );
    addClock( new WorldClock, scene );
    addClock( new AstronomicalClock(), scene );

    m_clocks[ 0 ]->show();
    m_clocks[ 0 ]->fadeIn();
    updateClockPositions();
}

ClockManager::~ClockManager()
{
}

void ClockManager::addClock( AbstractClock* clock, QGraphicsScene& scene )
{
    m_clocks.append( clock );
    scene.addItem( clock );
    clock->hide();
}

QRectF ClockManager::boundingRect() const
{
    return QRectF( 0,0,500,75 );
}

void ClockManager::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    middle.paint( painter, option, widget );
}

void ClockManager::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    QGraphicsItem::hoverEnterEvent(event);
}

void ClockManager::turnLeft()
{
    if( m_currentPos <= 0 )
    {
        m_currentPos = 0;
        return;
    }
    if( m_currentPos > 0 )
    {
        m_clocks[ m_currentPos ]->fadeOut();
        m_currentPos--;
        m_clocks[ m_currentPos ]->fadeIn();
    }
}

void ClockManager::turnRight()
{
    const uint last = m_clocks.size() - 1;

    if( m_currentPos > last )
    {
        m_currentPos = last;
        return;
    }
    if( last == 1 )
        return;
    if( m_currentPos < last )
    {
        m_clocks[ m_currentPos ]->fadeOut();
        m_currentPos++;
        m_clocks[ m_currentPos ]->fadeIn();
    }
}

void ClockManager::updateClockPositions()
{
    const QRectF centerRect;
    const QRectF screenRect( QDesktopWidget().screenGeometry() );

    foreach( QGraphicsItem* clock, m_clocks ) {
        QRectF centerRect = clock->boundingRect();
        centerRect.moveCenter( screenRect.center() );
        clock->setZValue(2);
 
        const qreal ratio = 0.5;

        clock->setTransform(
        QTransform().translate(
                screenRect.center().x() - clock->matrix().mapRect( centerRect ).width()/2,
                screenRect.center().y() - clock->matrix().mapRect( clock->boundingRect() ).height()/2 ).scale(ratio,ratio) );
    }
}
