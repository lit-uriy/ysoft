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

#include <QtGui/QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QDesktopWidget>
#include <QDebug>

#include "mainview.h"
#include "clockmanager.h"

int main(int argc, char *argv[])
{
    QApplication app( argc, argv );
    QDesktopWidget screen;

    QGraphicsScene scene;
    scene.setSceneRect( screen.screenGeometry() );

    MainView view( &scene );

    view.setWindowTitle( "Clocks" );
    view.setMinimumSize( screen.screenGeometry().size() );
    view.setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view.setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    view.setFrameShape( QFrame::NoFrame );
    view.setWindowState( Qt::WindowFullScreen );
    view.setBackgroundBrush( Qt::black );

  /*
    for licensing see http://www.oera.net/How2/TextureMaps2.htm
    "Here are some of my planetary texture maps that I've collected over the years. It has taken me lots
    of time to find and make these maps, but I'm providing them here for your modelling pleasure.
    They are available in a usable size compared to other places on the web. In fact, with the size of
    2500x1250 you should be able to render out full disc renders with as high as 1250x1250 resolution!!!!!
    If you do use these images in your own rendering, I would love to see them. If you have
    any renders, send them to me here. You are free to download these maps and use them in your own
    work as you see fit, but do NOT redistribute these maps in any form!!!!

    If you use the maps in ANY commercial images/Animation I would like to see the final product.
    I will not charge any money for use of the maps, so don't be worried about that!! :-)"
    */

    QGraphicsPixmapItem* background = new QGraphicsPixmapItem( QPixmap( ":/StarsMap.png" ) );
    background->setZValue( 0 );
    background->scale( 0.7, 0.7 );
    view.setBackground( background );
    scene.addItem( background );

    ClockManager* manager = new ClockManager( scene );
    scene.addItem( manager );
    manager->setZValue( 2 );
    view.setClockManager( manager );

    view.triggerElementPositioning();
    view.show();

    return app.exec();
}
