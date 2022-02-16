#include "cockroach.h"

#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QPointF>
#include <QLineF>
#include <QTimer>
#include <QPen>
#include <typeinfo>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "bullet.h"
#include "game.hpp"

extern Game *game;
extern Bullet *bullet;

/**
 * @brief Construct a new Cockroach:: Cockroach object
 * This Cockroach is the base class of all three kinds of Cockroach
 * It initialize the health, speed, value and enemy path
 *  The function move() and GotHit are overwritten by the subclasses
 *
 * @param health            Cockroach health
 * @param speed             Speed
 * @param value             Price of Cockroach
 * @param points_ToFollow   Cooridnated the cockroach will follow
 * @param parent            QGraphicsItem
 */
Cockroach::Cockroach(int health, int speed, int value,
                     QList<QPointF> pointsToFollow,
                     QGraphicsItem *parent) : health_(health),
                                              speed_(speed), value_(value), points_(pointsToFollow),
                                              QGraphicsPixmapItem(parent)
{
}

/**
 * @brief Get the cockroach value
 * @param  None
 * @return value_ value of cockroach
 */

int Cockroach::GetValue() const
{
    return value_;
}

/**
 * @brief Get the cockroach health
 * @param  None
 * @return health_ health of cockroach
 */
int Cockroach::GetHealth() const
{
    return health_;
}

/**
 * @brief Get the cockroach speed
 * @param  None
 * @return speed_ speed of cockroach
 */
int Cockroach::GetSpeed() const
{
    return speed_;
}

/**
 * @brief Defines how enemy change its direction
 * @param  p The destination point
 * @return ln.length() the distance to next point
 */
int Cockroach::RotateToPoint(QPointF p)
{
    QPointF center = mapToScene(pixmap().rect().center());
    QLineF ln(center, p);
    setRotation(-1 * ln.angle());
    return ln.length();
}

/**
 * @brief Defines how cockroach move,
 * when cockroach get close to destination,
 * set destination to the next
 * @param None
 * @return None
 */
void Cockroach::Move()
{
    // if close to dest, rotate to next dest
    int center_x = pixmap().rect().x();
    int center_y = pixmap().rect().y();
    QPointF center_coord = QPointF(pos().x() + center_x, pos().y() + center_y);
    QLineF ln(center_coord, dest_);

    if (ln.length() < 50)
    {
        if (destList_index_ < points_.length() - 1)
            destList_index_++;
        dest_ = points_[destList_index_];
    }
    PreventCollide();
    WalkTo(dest_);
}

/*
 * Definition: when croach receive hit, health decrease
 * Decreae by value
 */

/**
 * @brief When croach receive hit, decrease health
 * 
 * @param damage 
 */
void Cockroach::GotHit(int damage)
{
    health_ -= damage;
    if (IsDead())
    {
        game->scene->removeItem(this);
        delete this;
        return;
    }
}

/**
 * @brief Defines actions when cockroach collide
 * @param None
 * @return None
 */
void Cockroach::PreventCollide()
{
    //    colliding_items = collidingItems();
    //    PreventOutOfBoundry();
    BounceToWall();
    PreventCollidedToCocsh();
}

/**
 * @brief Defines actions when cockroach collide to boundary
 * @param None
 * @return None
 */
void Cockroach::PreventOutOfBoundry()
{
    colliding_items = collidingItems();
    if (((pos().y() >= 650) || (pos().y() < 0)) && (pos().x() < 1700))
    {
        qDebug() << "out of boundry!!";
        QLineF this_dist(pos(), points_[destList_index_]);
        if (destList_index_ < points_.size() - 1)
            RotateToPoint(dest_);
        setPos(x() + this_dist.dx() / 5, y() + this_dist.dy() / 5);
    }
}

/**
 * @brief Defines actions when cockroach collide to other cockroach
 * @param None
 * @return None
 */
void Cockroach::PreventCollidedToCocsh()
{
    colliding_items = collidingItems();
    // try to prevent collide
    for (size_t i = 0, n = colliding_items.size(); i < n; i++)
    {
        Cockroach *enemies = dynamic_cast<Cockroach *>(colliding_items[i]);
        if ((enemies) && (destList_index_ >= 2))
        {
            if (destList_index_ < points_.size() - 1)
            {
                QLineF this_dist(pos(), points_[destList_index_]);
                setPos(x() + this_dist.dx() / 3, y() + this_dist.dy() / 3);
            }
            return;
        }
    }
}

/**
 * @brief Defines actions when cockroach collide to wall
 * @param None
 * @return None
 */
void Cockroach::BounceToWall()
{
    colliding_items = collidingItems();
    for (size_t i = 0, n = colliding_items.size(); i < n; i++)
    {
        // check graphics
        QGraphicsRectItem *tile = dynamic_cast<QGraphicsRectItem *>(colliding_items[i]);
        if (tile)
        {
            if (tile->brush() == QColor(255, 165, 0))
            {
                RotateToPoint(dest_);
            }
            return;
        }
    }
}

/**
 * @brief Defines how cockroach take steps to the destination
 * @param nextPoint  destination point
 * @return None
 */
void Cockroach::WalkTo(QPointF nextPoint)
{
    //     move nenemy forward at currnt angle

    // if(destList_index_ == points_.length()-1){
    if (destList_index_ == points_.size() - 1)
    {
        game->game_over_flag = true;
        game->scene->removeItem(this);
        delete this;
        return;
    }
    else
    {
        RotateToPoint(nextPoint);
        double theta = rotation(); // degree
        dy = speed_ * qSin(qDegreesToRadians(theta));
        dx = speed_ * qCos(qDegreesToRadians(theta));
        setPos(x() + dx, y() + dy);
    }
}
/**
 * @brief Checks if cockroach is dead
 * 
 * @return true 
 * @return false 
 */
bool Cockroach::IsDead()
{
    return (health_ > 0 ? false : true);
}

/**
 * @brief Find the location of the current destination
 * @param None
 * @return index int
 */
int Cockroach::GetDestIndex() const
{
    for (size_t i = 0; i < points_.length(); i++)
    {
        if (dest_ == points_[i])
        {
            return i;
        }
    }
    return 0;
}
