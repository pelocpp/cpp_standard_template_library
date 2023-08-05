// =====================================================================================
// Graph Theory Redesign // Test_Kruskal.cpp
// =====================================================================================

#include "Graph.h"
#include "Solver_Kruskal.h"

using namespace Graph_Theory;
using namespace Graph_Theory_Kruskal;

void test_kruskal_01()
{
//    // https://www.programiz.com/dsa/kruskal-algorithm
//
//    constexpr int NumNodes = 6;
//
//    WeightedEdge<int> we1{ 0, 1, 4 };
//    WeightedEdge<int> we2{ 0, 2, 4 };
//    WeightedEdge<int> we3{ 1, 2, 2 };
//    WeightedEdge<int> we4{ 2, 3, 3 };
//    WeightedEdge<int> we5{ 2, 5, 2 };
//    WeightedEdge<int> we6{ 2, 4, 4 };
//    WeightedEdge<int> we7{ 3, 4, 3 };
//    WeightedEdge<int> we8{ 5, 4, 3 };
//
//    WeightedUndirectedGraphAdjListRepresentation<int, int> graph{ NumNodes };
//
//    graph.addEdge(we1);
//    graph.addEdge(we2);
//    graph.addEdge(we3);
//    graph.addEdge(we4);
//    graph.addEdge(we5);
//    graph.addEdge(we6);
//    graph.addEdge(we7);
//    graph.addEdge(we8);
//
//    KruskalSolver<int, int> kruskal{ graph };
//    kruskal.solve();
//    kruskal.printMST();
//}

// =====================================================================================
// End-of-File
// =====================================================================================
