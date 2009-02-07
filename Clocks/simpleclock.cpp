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
#include <QTimer>

#include "simpleclock.h"

SimpleClock::SimpleClock( QGraphicsItem * parent ) :
  AbstractClock( parent )
{
    m_shadow = new QGraphicsPixmapItem( QPixmap( "./images/simpleclock_shadow.png" ) );
    m_renderer = new QSvgRenderer( QString("./images/simpleclock.svg") );
}

QRectF SimpleClock::boundingRect() const
{
    return QRectF( 0, 0, 600, 600 );
}

void SimpleClock::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setOpacity( m_opacity );
    m_renderer->render( painter, "white_bg", boundingRect() );

    static const QPoint hourHand[5] = {
        QPoint(4, 2),
        QPoint(4, 12),
        QPoint(-4, 12),
        QPoint(-4, 2),
        QPoint(0, -40)
    };

    static const QPoint minuteHand[5] = {
        QPoint(4, 2),
        QPoint(4, 16),
        QPoint(-4, 16),
        QPoint(-4, 2),
        QPoint(0, -80)
    };

    static const QPoint secondHand[2] = {
        QPoint(0, 16),
        QPoint(0, -80)
    };

    const QColor hourColor( Qt::red );
    const QColor minuteColor( Qt::red );

    QLinearGradient gradient( QPointF(3,2), QPointF(-3,2) );
    gradient.setColorAt(0, QColor( 255, 0, 0 ) );
    gradient.setColorAt(1, QColor( 125, 0, 0) );

    int side = qMin(boundingRect().width(), boundingRect().height());
    QTime time = QTime::currentTime();

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(boundingRect().width() / 2, boundingRect().height() / 2);
    painter->scale(side / 200.0, side / 200.0);

    painter->setPen(Qt::NoPen);
    painter->setBrush( gradient );

    painter->save();
    painter->rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter->drawConvexPolygon(hourHand, 5);
    painter->restore();

    QPen pen( Qt::SolidLine );
    pen.setWidth( 4 );
    painter->setPen( pen );

    for (int i = 0; i < 12; ++i) {
        painter->drawLine(82, 0, 90, 0);
        painter->rotate(30.0);
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush( gradient );

    painter->save();
    painter->rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter->drawConvexPolygon(minuteHand, 5);
    painter->restore();

    painter->setPen( Qt::black );
    painter->setBrush(Qt::NoBrush);

    painter->save();
    painter->rotate(6.0 * (time.second()));
    painter->drawConvexPolygon(secondHand, 2);
    painter->restore();

    painter->setPen(Qt::gray);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter->drawLine(84, 0, 86   , 0);
        painter->rotate(6.0);
    }

    painter->setPen( Qt::NoPen );
    painter->setBrush( QColor(125,0,0) );
    painter->drawEllipse( -1,-1,2,2 );

    painter->restore();

    m_shadow->paint( painter, option, widget );

    m_renderer->render( painter, "rings", boundingRect() );
    m_renderer->render( painter, "glass", m_renderer->boundsOnElement("glass") );
}
