#include "DijkstraSolver.h"
#include "KruskalSolver.h"
#include "PrimsSolver.h"

void testDFS(GraphPtr & graph);
void testBFS(GraphPtr & graph);
void testDijkstra(GraphPtr & graph);
void testPrim(GraphPtr & graph);
void testKruskal(GraphPtr & graph);

int main()
{
    GraphPtr graph = make_shared<Graph>();

    graph->addVertex("Kiev",10,1);
    graph->addVertex("Lviv",10,2);
    graph->addVertex("Riga",12,1);
    graph->addVertex("Talinn",12,2);
    graph->addVertex("New York",1,5);
    graph->addVertex("Madrid",10,4);
    graph->addVertex("Rome",10,3);
    graph->addVertex("Washington",1,1);

    /*
 *                  30
 *  Washington(1,1) --- New_York(1,5)
 *    |
 * 300|
 *    |
 *    |         20             80             30
 *  Kiev (10,1)--- Lviv(10,2) --- Rome (10,3)---  Madrid(10,4)
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

    testDFS(graph);
    testBFS(graph);

    //testPrim(graph);
    // testKruskal(graph);
    testDijkstra(graph);

    // graph.printAllEdges(true);

    return 0;
}


void testDFS(GraphPtr & graph){
    graph->resetVertices();
    cout << "\nDFS:\n" << endl;
    graph->DFS("Kiev","Rome");
}

void testBFS(GraphPtr & graph){
    graph->resetVertices();
    cout << "\nBFS:\n" << endl;
    graph->BFS("Kiev","Rome");
}

void testDijkstra(GraphPtr & graph){
    graph->resetVertices();
    graph->resetDistances();
    DijkstraSolver solver (graph);
    if( solver.solve("Madrid", "Kiev") == true){

        solver.printDistances();

        VertexPtr v = graph->findVertex("Madrid");
        cout << "\nDijkstra: distance to " << v->getName() << " is " <<  v->getDistance() << endl;

    }
}

void testKruskal(GraphPtr & graph){
    graph->resetVertices();
    KruskalSolver solver(graph);
    if( solver.solve("Kiev") ){
        // solver.printDistances();
    }
}

void testPrim(GraphPtr & graph){
    graph->resetVertices();
    PrimsSolver solver(graph);
    if( solver.solve("Kiev") ){
        // solver.printDistances();
    }
}


