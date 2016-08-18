
#pragma once

#include "Edge.h"
#include "Common.h"

class Vertex {

public:

    //init with default name "None"
    Vertex();
    ~Vertex() = default;

    Vertex(const string &name,
           float x = 0,
           float y = 0,
           u_int32_t distance = std::numeric_limits<u_int32_t>::max()
            );

    Vertex(const Vertex& that) :
        name(that.name),
        edges(that.edges),
        distance(that.distance),
        x(that.x),
        y(that.y),
        visited(that.visited)
    {
    }

    Vertex& operator=(const Vertex& that)
    {
        name = that.name;
        edges = that.edges;
        distance = that.distance;
        x = that.x;
        y = that.y ;
        visited = that.visited;
        return *this;
    }

    bool addEdge(const EdgePtr &edge);

    EdgePtr getConnection(const Vertex &vert) const;

    void removeMutualConnection(Vertex &vert);

    VertexPtr getNearestNeighbour() const;

    EdgePtr getNearestNeighbourConnection() const;

    inline const list<EdgePtr> * getEdges() const{
        return &edges;
    }

    inline u_int32_t getDistance() const{
        return distance;
    }

    inline void setDistance(u_int32_t newDistance){
        distance = newDistance;
    }

    inline string getName() const{
        return name;
    }

    inline void setName(const string &newName){
        name = newName;
    }

    inline bool isVisited() const{
        return visited;
    }

    inline float getX() const{
        return x;
    }

    inline float getY() const{
        return y;
    }

    inline void setVisited(bool isVisited){
        visited = isVisited;
    }


    inline void printEdges(bool withWeights) const{
        for(const EdgePtr & i : edges  ){
            i->print(true);
        }
    }

private:

    string name;

    //adj list
    list<EdgePtr> edges;

    // distance from source
    u_int32_t distance;

    //coordinates for Manhattan distance
    float x;
    float y;

    bool visited;
};


struct CompareVertices
{
    using is_transparent = void;

    bool operator() (const VertexPtr& lhs, const VertexPtr& rhs) const
    {
        return lhs->getDistance() < rhs->getDistance();
    }
};


struct CompareEdgePtrByName
{
    using is_transparent = void;

    bool operator() (const EdgePtr& lhs, const EdgePtr& rhs) const
    {
        if(!lhs->getDestination() || !rhs->getDestination() || !lhs->getSource() || !rhs->getSource())
            return false;

        bool r1 = lhs->getDestination()->getName() == lhs->getDestination()->getName();
        bool r2 = rhs->getSource()->getName() == rhs->getSource()->getName();

        return (r1 && r2);
    }
};

struct CompareEdgePtrByWeight
{
    using is_transparent = void;

    bool operator() (const EdgePtr& lhs, const EdgePtr& rhs) const
    {
        return lhs->getWeight() < rhs->getWeight();
    }
};

