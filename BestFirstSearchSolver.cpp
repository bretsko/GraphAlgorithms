
#include "BestFirstSearchSolver.h"


BestFirstSearchSolver::BestFirstSearchSolver(const GraphPtr &graphArg): m_graph(graphArg),
    m_vertexPtrSet(make_shared<VertexPtrSet> (std::bind(&BestFirstSearchSolver::compareFunction,
                                                        this,std::placeholders::_1, std::placeholders::_2)))
{

}

bool BestFirstSearchSolver::solveImpl(const GraphPtr &graphPtr, const VertexPtr &src, const VertexPtr& dest)
{
    return solveImpl( graphPtr,src,dest, true); //enable by default the early exit
}

bool BestFirstSearchSolver::solveImpl(const GraphPtr &graphPtr, const VertexPtr& src, const VertexPtr& dest, bool earlyExit)
{

    currentTarget = dest;

    //vertices are ordered in the set based on Manhattan distance to currentTarget
    for (const auto &i : graph()->getVertices()){
        vertexPtrSet()->insert(i.second);
    }

    // printManhattanDistances();

    VertexPtrMap verticesMap = graphPtr->getVertices();

    if ( src==nullptr || dest==nullptr )
        return false;

    if(verticesMap.size() < 2){
        cerr << "No solution for " << graph()->getVertices().size() << " vertices" << endl;
        return false;
    }

    //checking base case - only 2 points, or less

    if( updateVertex(src, 0 ) == false){
        //break on error
        return false;
    }

    if(graph()->getVertices().size() == 2){

        cerr << "\nFinish! " << "Distance from " << src->getName() << " to " \
             << dest->getName() << " is " << src->getEdges()->front()->getWeight() << endl;
        return true;
    }

    VertexPtr v1 = src;
    VertexPtr vertMin = nullptr;
    u_int32_t counter = 0; //measuring algorithm efficiency

    while(true){

        float distManhMin = std::numeric_limits<float>::max();
        u_int32_t distMin = std::numeric_limits<u_int32_t>::max();

        bool foundTarget = false;

        auto edgesListPtr = v1->getEdges();

        //find the vertex with lowest Manhattan distance
        for (const EdgePtr &e : *edgesListPtr ){

            counter++;

            if(VertexPtr v2 = e->getDestination()){ //weak_ptr check

                if( v2->isVisited() == true)
                    continue;

                v2->setVisited(true);

                if(earlyExit && (currentTarget.get() ==  v2.get())){
                    vertMin = v2;
                    distMin = e->getWeight();
                    foundTarget = true;
                    break;
                }

                float dist = manhatanDistanceToTarget(v2);
                // cerr << "Comparing " << v2->getName() << " ManhDist: "<<  dist << endl;

                if(dist < distManhMin){
                    distManhMin = dist;
                    vertMin = v2;
                    distMin = e->getWeight();
                }
            }
        }

        VertexPtr vcopy = vertMin;

        if(vertMin->getDistance() > v1->getDistance() + distMin){

            auto newDist = v1->getDistance() + distMin;
            // updateVertex(v2,newDist); // FIXIT: doesn't work
            VertexPtr x (vertMin); //copy to reinsert updated Vertex

            x->setDistance(newDist);

            vertexPtrSet()->erase(vertMin); //update element

            vertexPtrSet()->insert(x);

        }

        //  cerr << "Visiting " << vcopy->getName() << " with ManhDist "<<  manhatanDistanceToTarget(vcopy) << endl;

        //earlyExit is checked already here
        if(foundTarget == true){
            cerr << "\nEarly exit, took " << counter << " steps to finish."<<  endl;
            return true;
        }

        v1 = vcopy;
    }

    cerr << "\nTook " << counter << " steps to finish."<<  endl;

    return true;
}

bool BestFirstSearchSolver::solveImplOptimized(const GraphPtr& graphPtr, const VertexPtr &src, const VertexPtr& dest)
{
    return solveImplOptimized(graphPtr,src,dest,true);
}

bool BestFirstSearchSolver::solveImplOptimized(const GraphPtr &graphPtr, const VertexPtr &src, const VertexPtr &dest, bool earlyExit)
{
    //TODO:
    return false;
}


void BestFirstSearchSolver::printManhattanDistances()const{

    if(graph()->getVertices().empty()){
        return;
    }

    cerr << "\nManhattan distances: \n" <<  endl;

    for (const auto& p : graph()->getVertices()){
        float dist = manhatanDistanceToTarget(p.second);
        cerr << p.second->getName() << ": " <<  dist << endl ;
    }
}

bool BestFirstSearchSolver::compareFunction(const VertexPtr &lhs, const VertexPtr &rhs)const
{
    float dist1 = manhatanDistanceToTarget(lhs);
    float dist2 = manhatanDistanceToTarget(rhs);
    return dist1 < dist2;
}

float BestFirstSearchSolver::manhatanDistanceToTarget(const VertexPtr &source)const{

    auto iter = manhattanDistanceMap.find(source);

    if (iter != manhattanDistanceMap.end() )
    {
        return iter->second;
    }

    return -1;
}

float BestFirstSearchSolver::calcManhatanDistanceToTarget(const VertexPtr &source)
{
    if(!currentTarget)
        return 0;

    float dist = manhatanDistanceToTarget(source);

    if(dist < 0){
        dist = graph()->calculateManhattanDistance(currentTarget,source);
        manhattanDistanceMap[source] = dist;
    }

    return dist;
}

bool BestFirstSearchSolver::updateVertex(const VertexPtr &vert, u_int32_t distance){

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


void BestFirstSearchSolver::printDistances() const{

    auto vertPtrSet = vertexPtrSet();

    for (const VertexPtr & i : *vertPtrSet ){
        cout << i->getName() << " : " << i->getDistance() << endl;
    }
}
