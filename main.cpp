#include "DijkstraSolver.h"

void testDFS(Graph & graph);
void testBFS(Graph & graph);
void testDijkstra(Graph & graph);

int main()
{

    Graph graph;
    graph.addVertex("Kiev");
    graph.addVertex("Lviv");
    graph.addVertex("Riga");
    graph.addVertex("Talinn");
    graph.addVertex("New York");
    graph.addVertex("Madrid");
    graph.addVertex("Rome");
    graph.addVertex("Washington");

    /*
 *             30
 *  Washington --- New_York
 *    |
 * 300|
 *    |
 *    |   20       80         30
 *  Kiev --- Lviv --- Rome ---  Mardid
 *    |
 *  50|
 *    |    10
 *  Riga  --- Talinn
 *
 */

    graph.connect("Kiev", "Lviv", 20);
    graph.connect("Kiev", "Riga", 50);
    graph.connect("Kiev", "Washington", 300);

    graph.connect("Riga", "Talinn", 10);            //Kiev - Talinn = 50 + 10
    graph.connect("Lviv", "Rome", 80);              //Kiev - Rome  = 20 + 80
    graph.connect("Washington" , "New York", 30);   //Kiev - New_York =  300 + 30
    graph.connect("Rome", "Madrid", 30);            //Kiev - Madrid = 20 + 80 + 30


    testDFS(graph);
    testBFS(graph);
    testDijkstra(graph);

    return 0;
}


void testDFS(Graph & graph){
    graph.resetVertices();
    cout << "\nDFS:\n" << endl;
    graph.DFS("Kiev","Rome");
}

void testBFS(Graph & graph){
    graph.resetVertices();
    cout << "\nBFS:\n" << endl;
    graph.BFS("Kiev","Rome");
}

void testDijkstra(Graph & graph){
    graph.resetVertices();
    DijkstraSolver solver(graph);
    if( solver.solve("Kiev", "Madrid") == true){
        solver.printDistances();
    }
}



