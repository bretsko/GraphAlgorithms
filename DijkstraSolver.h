#pragma once

#include "Graph.h"
#include "Common.h"
#include "Solver.h"


class DijkstraSolver : public Solver {
public:

    DijkstraSolver(const GraphPtr & graph);

    virtual ~DijkstraSolver() = default;

    DijkstraSolver(const DijkstraSolver& that) = delete;
    DijkstraSolver& operator=(const DijkstraSolver& that) = delete;

    bool solve(const string &src, const string &dest);
    bool solve( GraphPtr graph, VertexPtr src, VertexPtr dest);

    bool solve( VertexPtr src, VertexPtr dest);

    VertexPtr popNonVisited();

    inline VertexPtr findVertex(const string &vertexName){
        return getGraph()->findVertex(vertexName);
    }

    void printDistances();


    bool updateVertex(const VertexPtr &vert, u_int32_t distance);
private:

    VertexPtrSet vertexPtrSet;
};



