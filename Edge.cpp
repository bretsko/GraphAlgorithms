
#include "Edge.h"
#include "Vertex.h"

Edge::Edge(const VertexPtr &src, const VertexPtr &dest, u_int32_t weight)
    : m_source (src),
      m_destination(dest),
      m_weight (weight)
{

}

const pair<VertexPtr, VertexPtr> Edge::getVertices() const
{
    auto dest = m_destination.lock();
    auto src = m_source.lock();
    if(src && dest)
        return {src, dest};

    return pair<VertexPtr,VertexPtr>({nullptr, nullptr});;
}

const VertexPtr Edge::getDestination() const {

    VertexPtr dest = m_destination.lock();

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


const VertexPtr Edge::getSource() const{
    VertexPtr src = m_source.lock();
    if(src){
        return src;
    }

    return nullptr;
}


void Edge::print(bool withWeights) const
{

    VertexPtr src = m_source.lock();
    VertexPtr dest = m_destination.lock();

    if(withWeights){
        cerr << src->getName() << " - " << dest->getName() << ", " << m_weight  << endl;
    }else{
        cerr << src->getName() << " - " << dest->getName() << ", "  << endl;
    }

}


bool sortEdgesByWeight(const EdgePtr &l, const EdgePtr &r){
    u_int32_t el = l->getWeight();
    u_int32_t er = r->getWeight();
    return ( el< er);
}
