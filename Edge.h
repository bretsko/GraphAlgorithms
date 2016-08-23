#pragma once

#include "Common.h"

bool sortEdgesByWeight(const EdgePtr &l, const EdgePtr &r);

class Edge {

public:

    Edge(const VertexPtr &src, const VertexPtr &dest, u_int32_t weight );

    ~Edge() = default;

    Edge(const Edge& that)
        : m_source(that.m_source.lock()),
          m_destination(that.m_destination.lock()),
          m_weight (that.m_weight)
    {
    }

    Edge& operator=(const Edge& that)
    {
        m_destination = that.m_destination.lock();
        m_source = that.m_source.lock();
        m_weight = that.m_weight;
        return *this;
    }

    const pair<VertexPtr,VertexPtr> getVertices() const;

    const VertexPtr getSource() const;
    const VertexPtr getDestination()const;

    inline void setSource(const VertexPtr &vert){
        m_source = vert;
    }

    inline void setDestination(const VertexPtr &vert){
        m_destination = vert;
    }

    inline u_int32_t getWeight() const{
        return m_weight;
    }

    inline void setWeight(u_int32_t w){
        m_weight = w;
    }

    bool compareNamesUndirected(const Edge &edge) const;
    bool comparePtrsUndirected(const Edge &edge) const;

    bool compareNamesDirected(const Edge &edge) const;
    bool comparePtrsDirected(const Edge &edge) const;

    void print(bool withWeights) const;

private:

    WeakVertexPtr m_source;
    WeakVertexPtr m_destination;
    u_int32_t m_weight;
};



