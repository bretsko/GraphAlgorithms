#pragma once

#include "Common.h"
#include "Vertex.h"

struct Graph{

    Graph() = default;

    ~Graph() = default;

    Graph(const VertexPtrMap &vertices);

    Graph(const Graph& that) :
        verticesMap(that.verticesMap)
    {
    }

    Graph& operator=(const Graph& that)
    {
        verticesMap = that.verticesMap;
        return *this;
    }

    inline VertexPtrMap getVertices(){
        return verticesMap;
    }

    bool contains(const VertexPtr &vertexName);

    VertexPtr findVertex(const string &vertexName);


    bool addVertex(const string &vertexName);

    bool removeVertex(const string &vertexName);

    bool connect(const VertexPtr &vert1, const VertexPtr &vert2, u_int32_t weight);

    bool connect(const string &vert1, const string &vert2, u_int32_t weight);

private:
    VertexPtrMap verticesMap;
};





