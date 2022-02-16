#include "build_shotgun_tower_icon.hpp"
#include "game.hpp"
#include "shotgun_tower.h"

extern Game *game;

/**
 * @brief Constructor BuildShotgunTowerIcon        Builds shot tower icon
 * @param parent                    An optional parent
 */
BuildShotgunTowerIcon::BuildShotgunTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/towers_icon/images/short_gun_tower_icon.png"));
}

/**
 * @brief Add machine tower and add icon to cursor
 * @param event QGraphicsSceneMouseEvent pointer
 * @return None
 */

void BuildShotgunTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Clicked the shotgun tower icon";
    if (!game->building)
    {
        if(game->Withdraw(200))
        {
            game->building = new ShotgunTower();
            game->setCursor(QString(":/towers/images/shotgun_tower.png"));
        }
    }
}
