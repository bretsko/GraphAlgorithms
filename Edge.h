#pragma once

#include "Common.h"

struct Edge {

    Edge(const VertexPtr &toVertex,u_int32_t weight);

    ~Edge() = default;

    Edge(const Edge& that) :
        vertex(that.vertex),
        weight (that.weight)
    {
    }


    Edge& operator=(const Edge& that)
    {
        vertex = that.vertex;
        weight = that.weight;
        return *this;
    }


    inline WeakVertexPtr getVertex(){
        return vertex;
    }

    inline void setVertex(const VertexPtr &vert){
        vertex = vert;
    }

    inline u_int32_t getWeight(){
        return weight;
    }

    inline void setWeight(u_int32_t w){
        weight = w;
    }


private:
    WeakVertexPtr vertex;
    u_int32_t weight;
};




