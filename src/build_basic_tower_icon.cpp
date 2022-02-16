#include "build_basic_tower_icon.hpp"
#include "game.hpp"
#include "basic_tower.h"

extern Game *game;

/**
 * @brief Constructor BuildBasicTowerIcon   Builds basic tower icon
 * @param parent                            An optional parent
 */
BuildBasicTowerIcon::BuildBasicTowerIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{

}

/**
 * @brief Add basic tower and add icon to cursor
 * @param event QGraphicsSceneMouseEvent pointer
 * @return None
 */
void BuildBasicTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->building)
    {
        if (game->Withdraw(100))
        {
            qDebug() << "Create building !";
            game->building = new BasicTower();
            game->setCursor(QString(":/towers/images/basic_tower.png"));
        }
    }
}
