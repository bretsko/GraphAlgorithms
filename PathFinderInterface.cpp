
#include "PathFinderInterface.h"

bool PathFinderInterface::solve( const string & src,  const string & dest, bool optimized){

    GraphPtr graphPtr = graph();

    if (!graphPtr)
        return false;

    VertexPtr srcPtr = graphPtr->findVertex(src);
    VertexPtr destPtr = graphPtr->findVertex(dest);

    if (srcPtr == nullptr){
        cerr << src << " not found." << endl;
        return false;
    }

    if (destPtr == nullptr){
        cerr << dest << " not found." << endl;
        return false;
    }

    if(optimized)
        return solveImplOptimized(graphPtr,srcPtr,destPtr);

    return solveImpl(graphPtr,srcPtr,destPtr);
}
