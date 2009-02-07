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

#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include <QGraphicsSvgItem>
class QGraphicsPixmapItem;
class QTimeLine;

class ButtonItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    ButtonItem( QPixmap pixmap, QPixmap glow, QPixmap shadow, QGraphicsItem* parent = 0 );

    QRectF boundingRect() const;
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

signals:
    void clicked();

public slots:
    void updateOpacity( int opacity );
    void fadeIn();
    void fadeOut();

protected:
    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
    void mousePressEvent ( QGraphicsSceneMouseEvent * event );

private:
    qreal m_opacity;
    QTimeLine* m_timeLine;
    QGraphicsPixmapItem* m_button;
    QGraphicsPixmapItem* m_glow;
    QGraphicsPixmapItem* m_shadow;
};

#endif // BUTTONITEM_H
