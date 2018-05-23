//Неориентированный граф маршрутов между достопримечательностями
//Вершины содержат названия достопримечательностей
//Рёбра содержат информацию о маршрутах
#ifndef SIGHTSMULTIGRAPH_H
#define SIGHTSMULTIGRAPH_H
#include <vector>
#include "QString"
#include "Multigraph.h"
using namespace std;

struct EdgeLabels
{
    unsigned int Time;//время в пути в минутах
    unsigned int Cost;//стоимость в рублях
    QString Vehicle;//транспорт(пешком, на такси, ...)
};
class SightsMultigraph : public Multigraph<EdgeLabels*>
{
public:
    SightsMultigraph();
    void AddEdge(QString beginVertexName, QString endVertexName, unsigned int time, unsigned int cost, QString vehicle);
};

#endif // MULTIGRAPH_H
