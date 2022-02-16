#include "machine_gun_tower.h"
#include "bullet.h"
#include "game.hpp"
#include "QTimer"
#include "cockroach.h"

extern Game * game;

/**
 * @brief Constructor MachineGunTower      Sets graphics, creates area_of_effect and sets barrel lenght
 * @param parent                                An optional parent
 * return None
 */
MachineGunTower::MachineGunTower(QGraphicsItem *parent)
{
    // Machine gun tower has high rate of fire and bullet spread
    QPixmap pix = QPixmap(":/towers/images/machine_gun_tower.png");
    QPixmap pix_scaled = pix.scaled(70,80);

    setPixmap(pix_scaled);
    setTransformOriginPoint(pix_scaled.rect().center());
    SetCenterPoint(pix_scaled.rect().center());

    CreateAreaOfEffect(200);


    // Connect a timer to acquire_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(AcquireTarget()));

    // Set the rate of fire to be faster than basic_tower
    timer->start(200);

    SetBarrelLenght(60);

}

/**
 * @brief MachineGunTower::Fire     Override for Fire() method. Adds bullet spread with random angle
 *
 */
void MachineGunTower::Fire()
{

    int x_center = this->GetCenterPoint().x();
    int y_center = this->GetCenterPoint().y();
    QLineF ln(QPointF(x()+ x_center, y()+ y_center), target);
    int angle = ln.angle();


    this->RotateTowardsEnemy(angle);

    Bullet * bullet = new Bullet(75, 300);

    // Calculate the point for the tip of the barrel
    double l = GetBarrelLenght(); // The lenght of the barrel
    double dx = l * qCos(qDegreesToRadians(-1 * angle));
    double dy = l * qSin(qDegreesToRadians(-1 * angle));


    bullet->setPos(x()+ x_center + dx, y()+ y_center + dy);


    // To simulate bullet spread the bullet angle will have small random offset.
    int random_pos = rand() % 15;
    int random_neg = rand() % 15 - 15;
    int random = random_pos + random_neg;

    bullet->setRotation(angle + 90 + random);
    game->scene->addItem(bullet);
}

/**
 * @brief MachineGunTower::AcquireTarget        Overrides the Tower::AcquireTarget and uses its own Fire() method
 */
void MachineGunTower::AcquireTarget()
{
    // Get a list of all items the tower sees
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
        MachineGunTower::Fire();
    }

}
