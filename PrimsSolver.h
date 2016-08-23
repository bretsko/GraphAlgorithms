#pragma once

#include "Common.h"
#include "Edge.h"
#include "Graph.h"

//In Prim's, you always keep a connected component, starting with a single vertex.
//You look at all edges from the current component to other vertices and
//find the smallest among them. You then add the neighbouring vertex to the component,
//increasing its size by 1. In N-1 steps, every vertex would be merged to the current one
// if we have a connected graph.

typedef EdgePtrSetComparedByName EdgePtrSet;

class PrimsSolver
{
public:
    PrimsSolver(const GraphPtr & graph);

    ~PrimsSolver() = default;

    PrimsSolver(const PrimsSolver& that) = delete;
    PrimsSolver& operator=(const PrimsSolver& that) = delete;

    const shared_ptr<EdgePtrSet> solve(const VertexPtr &vert);

    const shared_ptr<EdgePtrSet> solve(const string &vertexName);

    inline const GraphPtr graph()const {
        return m_graph;
    }

    void printMST(const shared_ptr<EdgePtrSet> & MST);

    inline void visit(VertexPtr vert){
        graph()->visit(vert);
    }

private:
    GraphPtr m_graph;
};





