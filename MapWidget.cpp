#include "MapWidget.h"
MapWidget::MapWidget(QWidget *parent): QWebEngineView(parent)
{
    QWebEnginePage *mapPage = page();
    mapPage->load(QUrl("qrc:///map.html"));
}
