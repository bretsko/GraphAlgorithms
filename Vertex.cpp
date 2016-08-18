#include "Vertex.h"
#include "Edge.h"

Vertex::Vertex(const string &name, float xCoord, float yCoord,u_int32_t distance):
    name (name),
    distance(distance),
    x(xCoord),
    y(yCoord),
    visited (false)
{
}

Vertex::Vertex() : Vertex("None"){

}

bool Vertex::addEdge(const EdgePtr & edge )
{
    if(!edge)
        return false;

    edges.push_back(edge);
    return true;
}

EdgePtr Vertex::getNearestNeighbourConnection() const{

    if (edges.size() == 0)
        return nullptr;

    EdgePtr nearestNeighbour = edges.front();

    for (const EdgePtr & e : edges ){

        if(nearestNeighbour->getWeight() < e->getWeight()){
            nearestNeighbour = e;
        }
    }

    return nearestNeighbour;
}

VertexPtr Vertex::getNearestNeighbour() const{

    EdgePtr nearestNeighbourConnection = getNearestNeighbourConnection();

    if(nearestNeighbourConnection == nullptr)
        return nullptr;

    if(VertexPtr vertPtr = nearestNeighbourConnection->getDestination()){
        return vertPtr;
    }

    return nullptr;
}


EdgePtr Vertex::getConnection(const Vertex &vert) const{
    for (const EdgePtr & e : edges ){

        if(VertexPtr vertPtr = e->getDestination()){
            if (&vert == vertPtr.get() ){
                return e;
            }
        }
    }
    return nullptr;
}

void Vertex::removeMutualConnection(Vertex &vert){

    for (const EdgePtr & e : vert.edges ){

        if(VertexPtr vertPtr = e->getDestination()){
            if (this == vertPtr.get() ){
                vert.edges.remove(e);
                break;
            }
        }
    }

    for (const EdgePtr & e : edges ){

        if(VertexPtr vertPtr = e->getDestination()){
            if (&vert == vertPtr.get() )
                edges.remove(e);
            break;
        }
    }
}
