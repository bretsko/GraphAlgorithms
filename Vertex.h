
#pragma once

#include "Edge.h"
#include "Common.h"


struct Vertex {

    //init with default name "None"
    Vertex();

    Vertex(const string &name, u_int32_t distance = std::numeric_limits<u_int32_t>::max());

    ~Vertex() = default;

    Vertex(const Vertex& that) :
        name(that.name),
        edges(that.edges),
        distance(that.distance),
        visited(that.visited)
    {
    }

    Vertex& operator=(const Vertex& that)
    {
        name = that.name;
        edges = that.edges;
        distance = that.distance;
        visited = that.visited;
        return *this;
    }

    void setConnection(const VertexPtr & vert, u_int32_t weight);

    EdgePtr getConnection(Vertex &vert);

    void removeMutualConnection(Vertex &vert);

    VertexPtr getNearestNeighbour();
    EdgePtr getNearestNeighbourConnection();

    inline list<EdgePtr> * getEdges(){
        return &edges;
    }

    inline u_int32_t getDistance(){
        return distance;
    }

    inline void setDistance(u_int32_t newDistance){
        distance = newDistance;
    }

    inline string getName(){
        return name;
    }

    inline void setName(const string &newName){
        name = newName;
    }

    inline bool isVisited(){
        return visited;
    }

    void setVisited(bool isvisited){
        visited = isvisited;
    }

private:

    string name;

    //adj list
    list<EdgePtr> edges;

    // distance from source
    u_int32_t distance;

    bool visited;
};


struct Compare
{
    using is_transparent = void;

    bool operator() (const VertexPtr& lhs, const VertexPtr& rhs) const
    {
        return lhs->getDistance() < rhs->getDistance();
    }
};





