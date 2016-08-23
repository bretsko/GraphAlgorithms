#pragma once

#include "Graph.h"

//In Kruskal's, you do not keep one connected component but a forest.
//At each stage, you look at the globally smallest edge that does not
//create a cycle in the current forest. Such an edge has to necessarily
//merge two trees in the current forest into one. Since you start
//with N single-vertex trees, in N-1 steps, they would all have merged into one
//if the graph was connected.

typedef EdgePtrSetComparedByName EdgePtrSet;

class KruskalSolver
{
public:

    KruskalSolver(const GraphPtr & graph);

    ~KruskalSolver() = default;

    KruskalSolver(const KruskalSolver& that) = delete;
    KruskalSolver& operator=(const KruskalSolver& that) = delete;

    const shared_ptr<EdgePtrSet> solve(const VertexPtr &vert);

    const shared_ptr<EdgePtrSet> solve(const string &vertexName);

    const UnionFindPtr findUnion(const VertexPtr &p, const list<UnionFindPtr> &unions) const;

    inline const GraphPtr graph()const{
        return m_graph;
    }

    void printMST(const shared_ptr<EdgePtrSet> & MST)const;

    inline void visit(const VertexPtr &vert){
        graph()->visit(vert);
    }


private:
    GraphPtr m_graph;
};







