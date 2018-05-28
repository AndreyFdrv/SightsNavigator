#ifndef MULTIGRAPH_H
#define MULTIGRAPH_H
#include <vector>
#include <QString>
#include "MultigraphException.h"
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
        vector<edgeLabelType *> EdgesLabels;
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
    int GetVertexIndexByName(QString name)
    {
        for(int i=0; i<Vertices.size(); i++)
        {
            if(Vertices.at(i)->Name == name)
                return i;
        }
        return -1;
    }
    bool IsWayExist(Vertex *beginVertex, Vertex *endVertex, vector<bool> *isVerticesVisited)
    {
        if (beginVertex->Name == endVertex->Name)
            return true;
        (*isVerticesVisited)[GetVertexIndexByName(beginVertex->Name)] = true;
        for(int i=0; i<beginVertex->OutgoingEdges.size(); i++)
        {
            Vertex *edgeEndVertex = beginVertex->OutgoingEdges[i]->EndVertex;
            if((!(*isVerticesVisited)[GetVertexIndexByName(edgeEndVertex->Name)])&&
                    IsWayExist(edgeEndVertex, endVertex, isVerticesVisited))
                return true;
        }
        return false;
    }
    class Allocator
    {
    public:
        Allocator()
        {

        }
        void ReturnAll()
        {
            for_each(VerticesPool.begin(), VerticesPool.end(), [](Vertex* i)
            {
                delete i;
            });
            for_each(EdgesPool.begin(), EdgesPool.end(), [](EdgesGroup* i)
            {
                delete i;
            });
            VerticesPool.clear();
            EdgesPool.clear();
        }
        virtual ~Allocator()
        {
            ReturnAll();
        }
        Vertex *AddVertex()
        {
            Vertex *vertex = new Vertex();
            VerticesPool.push_back(vertex);
            return vertex;
        }
        EdgesGroup *AddEdgesGroup()
        {
            EdgesGroup *edgesGroup = new EdgesGroup();
            EdgesPool.push_back(edgesGroup);
            return edgesGroup;
        }
        void ReturnVertex(Vertex* vertex)
        {
            auto pos = find(VerticesPool.begin(), VerticesPool.end(), vertex);
            if(pos == VerticesPool.end())
            {
                throw MultigraphAllocatorException("Вершины не существует", __LINE__, __FUNCTION__, __TIMESTAMP__);
                return;
            }
            VerticesPool.erase(pos);
            delete vertex;
        }
        void ReturnEdges(EdgesGroup *edges)
        {
            auto pos = find(EdgesPool.begin(), EdgesPool.end(), edges);
            if(pos == EdgesPool.end())
            {
                throw MultigraphAllocatorException("Рёбер не существует", __LINE__, __FUNCTION__, __TIMESTAMP__);
                return;
            }
            EdgesPool.erase(pos);
            delete edges;
        }
    private:
        vector<Vertex *> VerticesPool;
        vector<EdgesGroup *> EdgesPool;
    };
    Allocator allocator;
public:
    class VertexIterator
    {
    private:
        size_t Position;
        vector<Vertex *> Vertices;
        typename vector<Vertex *>::iterator Iterator;
    public:
        VertexIterator(const VertexIterator& iterator)
        {
            Vertices = iterator.Vertices;
            Position = iterator.Position;
            Iterator = Vertices->begin();
            for(size_t i = 0; i < Position; i++)
                Iterator++;
        }
        VertexIterator(const size_t position, vector<Vertex *> vertices)
        {
            Position = position;
            Vertices = vertices;
            Iterator = Vertices->begin();
            for(size_t i = 0; i < _position; i++)
                Iterator++;
        }
        VertexIterator& operator ++ ()
        {
            if(Vertives->size() < (Position + 1))
            {
                throw IncorrectIndexException("Индекс указывает за пределы массива", __LINE__, __FUNCTION__, __TIMESTAMP__);
                return *this;
            }
            Position++;
            Iterator++;
            return *this;
        }
        VertexIterator& operator += (const size_t k)
        {
            if(_vertexP->size() < (_position + k))
            {
                throw IncorrectIndexException("Индекс указывает за пределы массива", __LINE__, __FUNCTION__, __TIMESTAMP__);
                return *this;
            }
            Position += k;
            for(size_t i = 0; i < k; i++)
                Iterator++;
            return *this;
        }
        bool operator == (const VertexIterator& iterator)
        {
            return (Iterator == iterator.Iterator);
        }
        bool operator != (const VertexIterator& iterator)
        {
            return (Iterator != iterator.Iterator);
        }
        Vertex* operator * ()
        {
            if(Position == Vertices->size())
            {
                throw IncorrectIndexException("Индекс указывает за пределы массива", __LINE__, __FUNCTION__, __TIMESTAMP__);
                return NULL;
            }
            return *Iterator;
        }
    };
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
            throw VertexExistingException("Вершина с таким значением уже существует", __LINE__, __FUNCTION__,
                                          __TIMESTAMP__, name);
        Vertex *vertex = allocator.AddVertex();
        vertex->Name = name;
        Vertices.push_back(vertex);
    }
    void AddEdge(QString beginVertexName, QString endVertexName, edgeLabelType *label)
    {
        if(!IsVertexExist(beginVertexName))
            throw VertexExistingException("Вершины не существует", __LINE__, __FUNCTION__, __TIMESTAMP__, beginVertexName);
        if(!IsVertexExist(endVertexName))
            throw VertexExistingException("Вершины не существует", __LINE__, __FUNCTION__, __TIMESTAMP__, endVertexName);
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
        if(!isEdgesGroupExist)
        {
            EdgesGroup *edgesGroup = allocator.AddEdgesGroup();
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
        EdgesGroup *edgesGroup = allocator.AddEdgesGroup();
        edgesGroup->BeginVertex = endVertex;
        edgesGroup->EndVertex = beginVertex;
        edgesGroup->EdgesLabels.push_back(label);
        endVertex->OutgoingEdges.push_back(edgesGroup);
    }
    void Clear()
    {
        allocator.ReturnAll();
        Vertices.clear();
    }
    vector<edgeLabelType *> GetEdgesLabels(QString beginVertexName, QString endVertexName)
    {
        Vertex *beginVertex = GetVertexByName(beginVertexName);
        for(int i = 0; i < beginVertex->OutgoingEdges.size(); i++)
        {
            if(beginVertex->OutgoingEdges.at(i)->EndVertex->Name == endVertexName)
                return beginVertex->OutgoingEdges.at(i)->EdgesLabels;
        }
        vector<edgeLabelType *> emptyResult;
        return emptyResult;
    }
};
}

#endif // MULTIGRAPH_H
