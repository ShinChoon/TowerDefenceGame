#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>



class Tower : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tower(QGraphicsItem * parent = 0);
    double DistanceTo(QGraphicsItem * item);
    virtual void Fire();
    void RotateTowardsEnemy(int angle);

    void SetCenterPoint(QPointF center_point);
    QPointF GetCenterPoint();
    void SetBarrelLenght(int lenght);
    int GetBarrelLenght();
    void CreateAreaOfEffect(int scale_factor);
public slots:
    virtual void AcquireTarget();
protected:
    QGraphicsPolygonItem * area_of_effect;
    QPointF target;
    bool has_target;
    QPointF center;
    int barrel_lenght;

private:
    //implement copy contructor and copy assingment overload here
};
#endif // TOWER_H
