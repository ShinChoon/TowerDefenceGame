#ifndef ADULT_COCKROACH_H
#define ADULT_COCKROACH_H

#include "cockroach.h"

class Adult_cockroach:public Cockroach{
public:
    Adult_cockroach(int health, int speed, int value, QList<QPointF>pointsToFollow,
                    QGraphicsItem *parent = 0);

private:
    void GotHit(int damage);

};
#endif // ADULT_COCKROACH_H
