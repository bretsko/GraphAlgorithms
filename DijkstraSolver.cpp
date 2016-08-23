
#include "DijkstraSolver.h"

//m_vertexPtrSet (make_shared<VertexPtrSet>())
DijkstraSolver::DijkstraSolver(const GraphPtr & graphArg) :
    m_graph(graphArg),m_vertexPtrSet(make_shared<VertexPtrSet>()){

    GraphPtr graphPtr = graph();

    for (const auto &i : graphPtr->getVertices()){

        vertexPtrSet()->insert(i.second);
    }

    sortAllEdges();
}


bool DijkstraSolver::solveImpl(const GraphPtr& graphPtr, const VertexPtr& src, const VertexPtr& dest)
{

    VertexPtrMap verticesMap = graphPtr->getVertices();

    if ( src==nullptr || dest==nullptr )
        return false;

    if(verticesMap.size() < 2){
        cerr << "No solution for " << graphPtr->getVertices().size() << " vertices" << endl;
        return false;
    }

    //checking base case - only 2 points, or less

    if( updateVertex(src, 0 ) == false){
        //break on error
        return false;
    }

    if(graphPtr->getVertices().size() == 2){

        cerr << "\nFinish! " << "Distance from " << src->getName() << " to " \
             << dest->getName() << " is " << src->getEdges()->front()->getWeight() << endl;
        return true;
    }

    VertexPtr v1 = nullptr;

    v1 = popNonVisited();

    static u_int32_t counter = 0; //measuring algorithm efficiency

    while(v1 != nullptr){

        auto edgesListPtr = v1->getEdges();

        for (auto &e : *edgesListPtr ){

            counter++;

            if(VertexPtr v2 = e->getDestination()){ //weak_ptr check

                if(v2->getDistance() > v1->getDistance() + e->getWeight()){

                    auto newDist = v1->getDistance() + e->getWeight();
                    // updateVertex(v2,newDist); // FIXIT: doesn't work
                    VertexPtr x (v2); //copy to reinsert updated Vertex

                    x->setDistance(newDist);

                    vertexPtrSet()->erase(v2); //update element

                    vertexPtrSet()->insert(x);
                }
            }
        }

        v1 = popNonVisited();
    }

    cerr << "\nTook " << counter << " steps to finish."<<  endl;

    return true;
}


//TODO:
bool DijkstraSolver::solveImplOptimized(const GraphPtr &graphPtr, const VertexPtr &src, const VertexPtr& dest)
{

    VertexPtrMap verticesMap = graphPtr->getVertices();

    if ( src==nullptr || dest==nullptr )
        return false;

    if(verticesMap.size() < 2){
        cerr << "No solution for " << graphPtr->getVertices().size() << " vertices" << endl;
        return false;
    }

    //checking base case - only 2 points, or less

    if( updateVertex(src, 0 ) == false){
        //break on error
        return false;
    }

    if(graphPtr->getVertices().size() == 2){

        cerr << "\nFinish! " << "Distance from " << src->getName() << " to " \
             << dest->getName() << " is " << src->getEdges()->front()->getWeight() << endl;
        return true;
    }

    VertexPtr v1 = nullptr;

    v1 = popNonVisited();

    if(!v1)
        return false;

    static u_int32_t counter = 0; //measuring algorithm efficiency

    while(v1 != nullptr){

        auto edgesListPtr = v1->getEdges();

        for (auto &e : *edgesListPtr ){

            counter++;

            if(VertexPtr v2 = e->getDestination()){ //weak_ptr check

                if(v2->getDistance() > v1->getDistance() + e->getWeight()){

                    auto newDist = v1->getDistance() + e->getWeight();
                    // updateVertex(v2,newDist); // FIXIT: doesn't work
                    VertexPtr x (v2); //copy to reinsert updated Vertex

                    x->setDistance(newDist);

                    vertexPtrSet()->erase(v2); //update element

                    vertexPtrSet()->insert(x);
                }
            }
        }

        v1 = popNonVisited();
    }

    cerr << "\nTook " << counter << " steps to finish."<<  endl;

    return true;
}


bool DijkstraSolver::updateVertex(const VertexPtr &vert, u_int32_t distance){

    if(!vert)
        return false;

    auto vertexIter = vertexPtrSet()->find(vert);

    if (vertexIter == vertexPtrSet()->end()){
        return false;
    }

    VertexPtr x (*vertexIter); //copy to reinsert updated Vertex
    x->setDistance(distance);

    vertexPtrSet()->erase(vertexIter); //update element

    vertexPtrSet()->insert(x);

    return true;
}

void DijkstraSolver::sortAllEdges(){

    auto vertPtrSet = vertexPtrSet();

    for (const VertexPtr &vert : *vertPtrSet){

        vert->sortEdges();
    }
}


const VertexPtr DijkstraSolver::popNonVisited(){

    VertexPtr v = nullptr;

    auto vertPtrSet = vertexPtrSet();

    //in a multiset iteration starts with a smallest,
    // and data stays sorted all the time
    for (const VertexPtr &vert : *vertPtrSet){

        if( vert->isVisited() == false){
            vert->setVisited(true);
            return vert;
        }
    }

    return nullptr;
}



void DijkstraSolver::printDistances()const{

    auto vertPtrSet = vertexPtrSet();

    for (const auto & i : *vertPtrSet ){
        cout << i->getName() << " : " << i->getDistance() << endl;
    }
}
