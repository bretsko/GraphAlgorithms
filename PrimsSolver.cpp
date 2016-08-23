
#include "PrimsSolver.h"



PrimsSolver ::PrimsSolver(const GraphPtr &graphArg):m_graph(graphArg){

}

const shared_ptr<EdgePtrSet> PrimsSolver::solve(const std::__cxx11::string &vertexName)
{
    VertexPtr v = graph()->findVertex(vertexName);

    if(v)
        return solve (v);

    return nullptr;
}


const shared_ptr<EdgePtrSet> PrimsSolver::solve(const VertexPtr &vert)
{
    if (vert == nullptr || vert->getEdges()->empty())
        return nullptr;

    //keeps all edges added so far and potential edges to be evaluated,
    //based on inspection if any of the vertices in the new edge are  present in MST
    unique_ptr<EdgePtrSet> PQ = make_unique<EdgePtrSet>();

    shared_ptr<EdgePtrSet> MST = make_shared<EdgePtrSet>();

    //all vertices added to MST
    unique_ptr <set<VertexPtr>> vSet = make_unique<set<VertexPtr>>();

    visit(vert);
    vSet->insert (vert);

    EdgePtr smallest = vert->getEdges()->front();

    for (const EdgePtr & e : *vert->getEdges()){
        if (e->getWeight() < smallest->getWeight()){
            smallest = e;
        }
    }

    MST->insert(smallest);

    VertexPtr v = smallest->getDestination();
    if(v){
        visit(v);
        vSet->insert(v);
    }else {
        //error, no destination vertex in edge
        return nullptr;
    }

    u_int32_t count = graph()->getVertices().size();

    while(count!=0){

        VertexPtr a = nullptr;
        VertexPtr b = nullptr;

        //update PQ
        for (const VertexPtr &v : *vSet){
            for (const EdgePtr &e : *v->getEdges()){
                PQ->insert(e);
            }
        }

        for (const EdgePtr & e : *PQ){

            a = e->getDestination();
            b = e->getSource();

            if( a && b && a->isVisited()==true && b->isVisited()==true){
                continue;
            }else if(a->isVisited()==false || b->isVisited()==false){

                visit(a);
                visit(b);

                vSet->insert(a); // set will insert duplicates here
                vSet->insert(b);

                MST->insert(e); //multiset can have duplicates, i.e. with similar weight

                break;
            }
        }

        count--;
    }

    printMST(MST);

    return MST;
}





void PrimsSolver::printMST(const shared_ptr<EdgePtrSet> &MST){
    cerr << "\nMST, size "<< MST->size() << ":\n" << endl;

    for( const EdgePtr &e : *MST ){
        e->print(true);
    }
}


