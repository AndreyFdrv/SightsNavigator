#ifndef MULTIGRAPH_H
#define MULTIGRAPH_H
#include <vector>
#include "QString"
using namespace std;
namespace multigraph
{
template <class edgeLabelType> class Multigraph
{
protected:
    struct Vertex;
    struct EdgesGroup//группа всех рёбер с совпадающими началом и концом
    {
        Vertex *BeginVertex;
        Vertex *EndVertex;
        vector<edgeLabelType> EdgesLabels;
    };
    struct Vertex
    {
        QString Name;
        vector<EdgesGroup *> OutgoingEdges;
    };
    vector<Vertex *> Vertices;
    Vertex *GetVertexByName(QString name)
    {
        for(int i=0; i<Vertices.size(); i++)
        {
            if(Vertices.at(i)->Name == name)
                return Vertices.at(i);
        }
        return NULL;
    }
public:
    Multigraph()
    {

    }
    bool IsVertexExist(QString name)
    {
        for(int i=0; i<Vertices.size(); i++)
        {
            QString vertexName = Vertices.at(i)->Name;
            if(vertexName == name)
                return true;
        }
        return false;
    }
    void AddVertex(QString name)
    {
        if(IsVertexExist(name))
            throw "Вершина с таким значением уже существует";
        Vertex *vertex = new Vertex;
        vertex->Name = name;
        Vertices.push_back(vertex);
    }
    void AddEdge(QString beginVertexName, QString endVertexName, edgeLabelType label)
    {
        if(!IsVertexExist(beginVertexName))
            throw "Начальной вершины не существует";
        if(!IsVertexExist(endVertexName))
            throw "Конечной вершины не существует";
        Vertex *beginVertex = GetVertexByName(beginVertexName);
        bool isEdgesGroupExist = false;
        for(int i=0; i<beginVertex->OutgoingEdges.size(); i++)
        {
            if(beginVertex->OutgoingEdges.at(i)->EndVertex->Name == endVertexName)
            {
                beginVertex->OutgoingEdges.at(i)->EdgesLabels.push_back(label);
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
            edgesGroup->EdgesLabels.push_back(label);
            beginVertex->OutgoingEdges.push_back(edgesGroup);
        }
        for(int i=0; i<endVertex->OutgoingEdges.size(); i++)
        {
            if(endVertex->OutgoingEdges.at(i)->EndVertex->Name == beginVertexName)
            {
                endVertex->OutgoingEdges.at(i)->EdgesLabels.push_back(label);
                return;
            }
        }
        edgesGroup = new EdgesGroup();
        edgesGroup->BeginVertex = endVertex;
        edgesGroup->EndVertex = beginVertex;
        edgesGroup->EdgesLabels.push_back(label);
        endVertex->OutgoingEdges.push_back(edgesGroup);
    }
    vector<edgeLabelType> GetEdgesLabels(QString beginVertexName, QString endVertexName)
    {
        Vertex *beginVertex = GetVertexByName(beginVertexName);
        for(int i = 0; i < beginVertex->OutgoingEdges.size(); i++)
        {
            if(beginVertex->OutgoingEdges.at(i)->EndVertex->Name == endVertexName)
                return beginVertex->OutgoingEdges.at(i)->EdgesLabels;
        }
        vector<edgeLabelType> emptyResult;
        return emptyResult;
    }
};
}

#endif // MULTIGRAPH_H
