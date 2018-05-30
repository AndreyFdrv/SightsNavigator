#include "SightsMultigraph.h"
#include <QFile>
#include <sstream>
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
bool SightsMultigraph::CheckGraphInvariant(vector<QString> chosenSights)
{
    if(chosenSights.size() < 2)
        return false;
    Vertex *beginVertex = Multigraph::GetVertexByName(chosenSights[0]);
    vector<bool> *isVerticesVisited=new vector<bool>();
    for(int i=0; i<Multigraph::Vertices.size(); i++)
        isVerticesVisited->push_back(false);
    for(int i=1; i<chosenSights.size(); i++)
    {
        if(!Multigraph::IsWayExist(beginVertex, Multigraph::GetVertexByName(chosenSights[i]), isVerticesVisited))
            return false;
        for(int j=0; j<Multigraph::Vertices.size(); j++)
            (*isVerticesVisited)[j]=false;
    }
    return true;
}
bool SightsMultigraph::Serialize(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly))
        return false;
    file.write(to_string(Sights.size()).c_str());
    file.write("\r\n");
    for(int i=0; i<Sights.size(); i++)
    {
        file.write((Sights[i]->getName()).toStdString().c_str());
        file.write("\t");
        file.write(to_string(Sights[i]->getX()).c_str());
        file.write("\t");
        file.write(to_string(Sights[i]->getY()).c_str());
        file.write("\t");
        file.write("\r\n");
    }
    int edgesCount = Multigraph::EdgesCount();
    file.write(to_string(edgesCount).c_str());
    file.write("\r\n");
    for(int i=0; i<Vertices.size(); i++)
    {
        QString beginName = Vertices[i]->Name;
        for(int j=0; j<Vertices[i]->OutgoingEdges.size(); j++)
        {
            QString endName = Vertices[i]->OutgoingEdges[j]->EndVertex->Name;
            if(QString::compare(beginName, endName, Qt::CaseSensitive)<0)
                continue;
            for(int k = 0; k<Vertices[i]->OutgoingEdges[j]->EdgesLabels.size(); k++)
            {
                file.write(beginName.toStdString().c_str());
                file.write("\t");
                file.write(endName.toStdString().c_str());
                file.write("\t");
                file.write(to_string(Vertices[i]->OutgoingEdges[j]->EdgesLabels[k]->Time).c_str());
                file.write("\t");
                file.write(to_string(Vertices[i]->OutgoingEdges[j]->EdgesLabels[k]->Cost).c_str());
                file.write("\t");
                file.write((Vertices[i]->OutgoingEdges[j]->EdgesLabels[k]->Vehicle).toStdString().c_str());
                file.write("\t");
                file.write("\r\n");
            }
        }
    }
    file.close();
    return true;
}
bool SightsMultigraph::Deserialize(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return false;
    QString verticesCountStr = file.readLine();
    bool success;
    int verticesCount = verticesCountStr.toInt(&success);
    if(!success)
    {
        file.close();
        return false;
    }
    for(int i=0; i<verticesCount; i++)
    {
        QStringList sightStr = QString(file.readLine()).split('\t');
        if(sightStr.size() < 3)
        {
            file.close();
            return false;
        }
        QString name = sightStr[0];
        Multigraph::AddVertex(name);
        double x = sightStr[1].toDouble(&success);
        if(!success)
        {
            file.close();
            return false;
        }
        double y = sightStr[2].toDouble(&success);
        if(!success)
        {
            file.close();
            return false;
        }
        Sights.push_back(new Sight(x, y, name));
    }
    QString edgesCountStr = file.readLine();
    int edgesCount = edgesCountStr.toInt(&success);
    if(!success)
    {
        file.close();
        return false;
    }
    for(int i=0; i<edgesCount; i++)
    {
        QStringList edgeStr = QString(file.readLine()).split('\t');
        if(edgeStr.size() < 5)
        {
            file.close();
            return false;
        }
        QString beginName = edgeStr[0];
        QString endName = edgeStr[1];
        int time = edgeStr[2].toInt(&success);
        if(!success)
        {
            file.close();
            return false;
        }
        int cost = edgeStr[3].toInt(&success);
        if(!success)
        {
            file.close();
            return false;
        }
        QString vehicle = edgeStr[4];
        AddEdge(beginName, endName, time, cost, vehicle);
    }
    file.close();
    return true;
}
void SightsMultigraph::Clear()
{
    Sights.clear();
    Multigraph::Clear();
}
