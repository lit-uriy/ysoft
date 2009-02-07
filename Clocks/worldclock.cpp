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

#include "worldclock.h"

WorldClock::WorldClock( QGraphicsItem * parent )
    : AbstractClock( parent )
{
    m_globe = new QGraphicsPixmapItem( QPixmap( "./images/globe.png" ) );
    m_worlds = new QGraphicsPixmapItem( QPixmap( "./images/worlds.png" ) );
}

QRectF WorldClock::boundingRect() const
{
    return QRectF( 0, 0, 600, 600 );
}

void WorldClock::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->setOpacity( m_opacity );
    painter->setRenderHint(QPainter::Antialiasing);

    painter->save();
    painter->translate( 0, 25 );
    m_worlds->paint( painter, option, widget );
    painter->restore();

    m_globe->paint( painter, option, widget );

    const uint pointerWidth = 2;

    static const QPoint minuteHand[3] = {
        QPoint(pointerWidth, -76),
        QPoint(-pointerWidth, -76),
        QPoint(0, -100)
    };

    static const QPoint secondHand[4] = {
        QPoint(-3, -92),
        QPoint(3, -92),
        QPoint(3, -96),
        QPoint(-3, -96)
    };

    QColor hourColor( Qt::white );
    QColor minuteColor( Qt::white );

    int side = qMin(boundingRect().width(), boundingRect().height());
    QTime time = QTime::currentTime();

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(boundingRect().width() / 2, boundingRect().height() / 2);
    painter->scale(side / 200.0, side / 200.0);

    painter->setPen(Qt::NoPen);
    painter->setBrush(hourColor);

    painter->save();
    painter->rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter->drawEllipse( -6, -86, 12, 12 );
    painter->restore();

    painter->setPen(Qt::white);

    for (int i = 0; i < 12; ++i) {
        painter->drawLine(88, 0, 96, 0);
        painter->rotate(30.0);
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);

    painter->save();
    painter->rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter->drawConvexPolygon(minuteHand, 3);
    painter->restore();

    painter->setPen( Qt::white );
    painter->setBrush(Qt::white);

    painter->save();
    painter->setOpacity( 0.2 );
    painter->rotate( 6.0 * ( time.second() - 3 ) );
    painter->drawConvexPolygon(secondHand, 4);
    painter->restore();

    painter->save();
    painter->setOpacity( 0.4 );
    painter->rotate( 6.0 * ( time.second() - 2 ) );
    painter->drawConvexPolygon(secondHand, 4);
    painter->restore();

    painter->save();
    painter->setOpacity( 0.6 );
    painter->rotate( 6.0 * ( time.second() - 2 ) );
    painter->drawConvexPolygon(secondHand, 4);
    painter->restore();

    painter->save();
    painter->setOpacity( 0.8 );
    painter->rotate( 6.0 * ( time.second() - 1 ) );
    painter->drawConvexPolygon(secondHand, 4);
    painter->restore();

    painter->save();
    painter->setOpacity( 1.0 );
    painter->rotate( 6.0 * time.second() );
    painter->setBrush( Qt::NoBrush );
    painter->drawEllipse(-4,-98,8,8);
    painter->restore();

    painter->setPen(Qt::white);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter->drawLine(92, 0, 96, 0);
        painter->rotate(6.0);
    }
    painter->restore();
}
