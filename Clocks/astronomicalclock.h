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

#ifndef ASTRONOMICALCLOCK_H
#define ASTRONOMICALCLOCK_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

#include "abstractclock.h"

class QRectF;
class QPixmap;

class AstronomicalClock : public AbstractClock
{
public:
    AstronomicalClock( QGraphicsItem * parent = 0 );
    virtual ~AstronomicalClock();

    QRectF boundingRect() const;
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

public slots:
    virtual void updateAnimationValues( int value );

protected:
    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );

private:
    QGraphicsPixmapItem* m_bg;

    QGraphicsPixmapItem* m_zodiac;
    uint m_zodiacPos;

    QGraphicsPixmapItem* m_pdt;
    int m_pdtPos;

    QGraphicsPixmapItem* m_act;
    int m_actPos;

    QGraphicsPixmapItem* m_sun;
    int m_sunPos;

    QGraphicsPixmapItem* m_shadow;
    qreal m_shadowOpacity;
};

#endif
