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

#include "digitalclock.h"
#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>
#include <QTime>
#include <QDebug>

DigitalClock::DigitalClock( QGraphicsItem * parent ) : AbstractClock( parent ),
    num_0( QPixmap( "./images/digital_0.png") ),
    num_1( QPixmap( "./images/digital_1.png") ),
    num_2( QPixmap( "./images/digital_2.png") ),
    num_3( QPixmap( "./images/digital_3.png") ),
    num_4( QPixmap( "./images/digital_4.png") ),
    num_5( QPixmap( "./images/digital_5.png") ),
    num_6( QPixmap( "./images/digital_6.png") ),
    num_7( QPixmap( "./images/digital_7.png") ),
    num_8( QPixmap( "./images/digital_8.png") ),
    num_9( QPixmap( "./images/digital_9.png") ),
    m_dots( QPixmap( "./images/dots.png") ),
    m_empty( QPixmap() )
{
    m_slice = new QGraphicsPixmapItem( QPixmap( "./images/slice.png" ) );
}

QRectF DigitalClock::boundingRect() const
{
    return QRectF( 0, 0, 920, 600 );
}

QGraphicsPixmapItem* DigitalClock::mapDigit( uint digit )
{
    Q_ASSERT( digit >= 0 && digit <= 9 );
    switch( digit )
    {
        case 0: return &num_0; break;
        case 1: return &num_1; break;
        case 2: return &num_2; break;
        case 3: return &num_3; break;
        case 4: return &num_4; break;
        case 5: return &num_5; break;
        case 6: return &num_6; break;
        case 7: return &num_7; break;
        case 8: return &num_8; break;
        case 9: return &num_9; break;

        default: Q_ASSERT(false); break;
    }
    return &num_0;
}

QList<QGraphicsPixmapItem*> DigitalClock::getNumber( int number, bool isHour )
{
    QList<QGraphicsPixmapItem*> result;

    const int one = number % 10;
    const int ten = ( number - one ) / 10;

    if( isHour && number < 10 )
        result.append( &m_empty );
    else if ( isHour && number >= 10 || !isHour )
        result.append( mapDigit( ten ) );
    result.append( mapDigit( one ) );
    return result;
}

static inline void mirrorImage(QPainter* painter, const QGraphicsPixmapItem* img)
{
    QImage tmpImage = img->pixmap().toImage();
    tmpImage = tmpImage.mirrored(0,1);

    QPoint p1, p2;
    p2.setY(tmpImage.height());

    QLinearGradient gradient(p1, p2);
    gradient.setColorAt(0, QColor(0, 0, 0, 100));
    gradient.setColorAt(0.5, Qt::transparent);
    gradient.setColorAt(1, Qt::transparent);

    QPainter p(&tmpImage);
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(0, 0, tmpImage.width(), tmpImage.height(), gradient);
    p.end();

    painter->save();
    QPixmap mirror( QPixmap::fromImage( tmpImage ) );
    painter->setBrush( mirror );
    painter->setOpacity( 0.5 );
    painter->translate( img->boundingRect().x(), img->boundingRect().height() - 60 );
    painter->drawRect( img->boundingRect() );
    painter->restore();
}


void DigitalClock::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    painter->setRenderHint( QPainter::Antialiasing );
    painter->setOpacity( m_opacity );

    m_slice->paint( painter, option, widget );

    // some adjustment
    painter->scale( 0.9, 0.9 );
    painter->translate( 50, 0 );

    const int x_offset = num_0.boundingRect().width() + 10;
    painter->save();
    painter->scale( 0.7, 0.7 );
    painter->setPen( Qt::NoPen );

    QTime time = QTime::currentTime();

    QList<QGraphicsPixmapItem*> hour = getNumber( time.hour(), true );
    hour[0]->paint( painter, option, widget );
    mirrorImage( painter, hour[0] );

    painter->translate( x_offset, 0 );
    hour[1]->paint( painter, option, widget );
    mirrorImage( painter, hour[1] );

    painter->translate( x_offset, 0 );
    if( time.second() % 2 == 1 ) {
        m_dots.paint( painter, option, widget );
        mirrorImage( painter, &m_dots );
    }
    painter->translate( m_dots.boundingRect().width() + 20, 0 );

    QList<QGraphicsPixmapItem*> minute = getNumber( time.minute(), false );
    minute[0]->paint( painter, option, widget );
    mirrorImage( painter, minute[0] );

    painter->translate( x_offset, 0 );
    minute[1]->paint( painter, option, widget );
    mirrorImage( painter, minute[1] );

    painter->restore();
}
