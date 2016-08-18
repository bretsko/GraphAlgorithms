
#pragma once

#include "Common.h"

class Solver{

public:

    Solver(const GraphPtr & graph) : m_graph(graph) {}

    virtual ~Solver() = default;

    inline GraphPtr getGraph(){
        return m_graph;
    }

    void visit(VertexPtr vert);

    void printMST(const shared_ptr<EdgePtrSet> & MST);

private:

    GraphPtr m_graph;
};
