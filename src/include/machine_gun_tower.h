#ifndef MACHINE_GUN_TOWER_H
#define MACHINE_GUN_TOWER_H

#include "tower.h"

class MachineGunTower : public Tower{
    Q_OBJECT
public:
    MachineGunTower(QGraphicsItem * parent = 0);
    void Fire();
public slots:
    void AcquireTarget();
};

#endif // MACHINE_GUN_TOWER_H
