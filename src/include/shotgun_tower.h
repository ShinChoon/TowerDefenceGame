#ifndef SHOTGUN_TOWER_H
#define SHOTGUN_TOWER_H

#include "tower.h"

class ShotgunTower : public Tower{
    Q_OBJECT
public:
    ShotgunTower(QGraphicsItem * parent = 0);
    void Fire();
public slots:
    void AcquireTarget();
};

#endif // SHOTGUN_TOWER_H
