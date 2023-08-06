// =====================================================================================
// Graph Theory Redesign // Test_Kruskal.cpp
// =====================================================================================

#include "Graph.h"
#include "Solver_Kruskal.h"

using namespace Graph_Theory;
using namespace Graph_Theory_Kruskal;

void test_kruskal_01()
{
    // https://www.programiz.com/dsa/kruskal-algorithm

    Graph<std::string, size_t> graph{ Direction::Undirected, Weight::Weighted };

    graph.addNodes({ "0", "1", "2", "3", "4", "5" });

    graph.addEdge("0", "1", 4);
    graph.addEdge("0", "2", 4);
    graph.addEdge("1", "2", 2);
    graph.addEdge("2", "3", 3);
    graph.addEdge("2", "5", 2);
    graph.addEdge("2", "4", 4);
    graph.addEdge("3", "4", 3);
    graph.addEdge("5", "4", 3);

    KruskalSolver<std::string, size_t> kruskal{ graph };
    kruskal.solve();
    kruskal.printMST();
}

void test_kruskal()
{
    test_kruskal_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
