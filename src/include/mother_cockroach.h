#ifndef MOTHER_COCKROACH_H
#define MOTHER_COCKROACH_H

#include "cockroach.h"

class Mother_cockroach:public Cockroach{
public:
    Mother_cockroach(int health, int speed, int value, int child_health, int child_speed, int child_value, QList<QPointF>pointsToFollow,
                    QGraphicsItem *parent = 0);
private:
    void Split();
    void GotHit(int);
    int child_health_;
    int child_speed_;
    int child_value_;

};


#endif // MOTHER_COCKROACH_H
