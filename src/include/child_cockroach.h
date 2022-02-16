#ifndef CHILD_COCKROACH_H
#define CHILD_COCKROACH_H

#include "cockroach.h"

class Child_cockroach : public Cockroach
{
public:
    Child_cockroach(int health, int speed, int value, QList<QPointF> pointsToFollow, int posit_index, QPointF q_offset, QGraphicsItem *parent = 0);

private:
    void StartBehindDestination(QPointF);
    void GotHit(int damage);
};

#endif // CHILD_COCKROACH_H
