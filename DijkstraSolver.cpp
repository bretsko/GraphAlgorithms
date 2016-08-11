#include "DijkstraSolver.h"


DijkstraSolver ::DijkstraSolver(const Graph &graph): SolverInterface(graph){

    GraphPtr graphPtr = getGraph();

    //init vertexPtrSet with graph vertice pointers
    for (const auto &i : graphPtr->getVertices()){
        vertexPtrSet.insert(i.second);
    }
}

bool DijkstraSolver::solve( const string & src,  const string & dest){

    GraphPtr graphPtr = getGraph();

    VertexPtr srcPtr = graphPtr->findVertex(src);
    VertexPtr destPtr = graphPtr->findVertex(dest);

    if (srcPtr == nullptr){
        cerr << src << " not found." << endl;
        return false;
    }

    if (destPtr == nullptr){
        cerr << dest << " not found." << endl;
        return false;
    }

    return solve(graphPtr,srcPtr,destPtr);
}




bool DijkstraSolver::solve(GraphPtr graph, VertexPtr src, VertexPtr dest)
{
    GraphPtr graphPtr = getGraph();
    assert (src!=nullptr && dest!=nullptr);
    assert(this->contains(src) && this->contains(dest));

    if(graphPtr->getVertices().size() < 2){
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

    while(v1 != nullptr){

        auto edgesListPtr = v1->getEdges();

        for (auto &e : *edgesListPtr ){

            if(VertexPtr v2 = e->getVertex().lock()){ //weak_ptr check

                if(v2->getDistance() > v1->getDistance() + e->getWeight()){

                    auto newDist = v1->getDistance() + e->getWeight();

                    VertexPtr x (v2); //copy to reinsert updated Vertex

                    x->setDistance(newDist);
                    x->setConnection(v1, e->getWeight());
                    e->setVertex(x);

                    vertexPtrSet.erase( v2 );
                    vertexPtrSet.insert(x);
                }
            }
        }

        v1 = popNonVisited();
    }

    cout << "\nFinish! " << "Distance from " << src->getName() << " to " \
         << dest->getName() << " is " << dest->getDistance() << endl;

    return true;
}


bool DijkstraSolver::updateVertex(VertexPtr vert, u_int32_t distance){

    auto vertexIter = vertexPtrSet.find(vert);

    if (vertexIter == vertexPtrSet.end()){
        return false;
    }

    VertexPtr x (*vertexIter); //copy to reinsert updated Vertex
    x->setDistance(distance);

    vertexPtrSet.erase(vertexIter); //update element
    vertexPtrSet.insert(x);

    return true;
}


VertexPtr DijkstraSolver::popNonVisited(){

    VertexPtr v = nullptr;

    //in a multiset iteration starts with a smallest,
    // and data stays sorted all the time
    for (const VertexPtr &vert : vertexPtrSet){

        if( vert->isVisited() == false){
            vert->setVisited(true);
            return vert;
        }
    }

    return nullptr;
}


void DijkstraSolver::printDistances(){

    GraphPtr graph = getGraph();

    for (const auto & i : vertexPtrSet ){
        cerr << i->getName() << " : " << i->getDistance() << endl;
    }
}
