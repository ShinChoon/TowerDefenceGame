#include "shotgun_tower.h"
#include "bullet.h"
#include <QTimer>
#include "game.hpp"
#include <stdlib.h>
#include <QDebug>
#include "cockroach.h"
#include "pellet.h"

extern Game* game;

/**
 * @brief Constructor ShotgunTower inherits from Tower
 * Creates area_of_effect and connects timer to its overwritten AcquireTarget method
 * Sets Barrel lenght
 * @param parent        An optional parent
 */
ShotgunTower::ShotgunTower(QGraphicsItem *parent)
{
    QPixmap pix = QPixmap(":/towers/images/shotgun_tower.png");
    QPixmap pix_scaled = pix.scaled(70,70);

    setPixmap(pix_scaled);
    setTransformOriginPoint(pix_scaled.rect().center());
    SetCenterPoint(pix_scaled.rect().center());

    CreateAreaOfEffect(100);

    // Connect a timer to acquire_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(acquire_target()));
    timer->start(3000);

    SetBarrelLenght(55);
}

/**
 * @brief ShotgunTower::fire creates five bullets with different angles that goes towards the target
 */
void ShotgunTower::Fire()
{

    QPointF center = mapToScene(GetCenterPoint());
    QLineF ln(center, target);
    int angle = ln.angle();

    RotateTowardsEnemy(angle);

    // Create 5 shotgun pellets
    Bullet * bullet1 = new Bullet(50, 100);
    Bullet * bullet2 = new Bullet(50, 100);
    Bullet * bullet3 = new Bullet(50, 100);
    Bullet * bullet4 = new Bullet(50, 100);
    Bullet * bullet5 = new Bullet(50, 100);

    // Calculate the point for the tip of the barrel
    double l = GetBarrelLenght(); // The lenght of the barrel
    double dx = l * qCos(qDegreesToRadians(-1 * angle));
    double dy = l * qSin(qDegreesToRadians(-1 * angle));

    bullet1->setPos(center.x() + dx, center.y() + dy);
    bullet2->setPos(center.x() + dx, center.y() + dy);
    bullet3->setPos(center.x() + dx, center.y() + dy);
    bullet4->setPos(center.x() + dx, center.y() + dy);
    bullet5->setPos(center.x() + dx, center.y() + dy);

    bullet1->setRotation(angle + 90 - 20);
    bullet2->setRotation(angle + 90 - 10);
    bullet3->setRotation(angle + 90);
    bullet4->setRotation(angle + 90 + 10);
    bullet5->setRotation(angle + 90 + 20);

    game->scene->addItem(bullet1);
    game->scene->addItem(bullet2);
    game->scene->addItem(bullet3);
    game->scene->addItem(bullet4);
    game->scene->addItem(bullet5);
}

/**
 * @brief ShotgunTower::acquire_target overrides the Tower::AcquireTarget() and uses instead its own fire() method
 */
void ShotgunTower::AcquireTarget()
{
    QList<QGraphicsItem *> colliding_items = area_of_effect->collidingItems();
    size_t n = colliding_items.size();


    has_target = false;

    double closest_dist = 300;
    QPointF closest_point = QPointF(0, 0);
    for (size_t i = 0; i < n; i++)
    {
        Cockroach * enemy = dynamic_cast<Cockroach *>(colliding_items[i]);
        if (enemy)
        {
            double this_dist = DistanceTo(enemy);
            if (this_dist < closest_dist)
            {
                closest_dist = this_dist;
                closest_point = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }

    target = closest_point;
    if (has_target)
    {
        ShotgunTower::Fire();
    }
}
