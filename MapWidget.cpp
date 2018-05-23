#include <QtWebChannel/QtWebChannel>
#include <QThread>
#include "MapWidget.h"
MapWidget::MapWidget(QWidget *parent): QWebEngineView(parent)
{
    sightsMultigraph.AddVertex("1");
    sightsMultigraph.AddVertex("2");
    sightsMultigraph.AddEdge("1", "2", 20, 0, "Пешком");
    //Вектор sights должен возвращаться мультиграфом, который ещё не реализован
    Sights = new QVector<Sight *>();
    Sights->append(new Sight(59.934410, 30.324564, "Казанский собор"));
    Sights->append(new Sight(59.937657, 30.308562, "Адмиралтейство"));
    Sights->append(new Sight(59.938279, 30.315546, "Дворцовая площадь"));
    Sights->append(new Sight(59.936442, 30.302236, "Медный всадник"));
    Sights->append(new Sight(59.934179, 30.306102, "Исакиевский собор"));
    Sights->append(new Sight(59.940213, 30.328921, "Спас на Крови"));
    Sights->append(new Sight(59.950137, 30.316697, "Петропавловская крепость"));
    WebChannel = new QWebChannel();
    page()->setWebChannel(WebChannel);
    WebChannel->registerObject("MapWidget", this);
    page()->load(QUrl("qrc:///map.html"));
    QObject::connect(page(), SIGNAL(loadFinished(bool)),
        this, SLOT(SendFirstSight()));
}
void MapWidget::SendFirstSight()
{
    WebChannel->registerObject("Sight", Sights->at(0));
    page()->runJavaScript("GetSight(0);");
}
void MapWidget::SendNextSight(int i)
{
    if(i >= Sights->size())
        return;
    WebChannel->registerObject("Sight", Sights->at(i));
    page()->runJavaScript("GetSight("+QString::number(i)+");");
}
MapWidget::~MapWidget()
{
    delete WebChannel;
    exit(0);
}
