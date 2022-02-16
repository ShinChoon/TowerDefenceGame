#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QLineF>
#include "bullet.h"
#include "tower.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include "game.hpp"
#include <QDebug>
#include <QPixmap>
#include <QGraphicsItem>
#include "cockroach.h"


extern Game * game;

/**
 * @brief Constructor Tower      An abstract class that inherits from QGraphicsPixmapItem and QObject
 * @param parent            An optional parameter
 */
Tower::Tower(QGraphicsItem * parent): QObject(), QGraphicsPixmapItem(parent)
{
    // Set the graphics
    QPixmap pix = QPixmap(":/towers/images/basic_tower.png");
    QPixmap pix_scaled = pix.scaled(50,50);
    setPixmap(pix_scaled);

    setTransformOriginPoint(this->pixmap().rect().center());
    SetCenterPoint(this->pixmap().rect().center());

    // Connect a timer to acquire_target
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(AcquireTarget()));
    timer->start(1000);

    // Set target
    target = QPointF(800, 0);
}

/**
 * @brief Tower::distanceTo     Calculates distance from tower to an item
 * @param item
 * @return
 */
double Tower::DistanceTo(QGraphicsItem *item)
{
    QLineF ln(pos(), item->pos());
    return ln.length();
}

/**
 * @brief Tower::fire       Creates a bullet that will travel towards the target
 */
void Tower::Fire()
{
    QPointF center = mapToScene(GetCenterPoint());
    QLineF ln(center, target);
    int angle = ln.angle();

    double l = GetBarrelLenght(); // The lenght of the barrel
    double dx = l * qCos(qDegreesToRadians(-1 * angle));
    double dy = l * qSin(qDegreesToRadians(-1 * angle));


    RotateTowardsEnemy(angle);
    Bullet * bullet = new Bullet(100, 400);
    bullet->setPos(center.x() + dx, center.y() + dy);
    bullet->setRotation(angle + 90);
    game->scene->addItem(bullet);

}

/**
 * @brief Tower::RotateTowardsEnemy     Rotates the tower
 * @param angle                         The angle of rotation
 */
void Tower::RotateTowardsEnemy(int angle)
{
    this->setRotation(-1 * angle + 90);
}

/**
 * @brief Tower::setCenterPoint     Set function for towers center point
 * @param center_point              The center point of the tower
 */
void Tower::SetCenterPoint(QPointF center_point)
{
    center = center_point;
}

/**
 * @brief Tower::getCenterPoint     Get function for towers center point
 * @return
 */
QPointF Tower::GetCenterPoint()
{
    return center;
}

/**
 * @brief Tower::acquire_target     Checks if enemies are in the area_of_effect, sets target and calls method fire()
 * A Virtual method
 */
void Tower::AcquireTarget()
{
    // Get a list of all items the tower sees
    QList<QGraphicsItem *> colliding_items = area_of_effect->collidingItems();
    size_t n = colliding_items.size();

    has_target = false;

    double closest_dist = 300;
    QPointF closest_point = QPointF(0, 0);
    for (size_t i = 0; i < n; i++) // Go through the list of colliding items
    {
        Cockroach * enemy = dynamic_cast<Cockroach *>(colliding_items[i]);
        if (enemy) // If a enemy pointer is found in list of colliding items
        {
            double this_dist = DistanceTo(enemy);
            if (this_dist < closest_dist)
            {
                closest_dist = this_dist;
                closest_point = colliding_items[i]->pos();
                has_target = true;
            }

        }

    }

    target = closest_point;
    if (has_target)
    {
        Tower::Fire();
    }

}

/**
 * @brief Tower::setBarrelLenght        Sets the value holding lenght of the barrel of the tower
 * @param lenght
 */
void Tower::SetBarrelLenght(int lenght)
{
    barrel_lenght = lenght;
}

/**
 * @brief Tower::getBarrelLenght        Gets the value holding lenght of the barrel of the tower
 * @return
 */
int Tower::GetBarrelLenght()
{
    return barrel_lenght;
}

/**
 * @brief Tower::createAreaOfEffect     Creates the PolygonItem area_of_effect from points and scales them accordingly
 * @param scale_factor                  The scale_factor defines the size of the polygon
 */
void Tower::CreateAreaOfEffect(int scale_factor)
{
    //Polygon takes a vector of points
    QVector<QPointF> points;
    // Add the desired points describing the polygon to the vector:
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1)
           << QPoint(3,2) << QPoint(2,3) << QPoint(1,3)
           << QPoint(0,2) << QPoint(0,1);

    // Scale the points
    size_t n = points.size();

    for (size_t i = 0; i < n; i++)
    {
        points[i] *= scale_factor;
    }

    //Create a polygon from these points
    QPolygonF polygon(points);

    // Create the QGraphicsPolygonItem
    area_of_effect = new QGraphicsPolygonItem(polygon, this);
    QColor trans = Qt::white;
    trans.setAlpha(0.0);
    area_of_effect->setPen(QPen(trans));


    // Move the polygon
    QPointF poly_center = QPointF(1.5,1.5);
    poly_center *= scale_factor;
    poly_center = mapToScene(poly_center);
    QPointF tower_center(GetCenterPoint());
    QLineF ln(poly_center, tower_center);
    area_of_effect->setPos(x() + ln.dx(),y()+ ln.dy());

}

