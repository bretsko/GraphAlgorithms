#pragma once

#include "Common.h"


class Edge {

public:

    Edge(const VertexPtr &src, const VertexPtr &dest, u_int32_t weight );

    ~Edge() = default;

    Edge(const Edge& that)
        : source(that.source.lock()),
          destination(that.destination.lock()),
          weight (that.weight)
    {
    }

    Edge& operator=(const Edge& that)
    {
        destination = that.destination.lock();
        source = that.source.lock();
        weight = that.weight;
        return *this;
    }

    pair<VertexPtr,VertexPtr> getVertices() const;

    VertexPtr getSource() const;
    VertexPtr getDestination()const;

    inline void setSource(const VertexPtr &vert){
        source = vert;
    }

    inline void setDestination(const VertexPtr &vert){
        destination = vert;
    }

    inline u_int32_t getWeight() const{
        return weight;
    }

    inline void setWeight(u_int32_t w){
        weight = w;
    }

    bool compareNamesUndirected(const Edge &edge) const;
    bool comparePtrsUndirected(const Edge &edge) const;

    bool compareNamesDirected(const Edge &edge) const;
    bool comparePtrsDirected(const Edge &edge) const;

    void print(bool withWeights) const;

private:

    WeakVertexPtr source;
    WeakVertexPtr destination;
    u_int32_t weight;
};



