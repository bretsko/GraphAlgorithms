
#pragma once

#include <list>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <cstdbool>
#include <algorithm>


using std::cerr;
using std::cout;
using std::endl;
using std::cin;

using std::string;
using std::list;
using std::map;
using std::multiset;

using std::weak_ptr;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
using std::find;


struct Vertex;
struct Edge;
struct Compare;
class Graph;


typedef shared_ptr <Graph> GraphPtr;
typedef shared_ptr <Vertex> VertexPtr;
typedef weak_ptr <Vertex> WeakVertexPtr;
typedef shared_ptr <Edge> EdgePtr;

typedef multiset <VertexPtr, Compare> VertexPtrSet;
typedef map <string, VertexPtr> VertexPtrMap;



