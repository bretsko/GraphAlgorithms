
#pragma once

#include "Common.h"
#include "Graph.h"


class PathFinderInterface {

public:

    bool solve(const string &src, const string &dest, bool optimized);

    virtual void printDistances()const = 0;

    virtual ~PathFinderInterface()  = default;

protected:

    virtual const GraphPtr graph() const = 0;

    virtual bool solveImpl( const GraphPtr& graph, const VertexPtr &src, const VertexPtr& dest) = 0;

    virtual bool solveImplOptimized( const GraphPtr &graph, const VertexPtr &src, const VertexPtr& dest) = 0;

    inline const VertexPtr findVertex(const string &vertexName){
        return graph()->findVertex(vertexName);
    }
};
