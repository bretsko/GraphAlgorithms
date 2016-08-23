#include "KruskalSolver.h"

#include "Vertex.h"
#include "Edge.h"
#include "UnionFind.h"


KruskalSolver ::KruskalSolver(const GraphPtr &graphArg):m_graph(graphArg){

}

const shared_ptr<EdgePtrSet> KruskalSolver::solve(const string &vertexName)
{
    VertexPtr v = nullptr;
    v = graph()->findVertex(vertexName);
    if(v)
        return solve (v);

    return nullptr;
}



const shared_ptr<EdgePtrSet> KruskalSolver::solve(const VertexPtr &start)
{
    if (start == nullptr || start->getEdges()->empty())
        return nullptr;

    shared_ptr<EdgePtrSet> MST = make_shared<EdgePtrSet>();

    list<UnionFindPtr> unions;

    EdgePtr smallestEdge = graph()->getSmallestEdge(start);

    MST->insert(smallestEdge);

    VertexPtr nearest = graph()->getTheOtherVertex(smallestEdge,start);

    for (const auto & p : graph()->getVertices()){
        UnionFindPtr u = createUnionFind(p.second);
        unions.push_back(u);
    }

    UnionFindPtr u_start = findUnion(start,unions);
    UnionFindPtr u_nearest = findUnion(nearest,unions);

    unionVertices(u_start, u_nearest);

    bool doubleBreak = false;

    u_int32_t count = graph()->getEdges().size();

    while(count!=0){

        VertexPtr a = nullptr;
        VertexPtr b = nullptr;

        //iter edges starting with smallest
        for (const EdgePtr & e1 : graph()->getEdges()){
            if(doubleBreak){
                doubleBreak = false;
                break;
            }
            for (const EdgePtr & e2 : *MST){
                if (e1->comparePtrsUndirected(*e2) == false){ //found new edge e1

                    a = e1->getDestination();
                    b = e1->getSource();

                    if( !a || !b ){
                        continue;
                    }

                    UnionFindPtr u1 = findUnion(a,unions);
                    UnionFindPtr u2 = findUnion(b,unions);

                    if( unionVertices(u1, u2)){
                        MST->insert(e1); //multiset can have duplicates, i.e. with similar weight
                        doubleBreak = true;
                        break;
                    }

                }
            }
        }

        count--;
    }

    printMST(MST);

    return MST;
}



const UnionFindPtr KruskalSolver::findUnion(const VertexPtr &p, const list<UnionFindPtr> & unions)const{

    for (const UnionFindPtr & v  : unions){
        if(v->getThis()->getName() == p->getName())
            return v;
    }

    return nullptr;
}

void KruskalSolver::printMST(const shared_ptr<EdgePtrSet> &MST)const{
    cerr << "\nMST, size "<< MST->size() << ":\n" << endl;

    for( const EdgePtr &e : *MST ){
        e->print(true);
    }
}



