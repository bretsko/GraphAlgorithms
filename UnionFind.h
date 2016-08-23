
#pragma once

#include "Common.h"
#include "Vertex.h"

bool unionVertices(const UnionFindPtr &u1, const UnionFindPtr &u2);

const UnionFindPtr createUnionFind(const VertexPtr & ptr);

//TODO: template
struct UnionFind {

    UnionFind( const VertexPtr & ptr ) : rank(0), weakThis(ptr){

    }

    ~UnionFind() = default;

    const UnionFindPtr findRoot();

    inline const UnionFindPtr getRoot() const{
        return root.lock();
    }

    inline void setRoot(const UnionFindPtr &ptr){
        root = ptr;
    }

    inline const VertexPtr getThis() const{
        return weakThis.lock();
    }

    inline const UnionFindPtr getParent() const{
        return parent.lock();
    }

    inline void setParent(const UnionFindPtr &ptr){
        parent = ptr;
    }

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
