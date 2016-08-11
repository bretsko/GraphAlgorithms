#include "Vertex.h"

Vertex::Vertex(const string &name, u_int32_t distance):
    name (name),
    distance(distance),
    visited (false) {
}

Vertex::Vertex() : Vertex("None"){

}


void Vertex::setConnection(const VertexPtr& vert, u_int32_t weight){

    for (const EdgePtr& e : edges ){
        if(VertexPtr vertPtr = e->getVertex().lock()){ //weak_ptr check
            if (vertPtr == vert)
                return;
        }
    }

    EdgePtr edge = make_shared<Edge>(vert, weight);
    edges.push_back(edge);

}

EdgePtr Vertex::getConnection(Vertex &vert){
    for (const EdgePtr & e : edges ){

        if(VertexPtr vertPtr = e->getVertex().lock()){
            if (&vert == vertPtr.get() ){
                return e;
            }
        }
    }
    return nullptr;
}

void Vertex::removeMutualConnection(Vertex &vert){

    for (const EdgePtr & e : vert.edges ){

        if(VertexPtr vertPtr = e->getVertex().lock()){
            if (this == vertPtr.get() ){
                vert.edges.remove(e);
                break;
            }
        }
    }

    for (const EdgePtr & e : edges ){

        if(VertexPtr vertPtr = e->getVertex().lock()){
            if (&vert == vertPtr.get() )
                edges.remove(e);
            break;
        }
    }
}


