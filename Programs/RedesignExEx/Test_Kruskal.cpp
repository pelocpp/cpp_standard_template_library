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

    constexpr int NumNodes = 6;

    Graph<int, int> graph{ Direction::Undirected, Weight::Weighted };

    graph.addNodes({ 0, 1, 2, 3, 4, 5 });

    //Edge<int> we1{ 0, 1, 4 };
    //Edge<int> we2{ 0, 2, 4 };
    //Edge<int> we3{ 1, 2, 2 };
    //Edge<int> we4{ 2, 3, 3 };
    //Edge<int> we5{ 2, 5, 2 };
    //Edge<int> we6{ 2, 4, 4 };
    //Edge<int> we7{ 3, 4, 3 };
    //Edge<int> we8{ 5, 4, 3 };

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 3);
    graph.addEdge(2, 5, 2);
    graph.addEdge(2, 4, 4);
    graph.addEdge(3, 4, 3);
    graph.addEdge(5, 4, 3);

    KruskalSolver<int, int> kruskal{ graph };
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
