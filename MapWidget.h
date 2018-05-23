#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtWebEngineWidgets/QWebEngineView>
#include "Sight.h"
#include "Multigraph.h"

class MapWidget:public QWebEngineView
{
Q_OBJECT
private:
    QVector<Sight *> *Sights;
    Multigraph multigraph;
public:
    QWebChannel* WebChannel;
    MapWidget(QWidget *parent=0);
    ~MapWidget();
    Q_INVOKABLE void SendNextSight(int i);
public slots:
    void SendFirstSight();
};

#endif // MAPWIDGET_H
