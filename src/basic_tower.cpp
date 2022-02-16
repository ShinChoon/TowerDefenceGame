#include "basic_tower.h"
#include "bullet.h"
#include "game.hpp"
#include "QTimer"



extern Game * game;

/**
 * @brief Constructor BasicTower        Sets graphics, creates area_of_effect and sets barrel lenght
 * @param parent                        An optional parent
 */
BasicTower::BasicTower(QGraphicsItem *parent)
{
    QPixmap pix = QPixmap(":/towers/images/basic_tower.png");
    QPixmap pix_scaled = pix.scaled(70,70);

    setPixmap(pix_scaled);
    setTransformOriginPoint(pix_scaled.rect().center());
    SetCenterPoint(pix_scaled.rect().center());

    CreateAreaOfEffect(150);

    // Connect a timer to acquire_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(AcquireTarget()));
    timer->start(1000);

    SetBarrelLenght(55);
}

/**
 * @brief BasicTower::AcquireTarget     Uses Tower::AcquireTarget()
 */
void BasicTower::AcquireTarget()
{
    // The Basic Tower will use the Tower class' acquire_target() method.
    Tower::AcquireTarget();
}
