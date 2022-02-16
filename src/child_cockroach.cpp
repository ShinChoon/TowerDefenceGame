#include "child_cockroach.h"

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
 * @brief Construct a new Child_cockroach::Child_cockroach object
 * it defines the speed, value, enemy path, 
 * the initial location and position offset appear on the map
 * 
 * @param health            Cockroach health
 * @param speed             Speed
 * @param value             Price of Cockroach
 * @param points_ToFollow   Coordinates the cockroach will follow
 * @param posit_index       Index in enemy path Qlist
 * @param q_offset          Position offset appear on the map
 * @param parent            QGraphicsItem
 */

Child_cockroach::Child_cockroach(int health, int speed, int value, QList<QPointF> pointsToFollow, int posit_index, QPointF q_offset, QGraphicsItem *parent)
    : Cockroach(health, speed, value, pointsToFollow, parent)
{
    QPixmap pix = QPixmap(":/cockroach/images/child_cockroach.png");
    QPixmap pix_scaled = pix.scaled(50, 50);

    setPixmap(pix_scaled);

    destList_index_ = 0;
    dest_ = points_[0];

    QPointF center_coord = mapToScene(pixmap().rect().center());
    setTransformOriginPoint(center_coord);

    setPos(dest_ - center_coord);
    // RotateToPoint(dest_);
    dest_ = points_[posit_index];

    StartBehindDestination(q_offset);
    destList_index_ = posit_index;

    // connect timer to move forward
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(200);
}

/**
 * @brief set position to be few bits before the point
 * @param dest_point  destination point
 * @return None
 */

void Child_cockroach::StartBehindDestination(QPointF offset)
{
    dest_ = QPointF(dest_.x() + offset.x(), dest_.y() + offset.y());
    setPos(dest_);
}
/**
 * @brief Define damage decrement when child cockroach got hit
 * @param damage value to decrease the health
 * @return None
 */
void Child_cockroach::GotHit(int damage)
{
    health_ -= damage;
    if (IsDead())
    {
        game->scene->removeItem(this);
        game->child_killed++;
        game->Deposit(value_);
        delete this;
        return;
    }

}
