#include "DijkstraSolver.h"

Graph::Graph(const VertexPtrMap &vertices):verticesMap(vertices){

}

VertexPtr Graph::findVertex(const string &vertexName)
{
    auto iter = verticesMap.find(vertexName);
    if (iter != verticesMap.end()){
        return iter->second;
    }
    return nullptr;
}

bool Graph::contains(const VertexPtr &vertex)
{
    auto iter = verticesMap.find(vertex->getName());
    if (iter != verticesMap.end()){
        return true;
    }
    return false;
}

bool Graph::addVertex(const string &vertexName)
{
    VertexPtr vert = make_shared<Vertex>(vertexName);
    verticesMap.insert( {vertexName ,vert });
    return true;
}

bool Graph::removeVertex(const string &vertexName)
{
    auto iter = verticesMap.find(vertexName);
    if (iter != verticesMap.end()){
        verticesMap.erase(iter);
        return true;
    }
    return false;
}


bool Graph::connect(const string &vert1, const string &vert2, u_int32_t weight ){

    auto v1 = findVertex(vert1);
    auto v2 = findVertex(vert2);

    if (v1 != nullptr && v2 != nullptr){
        return connect(v1, v2, weight);
    }

    return false;
}


bool Graph::connect(const VertexPtr &vert1, const VertexPtr &vert2, u_int32_t weight ){

    auto edgeListPtr = vert1->getEdges();

    for (const auto & e : *edgeListPtr){

        if(VertexPtr vertPtr = e->getVertex().lock()){
            //can only have one edge one way
            if (vertPtr == vert2 )
                return false;
        }
    }

    //adding the reverse edge - for undirected graph

    vert1->getEdges()->push_back(make_shared<Edge>(vert2,weight));
    vert2->getEdges()->push_back(make_shared<Edge>(vert1,weight));

    return true;
}




