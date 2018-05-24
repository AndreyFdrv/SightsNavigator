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
