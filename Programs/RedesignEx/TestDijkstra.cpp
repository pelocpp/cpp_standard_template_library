// =====================================================================================
// Graph Theory Redesign // Dijkstra.cpp
// =====================================================================================

#include "Graph.h"
#include "Solver_Dijkstra.h"

#include <numeric>
#include <list>

using namespace Graph_Theory;
using namespace Graph_Theory_Dijkstra;

void test_dijkstra_01()
{
    // Beispiel "LMU_Muenchen"

    Graph<int, size_t> graph{ Direction::Directed, Weight::Weighted };

    graph.addNodes({ 0, 1, 2, 3, 4, 5 });

    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 20);
    graph.addEdge(1, 4, 10);
    graph.addEdge(1, 3, 50);
    graph.addEdge(2, 4, 33);
    graph.addEdge(2, 3, 20);
    graph.addEdge(3, 4, 20);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 5, 1);

    // create solver
    DijkstraSolver<int, size_t> dijkstra{ graph };
    std::vector<size_t> distances = dijkstra.computeShortestPaths(0);
    dijkstra.printDistances(distances);
}

void test_dijkstra_02()
{
    // Beispiel "TU München Europakarte"

    Graph<int, size_t> graph{ Direction::Directed, Weight::Weighted };

    // Beispiel TUM München Europakarte
    constexpr int a = 0;
    constexpr int b = 1;
    constexpr int c = 2;
    constexpr int d = 3;
    constexpr int e = 4;
    constexpr int f = 5;
    constexpr int g = 6;
    constexpr int h = 7;
    constexpr int i = 8;
    constexpr int j = 9;

    // create a list of nodes from 0 up to 9
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), 0);
    graph.addNodes(l.begin(), l.end());

    graph.addEdge(i, a, 464);
    graph.addEdge(a, i, 464);
    graph.addEdge(c, f, 1054);
    graph.addEdge(f, c, 1054);
    graph.addEdge(a, f, 343);
    graph.addEdge(f, a, 343);
    graph.addEdge(c, e, 1364);
    graph.addEdge(e, c, 1364);
    graph.addEdge(a, h, 1435);
    graph.addEdge(h, a, 1435);
    graph.addEdge(f, b, 879);
    graph.addEdge(b, f, 879);
    graph.addEdge(f, e, 1106);
    graph.addEdge(e, f, 1106);
    graph.addEdge(h, g, 837);
    graph.addEdge(g, h, 837);
    graph.addEdge(b, g, 954);
    graph.addEdge(g, b, 954);
    graph.addEdge(j, d, 1053);
    graph.addEdge(d, j, 1053);
    graph.addEdge(g, d, 433);
    graph.addEdge(d, g, 433);
    graph.addEdge(b, h, 811);
    graph.addEdge(h, b, 811);
    graph.addEdge(b, j, 524);
    graph.addEdge(j, b, 524);
    graph.addEdge(j, e, 766);
    graph.addEdge(e, j, 766);

    DijkstraSolver<int, size_t> dijkstra{ graph };
    std::vector<size_t> distances = dijkstra.computeShortestPaths(2);
    dijkstra.printDistances(distances);
}

void test_dijkstra()
{
    // test_dijkstra_01();
    test_dijkstra_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
