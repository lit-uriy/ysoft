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

#include "abstractclock.h"
#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <QTimeLine>
#include <QTimer>

AbstractClock::AbstractClock( QGraphicsItem * parent ) : QObject(), QGraphicsItem( parent ), m_opacity( 0 ), m_hidden(true)
{
    m_timeLine = new QTimeLine(2000, this);
    m_timeLine->setFrameRange(0, 100);
    m_timeLine->setCurveShape( QTimeLine::EaseInOutCurve );
    m_timeLine->setDirection( QTimeLine::Forward );
    QObject::connect( m_timeLine, SIGNAL( frameChanged(int) ), this, SLOT( updateOpacity(int) ) );

    m_animationTimeLine = new QTimeLine(2000, this);
    m_animationTimeLine->setFrameRange(0, 100);
    m_animationTimeLine->setCurveShape( QTimeLine::SineCurve );
    m_animationTimeLine->setDirection( QTimeLine::Forward );
    QObject::connect( m_animationTimeLine, SIGNAL( frameChanged(int) ), this, SLOT( updateAnimationValues(int) ) );


    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
    m_timer->start(1000);
}

AbstractClock::~AbstractClock()
{
    delete m_timer;
    delete m_timeLine;
}

QRectF AbstractClock::boundingRect() const
{
  return QRectF( 0, 0, 200, 200 );
}

void AbstractClock::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

    int side = qMin(boundingRect().width(), boundingRect().height());
    QTime time = QTime::currentTime();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate(boundingRect().width() / 2, boundingRect().height() / 2);
    painter->scale(side / 200.0, side / 200.0);

    painter->setPen(Qt::NoPen);
    painter->setBrush(hourColor);

    painter->save();
    painter->rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter->drawConvexPolygon(hourHand, 3);
    painter->restore();

    painter->setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        painter->drawLine(88, 0, 96, 0);
        painter->rotate(30.0);
    }

    painter->setPen(Qt::NoPen);
    painter->setBrush(minuteColor);

    painter->save();
    painter->rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter->drawConvexPolygon(minuteHand, 3);
    painter->restore();

    painter->setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter->drawLine(92, 0, 96, 0);
        painter->rotate(6.0);
    }
}

void AbstractClock::updateOpacity( int opacity )
{
    const qreal opacity_ = opacity;
    m_opacity = opacity_ / 100;
    update();
}

void AbstractClock::updateAnimationValues( int value )
{
    // overwrite this
    Q_UNUSED( value );
}

void AbstractClock::fadeIn()
{
    m_timeLine->setDirection(QTimeLine::Forward);
    m_timeLine->setDuration(2000);
    m_timeLine->start();
    show();
}

void AbstractClock::fadeOut()
{
    m_timeLine->setDirection(QTimeLine::Backward);
    m_timeLine->setDuration(200);
    m_timeLine->start();
    hide();
}

void AbstractClock::repaint()
{
    update();
}
