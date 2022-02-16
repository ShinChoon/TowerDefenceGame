#ifndef ITEM_PLACEBLE_TILE_H
#define ITEM_PLACEBLE_TILE_H

#include <QGraphicsPixmapItem>

class ItemPlacebleTile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ItemPlacebleTile(QString file_path, int width, int heigth, QPointF coord);
    virtual ~ItemPlacebleTile() {}
};

#endif // ITEM_PLACEBLE_TILE_H

