#include <item_not_placeble_tile.h>

/**
 * @brief Construct a new Item Not Placeble Tile:: Item Not Placeble Tile object
 * Create a tile where items can not be placed
 * @param file_path File path for the image
 * @param width     Width the image need to fit in the tile 
 * @param height    Height the image need to fit in the tile 
 * @param coord     Corrdinate where to set tile once created
 */
ItemNotPlacebleTile::ItemNotPlacebleTile(QString file_path, int width, int height, QPointF coord)
{
    QPixmap tile_img = QPixmap(file_path);
    QPixmap tile_img_scaled = tile_img.scaled(width, height);
    setPixmap(tile_img_scaled);
    setPos(coord);
}
