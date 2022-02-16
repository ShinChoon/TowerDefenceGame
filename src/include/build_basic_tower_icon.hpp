#ifndef BUILD_BASIC_TOWER_ICON_HPP
#define BUILD_BASIC_TOWER_ICON_HPP

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildBasicTowerIcon: public QGraphicsPixmapItem{
public:

    // pass the image path, pass it price
    BuildBasicTowerIcon(QGraphicsItem *parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:
    int price;
};

#endif // BUILD_BASIC_TOWER_ICON_HPP
