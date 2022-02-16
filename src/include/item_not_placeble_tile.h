#ifndef ITEM_NOT_PLACEBLE_TILE_H
#define ITEM_NOT_PLACEBLE_TILE_H

#include <QGraphicsPixmapItem>

class ItemNotPlacebleTile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    ItemNotPlacebleTile(QString file_path, int width, int heigth, QPointF coord);
    virtual ~ItemNotPlacebleTile() {}
};

#endif // ITEM_NOT_PLACEBLE_TILE_H
