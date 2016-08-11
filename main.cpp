
#include "Common.h"
#include "DijkstraSolver.h"
#include "Graph.h"
#include "Vertex.h"

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
 *  Kiev --- Lviv --- Mardid --- Rome
 *    |
 *  50|
 *    |    10
 *  Riga  --- Talinn
 *
 *
 */

    graph.connect("Kiev", "Lviv", 20);
    graph.connect("Kiev", "Riga", 50);
    graph.connect("Kiev", "Washington", 300);

    graph.connect("Riga", "Talinn", 10); //Kiev - Talinn = 50 + 10
    graph.connect("Lviv", "Madrid", 80);  //Kiev - Madrid = 20 + 80
    graph.connect("Washington" , "New York", 30);  //Kiev - New_York = 30 + 300

    graph.connect("Madrid", "Rome", 30);  //Kiev - Rome = 20 + 80 + 30

    DijkstraSolver solver(graph);

    if( solver.solve("Kiev", "New York") == true){

        solver.printDistances();
    }

    return 0;
}

