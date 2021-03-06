#include <QtWebChannel/QtWebChannel>
#include <QThread>
#include "MapWidget.h"
#include <QMessageBox>
MapWidget::MapWidget(QWidget *parent): QWebEngineView(parent)
{
    const QString defaultMultigraphFilename = "default.mg";
    try
    {
        LoadSightsMultigraph(defaultMultigraphFilename, true);
    }
    catch(exception& e)
    {
        QMessageBox::information(this, "", QString(e.what()), QMessageBox::Ok);
    }
    Sights = sightsMultigraph.GetSights();
    WebChannel = new QWebChannel();
    page()->setWebChannel(WebChannel);
    WebChannel->registerObject("MapWidget", this);
    page()->load(QUrl("qrc:///map.html"));
    QObject::connect(page(), SIGNAL(loadFinished(bool)),
        this, SLOT(SendFirstSight()));
}
void MapWidget::FillSightMultigraph()
{
    sightsMultigraph.AddVertex("Казанский собор", 59.934410, 30.324564);
    sightsMultigraph.AddVertex("Адмиралтейство", 59.937657, 30.308562);
    sightsMultigraph.AddVertex("Дворцовая площадь", 59.938279, 30.315546);
    sightsMultigraph.AddVertex("Медный всадник", 59.936442, 30.302236);
    sightsMultigraph.AddVertex("Исакиевский собор", 59.934179, 30.306102);
    sightsMultigraph.AddVertex("Спас на Крови", 59.940213, 30.328921);
    sightsMultigraph.AddVertex("Петропавловская крепость", 59.950137, 30.316697);

    sightsMultigraph.AddEdge("Казанский собор", "Адмиралтейство", 15, 0, "пешком");
    sightsMultigraph.AddEdge("Казанский собор", "Дворцовая площадь", 10, 0, "пешком");
    sightsMultigraph.AddEdge("Казанский собор", "Медный всадник", 20, 0, "пешком");
    sightsMultigraph.AddEdge("Казанский собор", "Исакиевский собор", 16, 0, "пешком");
    sightsMultigraph.AddEdge("Казанский собор", "Спас на Крови", 8, 0, "пешком");
    sightsMultigraph.AddEdge("Казанский собор", "Петропавловская крепость", 29, 0, "пешком");

    sightsMultigraph.AddEdge("Адмиралтейство", "Дворцовая площадь", 9, 0, "пешком");
    sightsMultigraph.AddEdge("Адмиралтейство", "Медный всадник", 6, 0, "пешком");
    sightsMultigraph.AddEdge("Адмиралтейство", "Исакиевский собор", 8, 0, "пешком");
    sightsMultigraph.AddEdge("Адмиралтейство", "Спас на Крови", 22, 0, "пешком");
    sightsMultigraph.AddEdge("Адмиралтейство", "Петропавловская крепость", 22, 0, "пешком");

    sightsMultigraph.AddEdge("Дворцовая площадь", "Медный всадник", 12, 0, "пешком");
    sightsMultigraph.AddEdge("Дворцовая площадь", "Исакиевский собор", 12, 0, "пешком");
    sightsMultigraph.AddEdge("Дворцовая площадь", "Спас на Крови", 12, 0, "пешком");
    sightsMultigraph.AddEdge("Дворцовая площадь", "Петропавловская крепость", 21, 0, "пешком");

    sightsMultigraph.AddEdge("Медный всадник", "Исакиевский собор", 7, 0, "пешком");
    sightsMultigraph.AddEdge("Медный всадник", "Спас на Крови", 25, 0, "пешком");
    sightsMultigraph.AddEdge("Медный всадник", "Петропавловская крепость", 26, 0, "пешком");

    sightsMultigraph.AddEdge("Исакиевский собор", "Спас на Крови", 22, 0, "пешком");
    sightsMultigraph.AddEdge("Исакиевский собор", "Петропавловская крепость", 29, 0, "пешком");

    sightsMultigraph.AddEdge("Спас на Крови", "Петропавловская крепость", 20, 0, "пешком");

    const int taxiCostPerKM = 35;
    sightsMultigraph.AddEdge("Казанский собор", "Адмиралтейство", 9, taxiCostPerKM * 2.4, "на такси");
    sightsMultigraph.AddEdge("Казанский собор", "Дворцовая площадь", 4, taxiCostPerKM * 1, "на такси");
    sightsMultigraph.AddEdge("Казанский собор", "Медный всадник", 8, taxiCostPerKM * 1.9, "на такси");
    sightsMultigraph.AddEdge("Казанский собор", "Исакиевский собор", 5, taxiCostPerKM * 1.5, "на такси");
    sightsMultigraph.AddEdge("Казанский собор", "Спас на Крови", 3, taxiCostPerKM * 0.4, "на такси");
    sightsMultigraph.AddEdge("Казанский собор", "Петропавловская крепость", 7, taxiCostPerKM * 2.6, "на такси");

    sightsMultigraph.AddEdge("Адмиралтейство", "Дворцовая площадь", 9, taxiCostPerKM * 3.3, "на такси");
    sightsMultigraph.AddEdge("Адмиралтейство", "Медный всадник", 4, taxiCostPerKM * 1.3, "на такси");
    sightsMultigraph.AddEdge("Адмиралтейство", "Исакиевский собор", 5, taxiCostPerKM * 1.2, "на такси");
    sightsMultigraph.AddEdge("Адмиралтейство", "Спас на Крови", 9, taxiCostPerKM * 3.3, "на такси");
    sightsMultigraph.AddEdge("Адмиралтейство", "Петропавловская крепость", 12, taxiCostPerKM * 4.5, "на такси");

    sightsMultigraph.AddEdge("Дворцовая площадь", "Медный всадник", 5, taxiCostPerKM * 1.9, "на такси");
    sightsMultigraph.AddEdge("Дворцовая площадь", "Исакиевский собор", 7, taxiCostPerKM * 1.6, "на такси");
    sightsMultigraph.AddEdge("Дворцовая площадь", "Спас на Крови", 4, taxiCostPerKM * 0.85, "на такси");
    sightsMultigraph.AddEdge("Дворцовая площадь", "Петропавловская крепость", 9, taxiCostPerKM * 2.7, "на такси");

    sightsMultigraph.AddEdge("Медный всадник", "Исакиевский собор", 2, taxiCostPerKM * 0.45, "на такси");
    sightsMultigraph.AddEdge("Медный всадник", "Спас на Крови", 5, taxiCostPerKM * 2.4, "на такси");
    sightsMultigraph.AddEdge("Медный всадник", "Петропавловская крепость", 7, taxiCostPerKM * 3.3, "на такси");

    sightsMultigraph.AddEdge("Исакиевский собор", "Спас на Крови", 8, taxiCostPerKM * 2.2, "на такси");
    sightsMultigraph.AddEdge("Исакиевский собор", "Петропавловская крепость", 10, taxiCostPerKM * 2.2, "на такси");

    sightsMultigraph.AddEdge("Спас на Крови", "Петропавловская крепость", 7, taxiCostPerKM * 3.2, "на такси");
}
void MapWidget::SendFirstSight()
{
    WebChannel->registerObject("Sight", Sights.at(0));
    page()->runJavaScript("GetSight(0);");
}
void MapWidget::SendNextSight(int i)
{
    if(i >= Sights.size())
        return;
    WebChannel->registerObject("Sight", Sights.at(i));
    page()->runJavaScript("GetSight("+QString::number(i)+");");
}
void MapWidget::SetMaxCost(QString maxCostStr)
{
    bool success;
    MaxCost = maxCostStr.toInt(&success);
    if((!success)||(MaxCost<0))
    {
        MaxCost = -1;
        QMessageBox msgError;
        msgError.setText("Сумма должна быть неотрицательным целым числом");
        msgError.exec();
    }
}
void MapWidget::FindOptimalWay()
{
    if(MaxCost == -1)
        return;
    if(!sightsMultigraph.CheckGraphInvariant(ChosenSights))
    {
        QMessageBox msgError;
        msgError.setText("Не удалось найти оптимальный путь");
        msgError.exec();
        return;
    }
    vector<Route *> result = sightsMultigraph.FindOptimalWay(ChosenSights, MaxCost);
    if(result.size()==0)
    {
        QMessageBox msgError;
        msgError.setText("Не удалось найти оптимальный путь");
        msgError.exec();
        return;
    }
    QMessageBox msgResult;
    QString resultStr = "Оптимальный путь:\n\n";
    for(int i = 0; i<result.size(); i++)
    {
        resultStr += QString::number(i+1);
        resultStr += ") Начальная достопримечательность: ";
        resultStr += result.at(i)->BeginSight;
        resultStr += "\n";
        resultStr += "Конечная достопримечательность: ";
        resultStr += result.at(i)->EndSight;
        resultStr += "\n";
        resultStr += "Способ перемещения: ";
        resultStr += result.at(i)->Labels.Vehicle;
        resultStr += "\n";
        resultStr += "Время в пути: ";
        resultStr += QString::number(result.at(i)->Labels.Time);
        resultStr += " минут\n";
        resultStr += "Стоимость: ";
        resultStr += QString::number(result.at(i)->Labels.Cost);
        resultStr += " рублей\n";
        resultStr += "\n\n";
    }
    msgResult.setText(resultStr);
    msgResult.exec();
}
void MapWidget::GetNextChoosenSight(QString name, int count)
{
    if(count < 2)
    {
        QMessageBox msgError;
        msgError.setText("Выберите хотя бы две достопримечательности");
        msgError.exec();
        return;
    }
    ChosenSights.push_back(name);
    if(ChosenSights.size() == count)
        FindOptimalWay();
    page()->runJavaScript("SendChoosenSight("+QString::number(ChosenSights.size())+");");
}
void MapWidget::GetFirstChoosenSight()
{
    ChosenSights.clear();
    page()->runJavaScript("SendChoosenSight(0);");
}
MapWidget::~MapWidget()
{
    delete WebChannel;
    exit(0);
}
void MapWidget::SaveSightsMultigraph(QString filename)
{
    if(sightsMultigraph.IsEmpty())
        return;
    sightsMultigraph.Serialize(filename);
}
void MapWidget::LoadSightsMultigraph(QString filename, bool isInit)
{
    sightsMultigraph.Clear();
    page()->runJavaScript("Clear();");
    if(!sightsMultigraph.Deserialize(filename))
    {
        QMessageBox msgError;
        msgError.setText("Ошибка загрузки");
        msgError.exec();
    }
    Sights = sightsMultigraph.GetSights();
    if(!isInit)
        SendFirstSight();
}
