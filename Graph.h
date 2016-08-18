#pragma once

#include "Common.h"
#include "Vertex.h"
#include "Edge.h"


//Undirected weighted graph
struct Graph{
public:
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

    bool contains(const VertexPtr &vert);

    VertexPtr findVertex(const string &vertexName);

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

    EdgePtr findEdge(const EdgePtr &edge);
    EdgePtr findEdge(const VertexPtr &vert1, const VertexPtr &vert2);

    bool connect(const VertexPtr &vert1, const VertexPtr &vert2, u_int32_t weight);
    bool connect(const string &vert1, const string &vert2, u_int32_t weight);

    inline VertexPtrMap getVertices() const{
        return *verticesMap;
    }

    inline EdgePtrSet getEdges() const{
        return edgesSet;
    }

    inline void visit(VertexPtr vert){
        cout << "\nVisiting " << vert->getName() << endl;
        vert->setVisited(true);
    }

    void printAllEdges(bool withWeights);
    void printEdgesInVertices(VertexPtr);
    void printEdges(const VertexPtr &vert);

    EdgePtr getSmallestEdge(const VertexPtr &vert);
    VertexPtr getTheOtherVertex(const EdgePtr &edge, const VertexPtr &vert);
    VertexPtr getNearestNeighbour(const VertexPtr &vert);

    //used for Manhattan distance, TODO
    float calculateDistance(const VertexPtr &p1, const VertexPtr &p2);

private:

    EdgePtrSet edgesSet;
    unique_ptr<VertexPtrMap> verticesMap;
};





