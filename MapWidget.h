#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtWebEngineWidgets/QWebEngineView>

class MapWidget:public QWebEngineView
{
Q_OBJECT
public:
    MapWidget(QWidget *parent=0);
};

#endif // MAPWIDGET_H
