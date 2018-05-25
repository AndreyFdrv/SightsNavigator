#include "SightsMultigraph.h"
SightsMultigraph::SightsMultigraph()
{

}
void SightsMultigraph::AddVertex(QString name, double x, double y)
{
    Sight *sight = new Sight(x, y, name);
    Sights.push_back(sight);
    Multigraph::AddVertex(name);
}
void SightsMultigraph::AddEdge(QString beginVertexName, QString endVertexName, unsigned int time, unsigned int cost,
                         QString vehicle)
{
    EdgeLabels *labels = new EdgeLabels();
    labels->Cost = cost;
    labels->Time = time;
    labels->Vehicle = vehicle;
    Multigraph::AddEdge(beginVertexName, endVertexName, labels);
}
vector<Sight *> SightsMultigraph::GetSights()
{
    return Sights;
}
vector<Route *> SightsMultigraph::FindOptimalWayForCurrentSightsOrder(vector<QString> choosenSights, int maxCost)
{
    //ещё не реализован
    vector<Route *> result;
    for(int i = 0; i < choosenSights.size()-1; i++)
    {
        vector<EdgeLabels *> edgesLabels = Multigraph::GetEdgesLabels(choosenSights.at(i), choosenSights.at(i+1));
        if(edgesLabels.size()==0)
        {
            vector<Route *> emptyResult;
            return emptyResult;
        }
        for(int j = 0; j < edgesLabels.size(); j++)
        {
            if(edgesLabels.at(j)->Vehicle == "пешком")
            {
                Route *route = new Route();
                route->BeginSight = choosenSights.at(i);
                route->EndSight = choosenSights.at(i+1);
                route->Labels.Cost = edgesLabels.at(j)->Cost;
                route->Labels.Time = edgesLabels.at(j)->Time;
                route->Labels.Vehicle = edgesLabels.at(j)->Vehicle;
                result.push_back(route);
            }
        }
    }
    return result;
}
vector<Route *> SightsMultigraph::GetBetterWay(vector<Route *> way1, vector<Route *> way2)
{
    if((way1.size() == 0) && (way2.size() == 0))
        return way1;
    if(way1.size()==0)
        return way2;
    if(way2.size()==0)
        return way1;
    int sum1=0;
    for(int i = 0; i<way1.size(); i++)
    {
        sum1 += way1.at(i)->Labels.Time;
    }
    int sum2=0;
    for(int i = 0; i<way2.size(); i++)
    {
        sum2 += way2.at(i)->Labels.Time;
    }
    return sum1<sum2?way1:way2;
}
vector<QString> SightsMultigraph::ChangeOrder(vector<QString> choosenSights, int i, int j)
{
    QString temp = choosenSights[i];
    choosenSights[i] = choosenSights[j];
    choosenSights[j] = temp;
    return choosenSights;
}
vector<Route *> SightsMultigraph::FindOptimalWay(vector<QString> choosenSights, int maxCost, int leftChangeIndex,
                                                 int rightChangeIndex, bool isInit)
{
    vector<Route *> optimalWay;
    if(isInit)
    {
        optimalWay = FindOptimalWayForCurrentSightsOrder(choosenSights, maxCost);
    }
    vector<Route *> way;
    if(leftChangeIndex+1<rightChangeIndex)
    {
        way = FindOptimalWay(choosenSights, maxCost, leftChangeIndex+1, rightChangeIndex, false);
        optimalWay = GetBetterWay(optimalWay, way);
    }
    if(rightChangeIndex+1<choosenSights.size())
    {
        way = FindOptimalWay(choosenSights, maxCost, leftChangeIndex, rightChangeIndex+1, false);
        optimalWay = GetBetterWay(optimalWay, way);
    }
    choosenSights = ChangeOrder(choosenSights, leftChangeIndex, rightChangeIndex);
    way = FindOptimalWayForCurrentSightsOrder(choosenSights, maxCost);
    optimalWay = GetBetterWay(optimalWay, way);
    if(leftChangeIndex+1<rightChangeIndex)
    {
        way = FindOptimalWay(choosenSights, maxCost, leftChangeIndex+1, rightChangeIndex, false);
        optimalWay = GetBetterWay(optimalWay, way);
    }
    if(rightChangeIndex+1<choosenSights.size())
    {
        way = FindOptimalWay(choosenSights, maxCost, leftChangeIndex, rightChangeIndex+1, false);
        optimalWay = GetBetterWay(optimalWay, way);
    }
    return optimalWay;
}
