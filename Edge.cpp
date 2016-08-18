#include "Edge.h"
#include "Vertex.h"

Edge::Edge(const VertexPtr &src, const VertexPtr &dest, u_int32_t weight)
    : source (src),
      destination(dest),
      weight (weight)
{

}

pair<VertexPtr, VertexPtr> Edge::getVertices() const
{
    auto dest = destination.lock();
    auto src = source.lock();
    if(src && dest)
        return {src, dest};

    return pair<VertexPtr,VertexPtr>({nullptr, nullptr});;
}

VertexPtr Edge::getDestination() const {
    VertexPtr dest = destination.lock();

    if(dest){
        return dest;
    }

    return nullptr;
}


bool Edge::compareNamesUndirected(const Edge &edge) const
{
    bool r1 = (getDestination()->getName() == edge.getDestination()->getName());
    bool r2 = (getSource()->getName() == edge.getSource()->getName());

    bool r3 = (getDestination()->getName() == edge.getSource()->getName());
    bool r4 = (getSource()->getName() == edge.getDestination()->getName());

    if((r1 && r2) || (r3 && r4)){
        return true;
    }

    return false;

}

bool Edge::compareNamesDirected(const Edge &edge) const
{
    bool r1 = (getDestination()->getName() == edge.getDestination()->getName());
    bool r2 = (getSource()->getName() == edge.getSource()->getName());

    if(r1 && r2) {
        return true;
    }


    return false;
}


bool Edge::comparePtrsUndirected(const Edge &edge) const
{
    bool r1 = (getDestination().get() == edge.getDestination().get());
    bool r2 = (getSource().get() == edge.getSource().get());

    bool r3 = (getDestination().get() == edge.getSource().get());
    bool r4 = (getSource().get() == edge.getDestination().get());

    if((r1 && r2) || (r3 && r4)){
        return true;
    }

    return false;
}


bool Edge::comparePtrsDirected(const Edge &edge) const
{
    bool r1 = (getDestination().get() == edge.getDestination().get());
    bool r2 = (getSource().get() == edge.getSource().get());

    if(r1 && r2){
        return true;
    }

    return false;
}


VertexPtr Edge::getSource() const{
    VertexPtr src = source.lock();
    if(src){
        return src;
    }

    return nullptr;
}


void Edge::print(bool withWeights) const
{

    VertexPtr src = source.lock();
    VertexPtr dest = destination.lock();

    if(withWeights){
        cerr << src->getName() << " - " << dest->getName() << ", " << weight  << endl;
    }else{
        cerr << src->getName() << " - " << dest->getName() << ", "  << endl;
    }

}



