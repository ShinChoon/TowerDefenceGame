#ifndef BASIC_TOWER_H
#define BASIC_TOWER_H
#include <QMessageBox>

#include "tower.h"

class BasicTower : public Tower{
    Q_OBJECT
public:
    BasicTower(QGraphicsItem * parent = 0);
public slots:
    void AcquireTarget();
};

#endif // BASIC_TOWER_H
