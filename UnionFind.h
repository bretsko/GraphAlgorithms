
#pragma once

#include "Common.h"
#include "Vertex.h"

bool unionVertices(UnionFindPtr &u1, UnionFindPtr &u2);

UnionFindPtr createUnionFind(const VertexPtr & ptr);

//TODO: template
struct UnionFind {

    UnionFind( const VertexPtr & ptr ) : rank(0), weakThis(ptr){

    }

    ~UnionFind() = default;

    UnionFindPtr findRoot();

    inline UnionFindPtr getRoot() const{
        return root.lock();
    }

    inline void setRoot(const UnionFindPtr &ptr){
        root = ptr;
    }

    inline VertexPtr getThis() const{
        return weakThis.lock();
    }

    inline UnionFindPtr getParent() const{
        return parent.lock();
    }

    void setParent(const UnionFindPtr& ptr);

    inline void setRank(u_int32_t r){
        rank = r;
    }

    inline u_int32_t getRank() const{
        return rank;
    }

private:
    u_int32_t rank;
    WeakUnionFindPtr root;
    WeakUnionFindPtr parent;
    WeakVertexPtr weakThis;

};
