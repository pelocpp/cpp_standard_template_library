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
    iter++;

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

void test_graphs_iterators_04()
{
    // b) Directed, Weighted

    Graph<std::string, size_t> graph{ Direction::Directed, Weight::Weighted };

    graph.addNodes({ "A", "B", "C", "D" });

    graph.addEdge(std::string{ "A" }, std::string{ "B" }, 10);
    graph.addEdge(std::string{ "B" }, std::string{ "C" }, 20);
    graph.addEdge(std::string{ "C" }, std::string{ "C" }, 10);
    graph.addEdge(std::string{ "C" }, std::string{ "A" }, 50);

    std::cout << graph.toString() << std::endl;

    //std::cout << graph.toStringRaw() << std::endl;

    for (const auto& x : graph) {

        //T& getDataFromNode(size_t index);
        //const T& getDataFromNode(size_t index) const;

        auto target = getTrackTarget(x);
        const std::string data = graph.getDataFromNode(target);
        auto weight = getTrackWeight(x);

        std::cout << "Target: " << target << " [" << data << "] - Weight: "  << weight.value() << std::endl;
    }
}

void test_graphs_iterators_05()
{
    // b) Directed, Weighted

    Graph<std::string, size_t> graph{ Direction::Directed, Weight::Weighted };

    graph.addNodes({ "A", "B", "C", "D", "E", "F" });

    graph.addEdge(std::string{ "B" }, std::string{ "C" }, 10);
    graph.addEdge(std::string{ "B" }, std::string{ "D" }, 20);
    graph.addEdge(std::string{ "B" }, std::string{ "E" }, 30);

    graph.addEdge(std::string{ "D" }, std::string{ "A" }, 40);
    graph.addEdge(std::string{ "D" }, std::string{ "B" }, 50);
    graph.addEdge(std::string{ "D" }, std::string{ "C" }, 60);

    graph.addEdge(std::string{ "F" }, std::string{ "A" }, 70);

    std::cout << graph.toString() << std::endl;
    //std::cout << graph.toStringRaw() << std::endl;

    for (const auto& x : graph) {

        //T& getDataFromNode(size_t index);
        //const T& getDataFromNode(size_t index) const;

        auto target = getTrackTarget(x);
        const std::string data = graph.getDataFromNode(target);
        auto weight = getTrackWeight(x);

        std::cout << "Target: " << target << " [" << data << "] - Weight: " << weight.value() << std::endl;
    }
}

void test_graphs_iterators_06()
{
    // b) Directed, Weighted

    // TESTING EMPTY GRAPH 
    // -------------------

    Graph<std::string, size_t> graph{ Direction::Directed, Weight::Weighted };

    std::cout << graph.toString() << std::endl;
    std::cout << graph.toStringRaw() << std::endl;

    for (const auto& x : graph) {

        auto target = getTrackTarget(x);
        const std::string data = graph.getDataFromNode(target);
        auto weight = getTrackWeight(x);

        std::cout << "Target: " << target << " [" << data << "] - Weight: " << weight.value() << std::endl;
    }
}

// =======================================================================

void test_graph_iterators()
{
    //test_graphs_iterators_01();
    //test_graphs_iterators_02();
    //test_graphs_iterators_03();
    //test_graphs_iterators_04();
    //test_graphs_iterators_05();
    test_graphs_iterators_06();
}

// =====================================================================================
// End-of-File
// =====================================================================================
