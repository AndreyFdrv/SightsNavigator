//Неориентированный граф маршрутов между достопримечательностями
//Вершины содержат названия достопримечательностей
//Рёбра содержат информацию о маршрутах
#ifndef MULTIGRAPH_H
#define MULTIGRAPH_H
#include <vector>
#include "QString"
using namespace std;
struct Vertex;
struct EdgeLabels
{
    unsigned int Time;//время в пути в минутах
    unsigned int Cost;//стоимость в рублях
    QString Vehicle;//транспорт(пешком, на такси, ...)
};
struct EdgesGroup//группа всех рёбер с совпадающими началом и концом
{
    Vertex *BeginVertex;
    Vertex *EndVertex;
    vector<EdgeLabels *> EdgesLabels;
};
struct Vertex
{
    QString Name;//имя достопримечательности
    vector<EdgesGroup *> OutgoingEdges;
};

class Multigraph
{
private:
    vector<Vertex *> Vertices;
    Vertex *GetVertexByName(QString name);
public:
    Multigraph();
    bool IsVertexExist(QString name);
    void AddVertex(QString name);
    void AddEdge(QString beginVertexName, QString endVertexName, unsigned int time, unsigned int cost, QString vehicle);
};

#endif // MULTIGRAPH_H
