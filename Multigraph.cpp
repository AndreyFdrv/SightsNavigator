#include "Multigraph.h"
Multigraph::Multigraph()
{

}
bool Multigraph::IsVertexExist(QString name)
{
    for(int i=0; i<Vertices.size(); i++)
    {
        QString vertexName = Vertices.at(i)->Name;
        if(vertexName == name)
            return true;
    }
    return false;
}
void Multigraph::AddVertex(QString name)
{
    if(IsVertexExist(name))
        throw "Вершина с таким именем уже существует";
    Vertex *vertex = new Vertex;
    vertex->Name = name;
    Vertices.push_back(vertex);
}
Vertex *Multigraph::GetVertexByName(QString name)
{
    for(int i=0; i<Vertices.size(); i++)
    {
        if(Vertices.at(i)->Name == name)
            return Vertices.at(i);
    }
    return NULL;
}
void Multigraph::AddEdge(QString beginVertexName, QString endVertexName, unsigned int time, unsigned int cost,
                         QString vehicle)
{
    if(!IsVertexExist(beginVertexName))
        throw "Начальной вершины не существует";
    if(!IsVertexExist(endVertexName))
        throw "Конечной вершины не существует";
    Vertex *beginVertex = GetVertexByName(beginVertexName);
    EdgeLabels *labels = new EdgeLabels();
    labels->Cost = cost;
    labels->Time = time;
    labels->Vehicle = vehicle;
    bool isEdgesGroupExist = false;
    for(int i=0; i<beginVertex->OutgoingEdges.size(); i++)
    {
        if(beginVertex->OutgoingEdges.at(i)->EndVertex->Name == endVertexName)
        {
            beginVertex->OutgoingEdges.at(i)->EdgesLabels.push_back(labels);
            isEdgesGroupExist = true;
            break;
        }
    }
    Vertex *endVertex = GetVertexByName(endVertexName);
    EdgesGroup *edgesGroup = new EdgesGroup();
    if(!isEdgesGroupExist)
    {
        edgesGroup->BeginVertex = beginVertex;
        edgesGroup->EndVertex = endVertex;
        edgesGroup->EdgesLabels.push_back(labels);
        beginVertex->OutgoingEdges.push_back(edgesGroup);
    }
    for(int i=0; i<endVertex->OutgoingEdges.size(); i++)
    {
        if(endVertex->OutgoingEdges.at(i)->EndVertex->Name == beginVertexName)
        {
            endVertex->OutgoingEdges.at(i)->EdgesLabels.push_back(labels);
            return;
        }
    }
    edgesGroup = new EdgesGroup();
    edgesGroup->BeginVertex = endVertex;
    edgesGroup->EndVertex = beginVertex;
    edgesGroup->EdgesLabels.push_back(labels);
    endVertex->OutgoingEdges.push_back(edgesGroup);
}
