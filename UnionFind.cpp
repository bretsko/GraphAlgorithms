#include "UnionFind.h"
#include "Utilities.h"

bool unionVertices(UnionFindPtr &u1, UnionFindPtr &u2){

    if (!u1 || !u2 || !u1->getThis() || !u2->getThis())
        return false;

    UnionFindPtr u1_root = u1->findRoot();
    UnionFindPtr u2_root = u2->findRoot();

    if (u1_root.get() == u2_root.get() ){
        return false;
    }

    if (u1->getRank() > u2->getRank()) {

        u2->setParent(u1);
        u2->setRoot(u1_root);

    } else if (u1->getRank() < u2->getRank()) {

        u1->setParent(u2);
        u1->setRoot(u2_root);

    } else if( u1->getRank() == u2->getRank()) {

        u1->setParent(u2);

        u2->setRoot(u2_root);
        u1->setRoot(u2_root);
    }

    return true;
}

UnionFindPtr createUnionFind(const VertexPtr &ptr){
    UnionFindPtr u = make_shared<UnionFind>(ptr);
    u->setRoot(u);
    u->setParent(u);
    return u;
}

UnionFindPtr UnionFind::findRoot(){

    rank = 0;

    UnionFindPtr ptr = getParent();

    if (!ptr){
        return nullptr;
    }

    while(ptr->getParent() && (ptr != ptr->getParent())){
        rank++;
        ptr = ptr->getParent();
    }

    root = ptr;

    return ptr;
}

void UnionFind::setParent(const UnionFindPtr &ptr){
    parent = ptr;
}




