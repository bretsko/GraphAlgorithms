
#include "Graph.h"


Graph::Graph(const VertexPtrMap &vertices): verticesMap (make_unique<VertexPtrMap>(vertices))
{
}

//--------------------------------VERTEX-----------------------------


//if already present returns false
bool Graph::addVertex(const string &vertexName, float x, float y)
{
    VertexPtr vert = nullptr;

    if (x!=0 || y!=0){
        vert = make_shared<Vertex>(vertexName, x, y);
    }else {
        vert = make_shared<Vertex>(vertexName);
    }

    bool result = verticesMap->insert( std::make_pair (vertexName ,vert )).second;
    return result;
}

VertexPtr Graph::findVertex(const string &vertexName) const
{

    auto iter = verticesMap->find(vertexName);

    if (iter != verticesMap->end()){
        VertexPtr foundVertex = iter->second;
        // u_int32_t dist = foundVertex->getDistance();
        //cerr << "Found: " << foundVertex->getName() << ", distance - " << dist << endl;
        return foundVertex;
    }

    return nullptr;
}

bool Graph::contains(const VertexPtr &vert)const
{
    string n = vert->getName();

    if(verticesMap->count(n)!=0){
        return true;
    }

    return false;
}


bool Graph::removeVertex(const string &vertexName)
{
    auto iter = verticesMap->find(vertexName);
    if (iter != verticesMap->end()){
        verticesMap->erase(iter);
        return true;
    }
    return false;
}


//--------------------------------EDGE-----------------------------


//check edge state and insert it
bool Graph::addEdge(const EdgePtr &edge){

    if (edge == nullptr)
        return false;

    if( findEdge(edge) != nullptr )
        return false;

    VertexPtr src = nullptr;
    VertexPtr dest = nullptr;

    src = edge->getDestination();
    dest = edge->getDestination();

    if(src == nullptr || dest == nullptr){
        return false;
    }

    edgesSet.insert(edge);
    return true;
}


//merges edges with common vertices and adds vertices if not present
bool Graph::addEdge(const VertexPtr &dest, const VertexPtr &src, u_int32_t weight){

    //considering only weighted graph
    if(!dest || !src || src == dest || weight == 0)
        return false;

    //for undirected graph checking if either way edge is present
    if(findEdge(dest,src))
        return false;

    //if vertices are not present in the graph add them
    if(!contains(src)){
        auto result = addVertex(src);
        if (!result)
            return false;
    }

    if(!contains(dest)){
        auto result = addVertex(dest);
        if (!result)
            return false;
    }

    //connect if not connected
    if(dest->getConnection(*src) == nullptr || src->getConnection(*dest) == nullptr){
        bool success = connect(src, dest,weight);
        if (!success)
            return false;
    }


    //create new edge for the graph, so that we don't depend on any of the vertices
    EdgePtr e = make_shared<Edge>(src, dest, weight);
    edgesSet.insert(e);

    return true;
}


//copies edge to the edgesSet
bool Graph::addEdgeCopy(const EdgePtr &edge){

    if (edge == nullptr)
        return false;

    EdgePtr e = make_shared<Edge>(*edge);

    return addEdge(e);
}

//finds similiar edge with the same vertices (source and destination can be swicthed)
const EdgePtr Graph::findEdge(const EdgePtr &edge) const{
    VertexPtr src = edge->getDestination();
    VertexPtr dest = edge->getDestination();
    return findEdge(src,dest);
}

const EdgePtr Graph::findEdge(const VertexPtr &vert1, const VertexPtr &vert2)const{

    //considering only weighted graph
    if(!vert1 || !vert2 || vert1 == vert2)
        return nullptr;

    for ( const EdgePtr & e : edgesSet){

        VertexPtr src = e->getDestination();
        VertexPtr dest = e->getDestination();

        if(src!=nullptr && dest!=nullptr){

            if((src == vert1 || src== vert2) && (dest == vert1 || dest== vert2)){
                return e;
            }
        }
    }

    return nullptr;
}


//--------------------------------OTHER-----------------------------


bool Graph::connect(const string &vert1, const string &vert2, u_int32_t weight ){

    auto v1 = findVertex(vert1);
    auto v2 = findVertex(vert2);

    if (v1 != nullptr && v2 != nullptr){
        return connect(v1, v2, weight);
    }

    return false;
}

bool Graph::connect(const VertexPtr &vert1, const VertexPtr &vert2, u_int32_t weight ){

    EdgePtr edge = make_shared<Edge>(vert1, vert2, weight);

    //I believe that double check if the edge is present in multiset is not needed
    //although edgesSet will add happily another duplicate here

    edgesSet.insert(edge);

    //adding both ways edges - for undirected graph
    vert1->addEdge(edge);
    vert2->addEdge(edge);

    return true;
}


void Graph::printEdges(const VertexPtr &vert )const{

    if(!vert)
        return;

    cerr << vert->getName() <<" is connected to: ";

    for (const EdgePtr & e : *vert->getEdges()){

        VertexPtr v = e->getDestination();

        //TODO:  << ", "

        if(v)
            cerr << v->getName() << endl;
    }

    cerr << endl;
}


void Graph::printEdgesInVertices( ) const{

    for (const auto & p: *verticesMap){
        VertexPtr v =  p.second;
        printEdges (v);
    }
}


void Graph::printAllEdges(bool withWeights) const{

    cerr << "\nGraph edges:\n"<< endl;

    for (const EdgePtr & e : edgesSet){

        e->print(withWeights);
    }

}




bool Graph::DFS(const VertexPtr& src,const VertexPtr&  dest)
{

    if (src == dest)
        return true;

    VertexPtr current = nullptr;

    stack<VertexPtr> vertStack;
    vertStack.push(src);

    static u_int32_t counter = 0; //to measure algorithm efficiency

    while(!vertStack.empty())
    {
        current = vertStack.top();
        vertStack.pop();

        if(current->isVisited() == true) continue;

        visit(current);
        auto edges = current->getEdges();

        //visit all adjacent
        for (const EdgePtr & e : *edges ){

            counter++;

            if(VertexPtr vertPtr = e->getDestination()){

                if (dest == vertPtr){
                    visit(dest);
                    cerr << "\nDFS: took " << counter << " steps to finish."<<  endl;

                    return true;
                }

                vertStack.push(vertPtr);
            }
        }
    }

    return false;
}

bool Graph::BFS(const VertexPtr& src,const VertexPtr& dest)
{
    if (src == dest)
        return true;

    VertexPtr current = nullptr;

    queue<VertexPtr> vertQueue;
    visit(src);
    vertQueue.push(src);
    static u_int32_t counter = 0; //to measure algorithm efficiency

    while(!vertQueue.empty())
    {

        current = vertQueue.front();
        vertQueue.pop();

        auto edges = current->getEdges();

        //visit all adjacents
        for (const EdgePtr & e : *edges ){

            counter++;

            if(VertexPtr vertPtr = e->getDestination()){

                if (vertPtr->isVisited() == false){
                    visit(vertPtr);

                    if (dest == vertPtr){
                        cerr << "\nBFS: took " << counter << " steps to finish."<<  endl;

                        return true;
                    }
                    vertQueue.push(vertPtr);
                }
            }
        }
    }

    return false;
}



VertexPtr Graph::getNearestNeighbour(const VertexPtr & vert) const{
    EdgePtr e = getSmallestEdge(vert);
    return getTheOtherVertex (e,vert);
}

float Graph::calculateManhattanDistance(const VertexPtr &p1, const VertexPtr &p2) const{

    float diffY = p1->getY() - p2->getY();
    float diffX = p1->getX() - p2->getX();
    float result = sqrt((diffY * diffY) + (diffX * diffX));

    //  cerr << "Manhattan distance " << p1->getName() << "-" << p2->getName() << ": " << result <<  endl;

    return result;
}


VertexPtr Graph::getTheOtherVertex(const EdgePtr& edge, const VertexPtr & vert) const{

    if(!edge || !vert )
        return nullptr;

    VertexPtr v = edge->getDestination();

    if(v != vert){
        return v;
    }else{
        return edge->getSource();
    }

}

EdgePtr Graph::getSmallestEdge(const VertexPtr & vert) const{

    if( vert->getEdges()->size() == 0)
        return nullptr;

    EdgePtr smallest = vert->getEdges()->front();

    if( vert->getEdges()->size() == 1)
        return smallest;

    for (const EdgePtr & e : *vert->getEdges()){
        if (e->getWeight() < smallest->getWeight()){
            smallest = e;
        }
    }

    return smallest;
}



