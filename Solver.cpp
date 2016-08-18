#include "Solver.h"
#include "Graph.h"

void Solver::printMST(const shared_ptr<EdgePtrSet> & MST){
    cerr << "\nMST, size "<< MST->size() << ":\n" << endl;

    for( const EdgePtr &e : *MST ){
        e->print(true);
    }
}

void Solver::visit(VertexPtr vert){
    getGraph()->visit(vert);
}
