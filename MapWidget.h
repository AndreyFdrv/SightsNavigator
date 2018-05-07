#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtWebEngineWidgets/QWebEngineView>
#include "Sight.h"

class MapWidget:public QWebEngineView
{
Q_OBJECT
private:
    QVector<Sight *> *Sights;
public:
    QWebChannel* WebChannel;
    MapWidget(QWidget *parent=0);
    ~MapWidget();
    Q_INVOKABLE void SendNextSight(int i);
public slots:
    void SendFirstSight();
};

#endif // MAPWIDGET_H
