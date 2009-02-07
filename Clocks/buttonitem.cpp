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

#include <QTimeLine>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>

#include "buttonitem.h"

ButtonItem::ButtonItem( QPixmap pixmap, QPixmap glow, QPixmap shadow, QGraphicsItem * parent )
    : QObject(), QGraphicsItem( parent ),
      m_opacity(0)
{
    m_button = new QGraphicsPixmapItem( pixmap );
    m_glow = new QGraphicsPixmapItem( glow );
    m_shadow = new QGraphicsPixmapItem( shadow );

    m_timeLine = new QTimeLine(1000, this);
    m_timeLine->setFrameRange(0, 100);
    m_timeLine->setCurveShape( QTimeLine::EaseInOutCurve );
    m_timeLine->setDirection( QTimeLine::Forward );
    QObject::connect( m_timeLine, SIGNAL( frameChanged(int) ), this, SLOT( updateOpacity(int) ) );

    setAcceptHoverEvents( true );
}

QRectF ButtonItem::boundingRect() const
{
    return QRectF( 0,0, 75,75 );
}

void ButtonItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    m_shadow->paint( painter, option, widget );
    painter->setOpacity( m_opacity );
    m_glow->paint( painter, option, widget );
    painter->setOpacity( 1 );
    m_button->paint( painter, option, widget );
}

void ButtonItem::updateOpacity( int opacity )
{
    const qreal opacity_ = opacity;
    m_opacity = opacity_ / 100;
    update();
}

void ButtonItem::fadeIn()
{
    m_timeLine->setDirection(QTimeLine::Forward);
    m_timeLine->setDuration(500);
    m_timeLine->start();
}

void ButtonItem::fadeOut()
{
    m_timeLine->setDirection(QTimeLine::Backward);
    m_timeLine->setDuration(500);
    m_timeLine->start();
}

void ButtonItem::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    event->accept();
    fadeIn();
}

void ButtonItem::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    event->accept();
    fadeOut();
}

void ButtonItem::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    event->accept();
    emit clicked();
}
