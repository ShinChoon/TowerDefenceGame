#include "build_machine_gun_tower_icon.hpp"
#include "game.hpp"
#include "machine_gun_tower.h"

extern Game *game;

/**
 * @brief Constructor BuildMachineGunTowerIcon        Builds machine tower icon
 * @param parent                    An optional parent
 */
BuildMachineGunTowerIcon::BuildMachineGunTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    // setPixmap(QPixmap(":/towers_icon/images/machine_gun_tower_icon.png"));
}

/**
 * @brief Add machine tower and add icon to cursor
 * @param event QGraphicsSceneMouseEvent pointer
 * @return None
 */

void BuildMachineGunTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Clicked the machine tower icon";
    if (!game->building)
    {
        if (game->Withdraw(1000))
        {
            game->building = new MachineGunTower();
            game->setCursor(QString(":/towers/images/machine_gun_tower.png"));
        }
    }
}
