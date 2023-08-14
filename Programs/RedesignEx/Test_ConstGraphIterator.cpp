// =====================================================================================
// Graph Theory Redesign // Test_ConstGraphIterator.cpp
// =====================================================================================

#include "Graph.h"

#include "Graph_ConstGraphIterator.h"

using namespace Graph_Theory;

void test_graphs_iterators_01()
{
    Graph<int> graph{};

    ConstGraphIterator<std::string, size_t> iter;

    graph.addNodes({ 22, 11, 33, 44, 55 });

    graph.addEdge(11, 33);
    graph.addEdge(22, 33);
    graph.addEdge(22, 44);
    graph.addEdge(22, 55);
    graph.addEdge(33, 44);
    graph.addEdge(44, 55);

    std::cout << graph.toString() << std::endl;
}

// =======================================================================

void test_graph_iterators()
{
    test_graphs_iterators_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
