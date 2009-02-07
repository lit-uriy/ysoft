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

#ifndef CLOCKMANAGER_H
#define CLOCKMANAGER_H

#include <QtGui/QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsSvgItem>
#include <QList>
#include <QGraphicsScene>

#include "abstractclock.h"
#include "buttonitem.h"

class ClockManager : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_DISABLE_COPY(ClockManager)

public:
    explicit ClockManager(QGraphicsScene& scene, QGraphicsItem *parent = 0);
    virtual ~ClockManager();

    virtual QRectF boundingRect() const;
    virtual void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

    void updateClockPositions();

protected:
    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );

private slots:
    void turnLeft();
    void turnRight();

private:
    void addClock( AbstractClock* clock, QGraphicsScene& scene );

    ButtonItem leftButton;
    ButtonItem rightButton;
    QGraphicsPixmapItem middle;
    QList<AbstractClock*> m_clocks;
    uint m_currentPos;
};

#endif // CLOCKMANAGER_H
