#ifndef PELLET_H
#define PELLET_H

#include "bullet.h"

class Pellet : public Bullet{
    Q_OBJECT
public:
    Pellet(QGraphicsItem *parent = 0);

};

#endif // PELLET_H
