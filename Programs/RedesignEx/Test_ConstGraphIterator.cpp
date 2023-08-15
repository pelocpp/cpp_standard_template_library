// =====================================================================================
// Graph Theory Redesign // Test_ConstGraphIterator.cpp
// =====================================================================================

#include "Graph.h"

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

void test_graphs_iterators_02()
{
    Graph<size_t> graph{};

    graph.addNodes({ 22, 11, 33, 44, 55 });

    graph.addEdge(11, 33);
    graph.addEdge(22, 33);
    graph.addEdge(22, 44);
    graph.addEdge(22, 55);
    graph.addEdge(33, 44);
    graph.addEdge(44, 55);

    std::cout << graph.toString() << std::endl;

    ConstGraphIterator<size_t> iter = graph.begin();

    auto& elem = *iter;

    ++iter;

    auto& elem2 = *iter;
}

void test_graphs_iterators_03()
{
    // b) Directed, Weighted

    Graph<std::string, size_t> graph{ Direction::Directed, Weight::Weighted };

    graph.addNodes({ "A", "B", "C", "D" });

    graph.addEdge(std::string{ "A" }, std::string{ "B" }, 10);
    graph.addEdge(std::string{ "B" }, std::string{ "C" }, 20);
    graph.addEdge(std::string{ "C" }, std::string{ "C" }, 10);
    graph.addEdge(std::string{ "C" }, std::string{ "A" }, 50);

    std::cout << graph.toString() << std::endl;

    std::cout << graph.toStringRaw() << std::endl;

    ConstGraphIterator<std::string, size_t> iter = graph.begin();

    auto& elem = *iter;

    ++iter;

    auto& elem2 = *iter;
}

// =======================================================================

void test_graph_iterators()
{
    //test_graphs_iterators_01();
    //test_graphs_iterators_02();
    test_graphs_iterators_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
