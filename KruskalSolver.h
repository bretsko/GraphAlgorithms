#pragma once
#include "Graph.h"
#include "Solver.h"

//In Kruskal's, you do not keep one connected component but a forest.
//At each stage, you look at the globally smallest edge that does not
//create a cycle in the current forest. Such an edge has to necessarily
//merge two trees in the current forest into one. Since you start
//with N single-vertex trees, in N-1 steps, they would all have merged into one
//if the graph was connected.

class KruskalSolver : public Solver
{
public:
    KruskalSolver(const GraphPtr & graph);

    ~KruskalSolver() = default;

    KruskalSolver(const KruskalSolver& that) = delete;
    KruskalSolver& operator=(const KruskalSolver& that) = delete;

    shared_ptr<EdgePtrSet> solve(const VertexPtr &vert);

    inline shared_ptr<EdgePtrSet> solve(const string &vertexName)
    {
        auto v = getGraph()->findVertex(vertexName);
        return solve ( v);
    }

    UnionFindPtr findUnion(const VertexPtr &p, const list<UnionFindPtr> &unions);
    shared_ptr<EdgePtrSet> solve1(const VertexPtr &vert);
};





