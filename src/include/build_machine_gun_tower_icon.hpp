#ifndef BUILD_MACHINE_GUN_TOWER_ICON_HPP
#define BUILD_MACHINE_GUN_TOWER_ICON_HPP

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildMachineGunTowerIcon: public QGraphicsPixmapItem{
public:
    BuildMachineGunTowerIcon(QGraphicsItem *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BUILD_MACHINE_GUN_TOWER_ICON_HPP
