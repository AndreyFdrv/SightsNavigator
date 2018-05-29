//Неориентированный граф маршрутов между достопримечательностями
//Вершины содержат названия достопримечательностей
//Рёбра содержат информацию о маршрутах
#ifndef SIGHTSMULTIGRAPH_H
#define SIGHTSMULTIGRAPH_H
#include <vector>
#include "QString"
#include "Multigraph.h"
#include "Sight.h"
using namespace std;

struct EdgeLabels
{
    unsigned int Time;//время в пути в минутах
    unsigned int Cost;//стоимость в рублях
    QString Vehicle;//транспорт(пешком, на такси, ...)
};
struct Route
{
    QString BeginSight;
    QString EndSight;
    EdgeLabels Labels;
};
class EdgesGroupManipulator;
class SightsMultigraph : public multigraph::Multigraph<EdgeLabels>
{
private:
    vector<Sight *> Sights;
    vector<Route *> FindOptimalWayForCurrentSightsOrder(vector<QString> chosenSights, int maxCost);
    vector<Route *> GetBetterWay(vector<Route *> way1, vector<Route *> way2);
    vector<QString> ChangeOrder(vector<QString> chosenSights, int leftChangeIndex, int rightChangeIndex);
    int ComputeCost(vector<Route *> way);
    int ComputeTime(vector<Route *> way);
public:
    friend EdgesGroupManipulator;
    SightsMultigraph();
    void AddVertex(QString name, double x, double y);
    void AddEdge(QString beginVertexName, QString endVertexName, unsigned int time, unsigned int cost, QString vehicle);
    vector<Sight *> GetSights();
    vector<Route *> FindOptimalWay(vector<QString> chosenSights, int maxCost, int leftChangeIndex=0, int rightChangeIndex=1,
                                   bool isInit = true);
    bool CheckGraphInvariant(vector<QString> chosenSights);
};

#endif // MULTIGRAPH_H
