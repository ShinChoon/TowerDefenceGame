#include "adult_cockroach.h"

#include <QTimer>
#include <QPixmap>
#include <QtDebug>
#include <QLineF>
#include <QWidget>
#include <QPolygonF>
#include <QPen>

#include "game.hpp"

extern Game *game;

/**
 * @brief Construct a new Adult_cockroach::Adult_cockroach object
 * This subclass defines the adult cockroach object,
 * it defines the speed, value, enemy path,
 * the initial location and position offset appear on the map
 * 
 * @param health            Cockroach health
 * @param speed             Speed
 * @param value             Price of Cockroach
 * @param points_ToFollow   Coordinates the cockroach will follow
 * @param parent            QGraphicsItem
 */
Adult_cockroach::Adult_cockroach(int health, int speed, int value, QList<QPointF> pointsToFollow, QGraphicsItem *parent)
    : Cockroach(health, speed, value, pointsToFollow, parent)
{
    QPixmap pix = QPixmap(":/cockroach/images/adult_cockroach.png");
    QPixmap pix_scaled = pix.scaled(60, 60);

    setPixmap(pix_scaled);

    destList_index_ = 0;
    dest_ = points_[0];

    QPointF center_coord = mapToScene(pixmap().rect().center());
    setTransformOriginPoint(center_coord);

    setPos(dest_ - center_coord);
    dest_ = points_[0];
    destList_index_ = 0;

    // connect timer to move forward
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(200);
}

/**
 * @brief Define damage decrement when adult cockroach got hit
 * @param damage value to decrease the health
 * @return None
 */
void Adult_cockroach::GotHit(int damage)
{
    health_ -= damage;
    if (IsDead())
    {
        game->scene->removeItem(this);
        game->adult_killed++;
        game->Deposit(value_);
        delete this;
        return;
    }
}
