#ifndef EDGESGROUPMANIPULATOR_H
#define EDGESGROUPMANIPULATOR_H
#include "SightsMultigraph.h"

class EdgesGroupManipulator
{
public:
    EdgesGroupManipulator(multigraph::Multigraph<EdgeLabels>::EdgesGroup* value);
    friend ostream& operator<< (ostream& os, const EdgesGroupManipulator& egm);
private:
    multigraph::Multigraph<EdgeLabels>::EdgesGroup* EdgesGroupPointer;
};

#endif // EDGESGROUPMANIPULATOR_H
