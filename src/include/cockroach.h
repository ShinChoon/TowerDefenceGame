#ifndef COCKROACH_H
#define COCKROACH_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
#include <QList>

class Cockroach : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // rule of three: default constructor, destructor, denied copy
    Cockroach() = default;
    Cockroach(int health, int speed,
              int value, QList<QPointF> pointsToFollow,
              QGraphicsItem *parent = 0);
    Cockroach(const Cockroach &Coch) = delete;
    Cockroach &operator=(Cockroach &coch) = delete;
    ~Cockroach() = default;

    int GetValue() const;
    int GetHealth() const;
    int GetSpeed() const;
    int GetDestIndex() const;
    QPointF GetDest() const { return dest_; }
    QList<QPointF> GetPointList() const { return points_; }

public slots:
    virtual void Move();
    virtual void GotHit(int damage);

protected:
    QList<QPointF> points_;
    QPointF dest_;
    int destList_index_;
    int health_;
    int speed_;
    int value_;
    double dx;
    double dy;
    int assB;
    qreal variant_ = 0;
    QTimer *timer_ = nullptr;
    QList<QGraphicsItem *> colliding_items;

    void PreventCollide();
    void PreventCollidedToCocsh();
    void PreventOutOfBoundry();
    void BounceToWall();

    void WalkTo(QPointF);
    bool IsDead();
    int RotateToPoint(QPointF p);
};

#endif // COCKROACH_H
