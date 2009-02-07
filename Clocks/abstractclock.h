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

#ifndef ABSTRACTCLOCK_H
#define ABSTRACTCLOCK_H

#include <QGraphicsItem>

class QTimeLine;
class QTimer;
class QRectF;

class AbstractClock : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    AbstractClock( QGraphicsItem * parent = 0 );
    virtual ~AbstractClock();

    QRectF boundingRect() const;
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

public slots:
    void updateOpacity( int opacity );
    virtual void updateAnimationValues( int value );
    void fadeIn();
    void fadeOut();
    void repaint();

protected:
    qreal m_opacity;
    QTimeLine* m_timeLine;
    QTimeLine* m_animationTimeLine;

    bool m_hidden;
    QTimer* m_timer;
};

#endif
