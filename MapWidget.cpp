#include "MapWidget.h"
MapWidget::MapWidget(QWidget *parent): QWebEngineView(parent)
{
    QWebEnginePage *mapPage = page();
    connect(mapPage, &QWebEnginePage::featurePermissionRequested,
            [this, mapPage](const QUrl &securityOrigin, QWebEnginePage::Feature feature) {
        if (feature != QWebEnginePage::Geolocation)
            return;
    });
    mapPage->load(QUrl(QStringLiteral("https://maps.google.com")));
}
