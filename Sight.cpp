#include "Sight.h"

Sight::Sight(double x, double y, QString name)
{
    this->x=x;
    this->y=y;
    thos->name=name;
}
double Sight::getX()
{
    return x;
}
double Sight::getY()
{
    return y;
}
QString Sight::getName()
{
    return name;
}
