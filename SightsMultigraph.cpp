#include "SightsMultigraph.h"
SightsMultigraph::SightsMultigraph()
{

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
