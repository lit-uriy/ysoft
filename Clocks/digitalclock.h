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
#include "abstractclock.h"
class QRectF;
class QPixmap;

class DigitalClock : public AbstractClock
{
public:
    DigitalClock( QGraphicsItem * parent = 0 );

    QRectF boundingRect() const;
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
    QList<QGraphicsPixmapItem*> getNumber( int number, bool isHour = false );
    QGraphicsPixmapItem* mapDigit( uint dig );

    QGraphicsPixmapItem num_0;
    QGraphicsPixmapItem num_1;
    QGraphicsPixmapItem num_2;
    QGraphicsPixmapItem num_3;
    QGraphicsPixmapItem num_4;
    QGraphicsPixmapItem num_5;
    QGraphicsPixmapItem num_6;
    QGraphicsPixmapItem num_7;
    QGraphicsPixmapItem num_8;
    QGraphicsPixmapItem num_9;
    QGraphicsPixmapItem m_dots;
    QGraphicsPixmapItem m_empty;
    QGraphicsPixmapItem* m_slice;
};
