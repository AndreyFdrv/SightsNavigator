#include <QtWebChannel/QtWebChannel>
#include <QThread>
#include "MapWidget.h"
#include <QMessageBox>
MapWidget::MapWidget(QWidget *parent): QWebEngineView(parent)
{
    sightsMultigraph.AddVertex("1");
    sightsMultigraph.AddVertex("2");
    sightsMultigraph.AddEdge("1", "2", 20, 0, "пешком");
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
void MapWidget::FindOptimalWay()
{
    //тут sightsMultigraph должен найти оптимальный путь, но это ещё не реализовано
    vector<Route> result;
    Route route;
    route.BeginSight = "Sight1";
    route.EndSight = "Sight2";
    EdgeLabels labels;
    labels.Cost = 0;
    labels.Time = 20;
    labels.Vehicle = "пешком";
    route.Labels = labels;
    result.push_back(route);
    QMessageBox msgResult;
    QString resultStr = "Оптимальный путь:\n\n";
    for(int i = 0; i<result.size(); i++)
    {
        resultStr += QString::number(i+1);
        resultStr += ") Начальная достопримечательность: ";
        resultStr += result.at(i).BeginSight;
        resultStr += "\n";
        resultStr += "Конечная достопримечательность: ";
        resultStr += result.at(i).EndSight;
        resultStr += "\n";
        resultStr += "Способ перемещения: ";
        resultStr += result.at(i).Labels.Vehicle;
        resultStr += "\n";
        resultStr += "Время в пути: ";
        resultStr += QString::number(result.at(i).Labels.Time);
        resultStr += " минут\n";
        resultStr += "Стоимость: ";
        resultStr += QString::number(result.at(i).Labels.Cost);
        resultStr += " рублей\n";
        resultStr += "\n\n";
    }
    msgResult.setText(resultStr);
    msgResult.exec();
}
void MapWidget::GetNextChoosenSight(QString name, int count)
{
    ChoosenSights.push_back(name);
    if(ChoosenSights.size() == count)
        FindOptimalWay();
    page()->runJavaScript("SendChoosenSight("+QString::number(ChoosenSights.size())+");");
}
void MapWidget::GetFirstChoosenSight()
{
    ChoosenSights.clear();
    page()->runJavaScript("SendChoosenSight(0);");
}
MapWidget::~MapWidget()
{
    delete WebChannel;
    exit(0);
}
