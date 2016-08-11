
#pragma once

#include "Common.h"

class SolverInterface{

public:

    SolverInterface(const Graph & graph) : m_graph(make_unique<Graph>(graph)) {}

    virtual ~SolverInterface() = default;

    virtual bool solve(const string &src, const string &dest) = 0;

    virtual bool solve(GraphPtr graph, VertexPtr src, VertexPtr dest) = 0;

    virtual bool solve(const VertexPtr src, const VertexPtr dest){
        return solve(m_graph,src,dest);
    }

    inline GraphPtr getGraph(){
        return m_graph;
    }

private:

    GraphPtr m_graph;
};
