#include "EdgesGroupManipulator.h"

EdgesGroupManipulator::EdgesGroupManipulator(multigraph::Multigraph<EdgeLabels>::EdgesGroup* value)
{
    EdgesGroupPointer = value;
}
ostream& operator<< (ostream& os, const EdgesGroupManipulator& egm)
{
    if(!egm.EdgesGroupPointer)
        return os;
    QString beginName = egm.EdgesGroupPointer->BeginVertex->Name;
    QString endName = egm.EdgesGroupPointer->EndVertex->Name;
    if(QString::compare(beginName, endName, Qt::CaseSensitive)<0)
        return os;
    vector<EdgeLabels *> edgesLabels = egm.EdgesGroupPointer->EdgesLabels;
    for(int i=0; i<edgesLabels.size(); i++)
    {
        os << beginName.toStdString() << "\t" << endName.toStdString() << edgesLabels[i]->Cost << edgesLabels[i]->Time
           << edgesLabels[i]->Vehicle.toStdString() << "\n";
    }
    return os;
}
