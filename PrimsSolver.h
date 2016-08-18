#pragma once

#include "Solver.h"


//In Prim's, you always keep a connected component, starting with a single vertex.
//You look at all edges from the current component to other vertices and
//find the smallest among them. You then add the neighbouring vertex to the component,
//increasing its size by 1. In N-1 steps, every vertex would be merged to the current one
// if we have a connected graph.

class PrimsSolver : public Solver
{
public:
    PrimsSolver(const GraphPtr & graph);

    ~PrimsSolver() = default;

    PrimsSolver(const PrimsSolver& that) = delete;
    PrimsSolver& operator=(const PrimsSolver& that) = delete;

    shared_ptr<EdgePtrSet> solve(const VertexPtr &vert);
    shared_ptr<EdgePtrSet> solve(const string &vertexName);
};





