#ifndef SIGHT_H
#define SIGHT_H
#include <QString>

class Sight
{
private:
    double x;
    double y;
    QString name;
public:
    Sight(double x, double y, QString name);
    double getX();
    double getY();
    QString getName();
};

#endif // SIGHT_H
