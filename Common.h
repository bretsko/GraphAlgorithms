
#pragma once

#include <list>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <cstdbool>
#include <algorithm>
#include <stack>
#include <queue>

using std::cerr;
using std::cout;
using std::endl;
using std::cin;

using std::string;
using std::list;
using std::set;
using std::multiset;
using std::map;
using std::stack;
using std::queue;

using std::weak_ptr;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
using std::find;
using std::move;
using std::pair;

class Graph;
class Vertex;
class Edge;
struct UnionFind;

struct CompareEdgePtrByName;
struct CompareEdgePtrByWeight;
struct CompareVerticesByDistance;

typedef shared_ptr <Graph> GraphPtr;
typedef shared_ptr <Edge> EdgePtr;
typedef shared_ptr <Vertex> VertexPtr;
typedef weak_ptr <Vertex> WeakVertexPtr;
typedef shared_ptr <UnionFind> UnionFindPtr;
typedef weak_ptr<UnionFind> WeakUnionFindPtr;

typedef set <EdgePtr, CompareEdgePtrByName> EdgePtrSetComparedByName;
typedef set <EdgePtr, CompareEdgePtrByName> EdgePtrSetComparedByWeight;
typedef map <string, VertexPtr> VertexPtrMap;


