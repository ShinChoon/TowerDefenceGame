#include "bullet.h"
#include <QPixmap>
#include <QTimer>
#include <QtMath>
#include "cockroach.h"
#include "game.hpp"
#include <stdlib.h>

/**
 * @brief Constructs bullet
 * @param damage        Sets the damage value of the bullet
 * @param range         Sets the range of the bullet
 * @return None
 */

extern Game * game;

Bullet::Bullet(int damage, double range) : damage_(damage), max_range(range)
{
    //Set graphics
    QPixmap pix = QPixmap(":/bullet/images/bullet.png");
    QPixmap scaled = pix.scaled(20, 20);
    setPixmap(scaled);

    setTransformOriginPoint(scaled.rect().center());


    // Connect a timer to move()
    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(20);

    distance_travelled = 0;
}

Bullet::~Bullet()
{
}

/**
 * @brief Timer connected slot that makes the bullet move along its current angle
 * A bullet ill only travel as far as the range allowes.
 * Checks for collisions with cockroaches and if it hits, it will cause damage to the cockroach and destroy itself
 *
 * @return None
 */
void Bullet::move()
{
    if (get_distance_travelled() >= get_max_range())
    {
        game->scene->removeItem(this);
        delete this;
        return;
    }

    //Move it at its current angle
    int STEP_SIZE = 40;
    double theta = rotation(); // In degrees

    double dx = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dy = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x() + dx, y()+ dy);
    int travelled = sqrt((dx * dx) + (dy * dy));
    distance_travelled = distance_travelled + travelled;

    // Get a list of all items the bullet touches
    QList<QGraphicsItem *> colliding_items = this->collidingItems();
    size_t n = colliding_items.size();

    for (size_t i = 0; i < n; i++) // Go through the list of colliding items
    {
        Cockroach * enemy = dynamic_cast<Cockroach *>(colliding_items[i]);
        if (enemy) // If a enemy pointer is found in list of colliding items
        {
            enemy->GotHit(GetDamage());
            game->scene->removeItem(this);
            delete this;
            return;
        }

    }
}

/**
 * @brief Bullet::get_max_range     Get function for max_range
 * @return max_range                Returns max_range
 */
double Bullet::get_max_range()
{
    return max_range;
}

/**
 * @brief Bullet::get_distance_travelled    Get function for distance_travelled
 * @return distance_travelled               Returns the distance the bullet has travelled
 */
double Bullet::get_distance_travelled()
{
    return distance_travelled;
}

/**
 * @brief Bullet::set_distance_travelled    Set function for distance_travelled
 * @param distance
 */
void Bullet::set_distance_travelled(double distance)
{
    distance_travelled = distance;
}


