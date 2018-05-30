#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtWebEngineWidgets/QWebEngineView>
#include "SightsMultigraph.h"

class MapWidget:public QWebEngineView
{
Q_OBJECT
private:
    vector<Sight *> Sights;
    SightsMultigraph sightsMultigraph;
    vector<QString> ChosenSights;
    int MaxCost;
    void FindOptimalWay();
public:
    QWebChannel* WebChannel;
    MapWidget(QWidget *parent=0);
    ~MapWidget();
    Q_INVOKABLE void SendNextSight(int i);
    Q_INVOKABLE void GetNextChoosenSight(QString name, int count);
    void FillSightMultigraph();
public slots:
    void SendFirstSight();
    void GetFirstChoosenSight();
    void SetMaxCost(QString maxCostStr);
    void SaveSightsMultigraph(QString filename);
    void LoadSightsMultigraph(QString filename, bool isInit=false);
};

#endif // MAPWIDGET_H
