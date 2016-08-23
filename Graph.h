#pragma once

#include "Common.h"
#include "Vertex.h"
#include "Edge.h"


//Undirected weighted graph
struct Graph{
public:

    typedef EdgePtrSetComparedByName EdgePtrSet;

    Graph(): verticesMap (make_unique<VertexPtrMap>()) {}
    ~Graph() = default;

    Graph(const VertexPtrMap &vertices);

    Graph(const Graph& that) = delete;
    Graph& operator=(const Graph& that)= delete;

    bool DFS(const VertexPtr&  src,const VertexPtr& dest);
    bool BFS(const VertexPtr&  src,const VertexPtr& dest);

    inline bool BFS(const string& src,const string&  dest){
        auto src_vert  = findVertex(src);
        auto dest_vert  = findVertex(dest);
        return BFS(src_vert,dest_vert);
    }

    inline bool DFS(const string& src,const string&  dest){
        auto src_vert  = findVertex(src);
        auto dest_vert  = findVertex(dest);
        return DFS(src_vert,dest_vert);
    }

    inline void resetVertices(){
        for (const auto & p : getVertices()){
            p.second->setVisited (false);
        }
    }

    inline void resetDistances(){
        for (const auto & p : getVertices()){
            p.second->setDistance (std::numeric_limits<u_int32_t>::max());
        }
    }

    bool contains(const VertexPtr &vert) const;

    VertexPtr findVertex(const string &vertexName) const;

    bool addVertex(const string &vertexName, float x = 0, float y = 0);
    bool removeVertex(const string &vertexName);

    //if already present returns false
    inline bool addVertex(const VertexPtr &vert)
    {
        if(!vert || contains(vert))
            return false;

        return verticesMap->insert({vert->getName(), vert}).second;
    }

    inline bool addVertexCopy(const VertexPtr &vert){
        return addVertex(make_shared<Vertex>(*vert));
    }

    bool addEdge(const EdgePtr &edge);
    bool addEdge(const VertexPtr &vert1, const VertexPtr &vert2, u_int32_t weight);
    bool addEdgeCopy(const EdgePtr &edge);

    const EdgePtr findEdge(const EdgePtr &edge)const;
    const EdgePtr findEdge(const VertexPtr &vert1, const VertexPtr &vert2) const;

    bool connect(const VertexPtr &vert1, const VertexPtr &vert2, u_int32_t weight);
    bool connect(const string &vert1, const string &vert2, u_int32_t weight);

    inline const VertexPtrMap getVertices() const{
        return *verticesMap;
    }

    inline const EdgePtrSet getEdges() const{
        return edgesSet;
    }

    inline void visit(const VertexPtr &vert){
        cout << "\nVisiting " << vert->getName() << endl;
        vert->setVisited(true);
    }

    void printAllEdges(bool withWeights) const;
    void printEdgesInVertices() const;
    void printEdges(const VertexPtr &vert) const;

    EdgePtr getSmallestEdge(const VertexPtr &vert) const;
    VertexPtr getTheOtherVertex(const EdgePtr &edge, const VertexPtr &vert) const;
    VertexPtr getNearestNeighbour(const VertexPtr &vert) const;

    float calculateManhattanDistance(const VertexPtr &p1, const VertexPtr &p2) const;

private:

    EdgePtrSet edgesSet;
    unique_ptr<VertexPtrMap> verticesMap;
};

