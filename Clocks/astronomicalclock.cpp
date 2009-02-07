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

#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>
#include <QTime>
#include <QPixmap>
#include <QDebug>
#include <QTimeLine>
#include <QTimer>
#include <QDesktopWidget>
#include <QGraphicsSceneHoverEvent>

#include "astronomicalclock.h"

AstronomicalClock::AstronomicalClock( QGraphicsItem * parent ) :
    AbstractClock( parent ),
    m_zodiacPos( 0 ),
    m_pdtPos( 0 ),
    m_actPos(0),
    m_sunPos( 0 ),
    m_shadowOpacity( 0.0 )
{
    setAcceptHoverEvents( true );

    m_bg = new QGraphicsPixmapItem( QPixmap( "./images/astro_bg.png" ) ),
    m_zodiac = new QGraphicsPixmapItem( QPixmap( "./images/astro_zodiac.png" ) ),
    m_pdt = new QGraphicsPixmapItem( QPixmap( "./images/astro_present_day_time.png" ) ),
    m_act = new QGraphicsPixmapItem( QPixmap( "./images/astro_ancient_czech_time.png" ) ),

    m_sun = new QGraphicsPixmapItem( QPixmap( "./images/astro_sun.png" ) );
    m_shadow = new QGraphicsPixmapItem( QPixmap( "./images/astro_shadow.png" ) );
    m_timer->stop();
}

AstronomicalClock::~AstronomicalClock()
{
    delete m_sun;
    m_shadowOpacity = 0;
}

QRectF AstronomicalClock::boundingRect() const
{
    return QRectF( 0, 0, 600, 600 );
}

void AstronomicalClock::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->setOpacity( m_opacity );
    painter->setRenderHint(QPainter::Antialiasing);

    // bg
    painter->save();
    m_bg->paint( painter, option, widget );
    painter->restore();

    // shadow
    painter->save();
    painter->setOpacity( m_shadowOpacity );
    m_shadow->paint( painter, option, widget );
    painter->restore();

    // hand
    painter->save();
    painter->translate( boundingRect().center() );
    painter->rotate( 90.0 );
    painter->translate( -292, -12 );
    m_pdt->paint( painter, option, widget );
    painter->restore();

    // outer ring
    painter->save();
    const QPointF center = boundingRect().center();
    QMatrix m( matrix() );
    m.translate( center.x(), center.y() );
    m.rotate( -m_actPos );
    m.translate( -center.x(), -center.y() );
    painter->setMatrix( m );
    m_act->paint( painter, option, widget );
    painter->restore();

    // Zodiac
    painter->save();
    m = matrix();
    m.translate( -180, -180 ); // -110
    const uint offset = 180; // 110
    m.translate( center.x() + offset, center.y() + offset );
    m.rotate( m_zodiacPos*1.8 );
    m.translate( -center.x() + offset, -center.y() + offset );
    painter->setMatrix( m );
    m_zodiac->paint( painter, option, widget );
    painter->restore();

    // sun
    painter->save();
    painter->translate( boundingRect().center().x() - ( m_sun->boundingRect().width() / 2 ) , 200 + m_sunPos );
    painter->translate( 0, m_sunPos );
    m_sun->paint( painter, option, widget );
    painter->restore();
}

void AstronomicalClock::updateAnimationValues( int value )
{
    const qreal tmp = value;
    m_sunPos = -value / 2;
    m_shadowOpacity = tmp / 100;
    m_actPos = value;
    m_zodiacPos = value;
    update();
}

void AstronomicalClock::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    event->accept();
    m_animationTimeLine->start();
}
