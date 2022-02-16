#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

class Bullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(int damage, double range);
    ~Bullet();
    int GetDamage(){return damage_;}
public slots:
    void move();
    double get_max_range(); // rest could be in public
    double get_distance_travelled();
    void set_distance_travelled(double distance);

private:
    double max_range;
    double distance_travelled;
    int damage_;
};

#endif // BULLET_H
