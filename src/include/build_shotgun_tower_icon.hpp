#ifndef BUILD_SHOTGUN_TOWER_ICON_HPP
#define BUILD_SHOTGUN_TOWER_ICON_HPP

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildShotgunTowerIcon: public QGraphicsPixmapItem{
public:
    BuildShotgunTowerIcon(QGraphicsItem *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BUILD_SHOTGUN_TOWER_ICON_HPP
