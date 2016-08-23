#pragma once

#include "PathFinderInterface.h"

class DijkstraSolver : public PathFinderInterface{

    typedef set <VertexPtr, CompareVerticesByDistance> VertexPtrSet;
    typedef shared_ptr <VertexPtrSet> VertexPtrSetPtr;

public:

    DijkstraSolver(const GraphPtr & graphArg);
    DijkstraSolver(const DijkstraSolver& that) = delete;
    DijkstraSolver& operator=(const DijkstraSolver& that) = delete;
    virtual ~DijkstraSolver() =default;

    void printDistances() const;

    virtual bool solveImpl(const GraphPtr &graphPtr, const VertexPtr& src, const VertexPtr& dest);
    virtual bool solveImplOptimized(const GraphPtr &graphPtr, const VertexPtr& src, const VertexPtr &dest);

private:

    const VertexPtr popNonVisited();

    bool updateVertex(const VertexPtr &vert, u_int32_t distance);

    inline  const VertexPtrSetPtr vertexPtrSet() const{
        return m_vertexPtrSet;
    }

    virtual inline const GraphPtr graph() const{
        return m_graph;
    }

    void sortAllEdges();

    GraphPtr m_graph;

    VertexPtrSetPtr m_vertexPtrSet;
};





