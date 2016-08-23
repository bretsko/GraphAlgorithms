
#include "PrimsSolver.h"
#include "KruskalSolver.h"
#include "DijkstraSolver.h"
#include "BestFirstSearchSolver.h"
#include "Utilities.h"

void testDFS(const GraphPtr & graph);
void testBFS(const GraphPtr & graph);
void testPrim(const GraphPtr & graph);
void testKruskal(const GraphPtr & graph);
void testDijkstra(const GraphPtr & graph);
void testDijkstraOptimized(const GraphPtr & graph);
void testBestFirstSearch(const GraphPtr & graph);


int main()
{
    GraphPtr graph = make_shared<Graph>();

    graph->addVertex("Kiev",10,10);
    graph->addVertex("Lviv",10,30);
    graph->addVertex("Riga",12,1);
    graph->addVertex("Talinn",12,2);
    graph->addVertex("New York",1,5);
    graph->addVertex("Madrid",10,50);
    graph->addVertex("Rome",10,40);
    graph->addVertex("Washington",1,1);

    /*
 *                  30
 *  Washington(1,1) --- New_York(1,5)
 *    |
 * 300|
 *    |
 *    |         20             80             30
 *  Kiev (10,10)--- Lviv(10,30) --- Rome (10,40)---  Madrid(10,50)
 *    |
 *  50|
 *    |         10
 *  Riga(12,1)  --- Talinn(12,2)
 *
 */

    graph->connect("Kiev", "Lviv", 20);
    graph->connect("Kiev", "Riga", 50);
    graph->connect("Kiev", "Washington", 300);

    graph->connect("Riga", "Talinn", 10);            //Kiev - Talinn = 50 + 10
    graph->connect("Lviv", "Rome", 80);              //Kiev - Rome  = 20 + 80
    graph->connect("Washington" , "New York", 30);   //Kiev - New_York =  300 + 30
    graph->connect("Rome", "Madrid", 30);            //Kiev - Madrid = 20 + 80 + 30

    //    testDFS(graph);
    //    testBFS(graph);
    //    testPrim(graph);
    //    testKruskal(graph);
    //    testDijkstra(graph);
    //    testBestFirstSearch(graph);

    //    cerr << "\nProfiler (DFS): " << profileFunc( testDFS,graph) << endl;

    //    cerr << "\nProfiler (BFS): " << profileFunc( testBFS,graph) << endl;

    //    cerr << "\nProfiler (Prim): " << profileFunc( testPrim,graph) << endl;

    //    cerr << "\nProfiler (Kruskal): " << profileFunc( testKruskal,graph) << endl;

    //currently just added sorting
    //    cerr << "\nProfiler (Dijkstra Optimized): " << profileFunc( testDijkstraOptimized,graph) << endl;

    //    cerr << "\nProfiler (Dijkstra): " << profileFunc( testDijkstra,graph) << endl;

    cerr << "\nProfiler (Best First Search): " << profileFunc( testBestFirstSearch,graph) << endl;

    // graph.printAllEdges(true);

    return 0;
}





//TODO: count steps and output
void testDFS(const GraphPtr & graph){
    graph->resetVertices();
    cout << "\nDFS:\n" << endl;
    graph->DFS("Kiev","Rome");
}

void testBFS(const GraphPtr & graph){
    graph->resetVertices();
    cout << "\nBFS:\n" << endl;
    graph->BFS("Kiev","Rome");
}

void testDijkstra(const GraphPtr & graph){
    graph->resetVertices();
    graph->resetDistances();
    DijkstraSolver solver (graph);
    if( solver.solve("Kiev", "Madrid", false) == true){

        // solver.printDistances();

        VertexPtr v = graph->findVertex("Madrid");
        cout << "\nDijkstra: distance to " << v->getName() << " is " <<  v->getDistance() << endl;

    }
}

void testDijkstraOptimized(const GraphPtr & graph){
    graph->resetVertices();
    graph->resetDistances();
    DijkstraSolver solver (graph);
    if( solver.solve("Kiev", "Madrid", true ) == true){

        // solver.printDistances();

        VertexPtr v = graph->findVertex("Madrid");
        cout << "\nDijkstra: distance to " << v->getName() << " is " <<  v->getDistance() << endl;

    }
}

void testBestFirstSearch(const GraphPtr & graph)
{
    graph->resetVertices();
    graph->resetDistances();
    BestFirstSearchSolver solver (graph);
    if( solver.solve("Kiev", "Madrid", false) == true){

        //  solver.printDistances();

        VertexPtr v = graph->findVertex("Madrid");
        cout << "\nBest First Search distance to " << v->getName() << " is " <<  v->getDistance() << endl;

    }
}


void testKruskal(const GraphPtr & graph){
    graph->resetVertices();
    KruskalSolver solver(graph);
    if( solver.solve("Kiev") != nullptr){
        // solver.printDistances();
    }
}

void testPrim(const GraphPtr & graph){
    graph->resetVertices();
    PrimsSolver solver(graph);
    if( solver.solve("Kiev") != nullptr){
        // solver.printDistances();
    }
}


