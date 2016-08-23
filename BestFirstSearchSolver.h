#pragma once

#include "PathFinderInterface.h"
#include <functional>

// Uses the estimated distance to the goal for set ordering.
// The location closest to the goal will be explored first.

class BestFirstSearchSolver : public PathFinderInterface {

    typedef std::function<bool(const VertexPtr& lhs, const VertexPtr& rhs)> CompareFunction;
    typedef set <VertexPtr, CompareFunction> VertexPtrSet;
    typedef shared_ptr <VertexPtrSet> VertexPtrSetPtr;

public:

    BestFirstSearchSolver& operator=(const BestFirstSearchSolver& that) = delete;
    BestFirstSearchSolver(const GraphPtr & graphArg);
    virtual ~BestFirstSearchSolver() = default;
    BestFirstSearchSolver(const BestFirstSearchSolver& that) = delete;

    virtual  bool solveImpl(const GraphPtr& graphPtr, const VertexPtr &src, const VertexPtr &dest);
    bool solveImpl(const GraphPtr& graphPtr, const VertexPtr &src, const VertexPtr& dest, bool earlyExit);

    virtual bool solveImplOptimized(const GraphPtr &graphPtr, const VertexPtr& src, const VertexPtr &dest);
    bool solveImplOptimized(const GraphPtr& graphPtr, const VertexPtr &src, const VertexPtr &dest, bool earlyExit);

    void printDistances()const;

    void printManhattanDistances()const;

private:

    bool compareFunction(const VertexPtr& lhs, const VertexPtr& rhs) const;

    virtual inline const GraphPtr graph() const{
        return m_graph;
    }

    float manhatanDistanceToTarget(const VertexPtr& source) const;

    float calcManhatanDistanceToTarget(const VertexPtr& source);

    bool updateVertex(const VertexPtr &vert, u_int32_t distance);

    inline const VertexPtrSetPtr vertexPtrSet() const{
        return m_vertexPtrSet;
    }

    GraphPtr m_graph;
    VertexPtrSetPtr m_vertexPtrSet;
    VertexPtr currentTarget;
    map <VertexPtr,float> manhattanDistanceMap;
};
