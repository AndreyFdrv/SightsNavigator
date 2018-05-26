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
int SightsMultigraph::ComputeCost(vector<Route *> way)
{
    unsigned int cost = 0;
    for(int i=0; i<way.size(); i++)
        cost += way[i]->Labels.Cost;
    return cost;
}
int SightsMultigraph::ComputeTime(vector<Route *> way)
{
    unsigned int time = 0;
    for(int i=0; i<way.size(); i++)
        time += way[i]->Labels.Time;
    return time;
}
vector<Route *> SightsMultigraph::FindOptimalWayForCurrentSightsOrder(vector<QString> chosenSights, int maxCost)
{
    if(chosenSights.size() < 2)
    {
        vector<Route *> emptyResult;
        return emptyResult;
    }
    Vertex *firstSight = Multigraph::GetVertexByName(chosenSights[0]);
    chosenSights.erase(chosenSights.begin());
    vector<Route *> optimalWay = FindOptimalWayForCurrentSightsOrder(chosenSights, maxCost);
    int optimalCostWithoutFirstSight = ComputeCost(optimalWay);
    if(optimalCostWithoutFirstSight > maxCost)
    {
        vector<Route *> emptyResult;
        return emptyResult;
    }
    vector<EdgeLabels *> edgesLabels = GetEdgesLabels(firstSight->Name, chosenSights[0]);
    bool isSuitableWayExist = false;
    int optimalTime = INT_MAX;
    Route *optimalFirstRoute = new Route();
    for(int i = 0; i < edgesLabels.size(); i++)
    {
        int cost = edgesLabels[i]->Cost + optimalCostWithoutFirstSight;
        if(cost > maxCost)
            continue;
        int time = edgesLabels[i]->Time + ComputeTime(optimalWay);
        if(time < optimalTime)
        {
            optimalTime = time;
            isSuitableWayExist = true;
            optimalFirstRoute->BeginSight = firstSight->Name;
            optimalFirstRoute->EndSight = chosenSights[0];
            optimalFirstRoute->Labels.Cost = edgesLabels[i]->Cost;
            optimalFirstRoute->Labels.Time = edgesLabels[i]->Time;
            optimalFirstRoute->Labels.Vehicle = edgesLabels[i]->Vehicle;
        }
    }
    if(!isSuitableWayExist)
    {
        vector<Route *> emptyResult;
        return emptyResult;
    }
    optimalWay.insert(optimalWay.begin(), optimalFirstRoute);
    return optimalWay;
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
vector<QString> SightsMultigraph::ChangeOrder(vector<QString> chosenSights, int i, int j)
{
    QString temp = chosenSights[i];
    chosenSights[i] = chosenSights[j];
    chosenSights[j] = temp;
    return chosenSights;
}
vector<Route *> SightsMultigraph::FindOptimalWay(vector<QString> chosenSights, int maxCost, int leftChangeIndex,
                                                 int rightChangeIndex, bool isInit)
{
    vector<Route *> optimalWay;
    if(isInit)
    {
        optimalWay = FindOptimalWayForCurrentSightsOrder(chosenSights, maxCost);
    }
    vector<Route *> way;
    if(leftChangeIndex+1<rightChangeIndex)
    {
        way = FindOptimalWay(chosenSights, maxCost, leftChangeIndex+1, rightChangeIndex, false);
        optimalWay = GetBetterWay(optimalWay, way);
    }
    if(rightChangeIndex+1<chosenSights.size())
    {
        way = FindOptimalWay(chosenSights, maxCost, leftChangeIndex, rightChangeIndex+1, false);
        optimalWay = GetBetterWay(optimalWay, way);
    }
    chosenSights = ChangeOrder(chosenSights, leftChangeIndex, rightChangeIndex);
    way = FindOptimalWayForCurrentSightsOrder(chosenSights, maxCost);
    optimalWay = GetBetterWay(optimalWay, way);
    if(leftChangeIndex+1<rightChangeIndex)
    {
        way = FindOptimalWay(chosenSights, maxCost, leftChangeIndex+1, rightChangeIndex, false);
        optimalWay = GetBetterWay(optimalWay, way);
    }
    if(rightChangeIndex+1<chosenSights.size())
    {
        way = FindOptimalWay(chosenSights, maxCost, leftChangeIndex, rightChangeIndex+1, false);
        optimalWay = GetBetterWay(optimalWay, way);
    }
    return optimalWay;
}
