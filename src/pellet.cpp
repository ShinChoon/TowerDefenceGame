#include "pellet.h"

/**
 * @brief Constructor Pellet
 * @param parent                                An optional parent
 * return None
 */
Pellet::Pellet(QGraphicsItem * parent)
{

    QPixmap pix = QPixmap(":/bullet/images/pellet.png");

    QPixmap scaled = pix.scaled(10,10);


    setPixmap(scaled);

}
