#pragma once

#include "Common.h"
#include "SolverInterface.h"
#include "Graph.h"
#include <assert.h>

class DijkstraSolver : public SolverInterface {
public:

    DijkstraSolver(const Graph & graph);

    ~DijkstraSolver() = default;

    DijkstraSolver(const DijkstraSolver& that) = delete;
    DijkstraSolver& operator=(const DijkstraSolver& that) = delete;

    virtual bool solve(const string &src, const string &dest);
    virtual bool solve( GraphPtr graph, VertexPtr src, VertexPtr dest);

    inline virtual bool solve( VertexPtr src,  VertexPtr dest){
        assert (src!=nullptr && dest!=nullptr);
        GraphPtr graphPtr = getGraph();
        return solve(graphPtr,src,dest);
    }

    bool updateVertex(VertexPtr vert, u_int32_t distance);

    VertexPtr popNonVisited();

    inline bool contains(const VertexPtr &vertex){
        return getGraph()->contains(vertex);
    }

    inline VertexPtr findVertex(const std::__cxx11::string &vertexName){
        return getGraph()->findVertex(vertexName);
    }

    void printDistances();

private:
    VertexPtrSet vertexPtrSet;
};



