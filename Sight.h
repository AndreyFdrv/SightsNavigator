#ifndef SIGHT_H
#define SIGHT_H
#include <QString>
#include <QObject>

class Sight:public QObject
{
Q_OBJECT
private:
    double x;
    double y;
    QString name;
public:
    Sight(double x, double y, QString name);
    Q_INVOKABLE double getX();
    Q_PROPERTY(double X READ getX)
    Q_INVOKABLE double getY();
    Q_PROPERTY(double Y READ getY)
    Q_INVOKABLE QString getName();
    Q_PROPERTY(QString Name READ getName)
};

#endif // SIGHT_H
