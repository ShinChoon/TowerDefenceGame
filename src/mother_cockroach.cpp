#include "mother_cockroach.h"

#include <QTimer>
#include <QPixmap>
#include <QtDebug>
#include <QLineF>
#include <QWidget>
#include <QPolygonF>
#include <QPen>
#include <QDebug>
#include <stdlib.h>

#include "child_cockroach.h"
#include "game.hpp"

extern Game *game; // there is an external game object

/**
 * @brief Constructor Mother_cockroach        defines the adult cockroach object,it defines the speed, value, enemy path, the initial location and position offset appear on the map
 * @param health                    Set health
 * @param speed                     Set speed
 * @param value                     Set value
 * @param pointsToFollow            Set pointsToFollow
 * @param child_health              Set child health
 * @param child_speed               Set child speed
 * @param child_value               Set child value
 * @param parent                    An optional parent
 */
Mother_cockroach::Mother_cockroach(int health, int speed, int value, int child_health, int child_speed, int child_value,
                                   QList<QPointF> pointsToFollow, QGraphicsItem *parent)
    : Cockroach(health, speed, value, pointsToFollow, parent)
{
    child_health_ = child_health;
    child_speed_ = child_speed;
    child_value_ = child_value;
    QPixmap pix = QPixmap(":/cockroach/images/mother_cockroach.png");
    QPixmap pix_scaled = pix.scaled(70, 70);

    setPixmap(pix_scaled);

    destList_index_ = 0;
    dest_ = points_[0];

    QPointF center_coord = mapToScene(pixmap().rect().center());
    setTransformOriginPoint(center_coord);

    setPos(dest_ - center_coord);
    // RotateToPoint(dest_);
    dest_ = points_[0];

    // StartBehindDestination(q_offset);
    destList_index_ = 0;

    // connect timer to move forward
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Move()));
    timer->start(200);
}

/**
 * @brief Defines actions specifically when mother was hit
 * if mother dead, it creates few new babies and is removed from scene.
 * @param None
 * @return None
 */
void Mother_cockroach::GotHit(int damage)
{

    if (health_ > 0)
    {
        health_ -= damage; // by feature value
    }
    else
    {
        this->Split();
        game->scene->removeItem(this);
        game->mother_killed++;
        game->Deposit(value_);
        //        game->child_spawmed+=4;
        //        game->total_spawned+=4;
        delete this;
        return;
    }
}

/**
 * @brief Defines how mother generate numbers of babies
 * if mother dead, it creates 4 new babies and is removed from scene.
 * @param None
 * @return None
 */

void Mother_cockroach::Split()
{
    Child_cockroach *baby1st = new Child_cockroach(child_health_, child_speed_, child_value_, points_,
                                                   destList_index_ - 1, QPointF(-20, -15));
    Child_cockroach *baby2nd = new Child_cockroach(child_health_, child_speed_, child_value_, points_,
                                                   destList_index_ - 1, QPointF(-20, -5));
    Child_cockroach *baby3rd = new Child_cockroach(child_health_, child_speed_, child_value_, points_,
                                                   destList_index_ - 1, QPointF(20, 5));
    Child_cockroach *baby4th = new Child_cockroach(child_health_, child_speed_, child_value_, points_,
                                                   destList_index_ - 1, QPointF(20, 15));

    game->scene->addItem(baby1st);
    game->scene->addItem(baby2nd);
    game->scene->addItem(baby3rd);
    game->scene->addItem(baby4th);
}
