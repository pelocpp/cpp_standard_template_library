// =====================================================================================
// Graph Theory Redesign
// =====================================================================================

#include "Graph.h"

using namespace Graph_Theory;

// Testing only graphs
// a) Directed,    Unweighted
// b) Directed,    Weighted
// c) Undirected,  Unweighted
// d) Undirected,  Weighted

void test_graphs_01()
{
    // a) Directed, Unweighted

    Graph<int> graph{};

    graph.addNodes({ 22, 11, 33, 44 });

    graph.addEdge(11, 33);
    graph.addEdge(22, 33);
    graph.addEdge(22, 44);
    graph.addEdge(22, 55);
    graph.addEdge(33, 44);
    graph.addEdge(44, 55);

    std::cout << graph.toString() << std::endl;
}

void test_graphs_01_a()
{
    // a) Directed, Unweighted

    Graph<std::string> graph{};

    graph.addNodes({ "A", "B", "C", "D" });

    graph.addEdge(std::string {"A"}, std::string {"B"});
    graph.addEdge(std::string {"B"}, std::string {"C"});
    graph.addEdge(std::string {"C"}, std::string {"C"});
    graph.addEdge(std::string {"C"}, std::string {"A"});

    std::cout << graph.toString() << std::endl;
}

// ------------------------------------------------------------------------

void test_graphs_02()
{
    // b) Directed, Weighted

    Graph<int, size_t> graph{ Direction::Directed, Weight::Weighted };

    graph.addNodes({ 0, 1, 2, 3, 4, 5 });

    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 20);
    graph.addEdge(1, 4, 10);
    graph.addEdge(1, 3, 50);
    graph.addEdge(2, 4, 33);
    graph.addEdge(2, 3, 20);
    graph.addEdge(3, 4, 20);
    graph.addEdge(3, 5, 2  );
    graph.addEdge(4, 5, 1  );

    std::cout << graph.toString() << std::endl;
}

void test_graphs_02_a()
{
    // b) Directed, Weighted

    Graph<std::string, size_t> graph{ Direction::Directed, Weight::Weighted };

    graph.addNodes({ "A", "B", "C", "D" });

    graph.addEdge(std::string {"A"}, std::string {"B"}, 10);
    graph.addEdge(std::string {"B"}, std::string {"C"}, 20);
    graph.addEdge(std::string {"C"}, std::string {"C"}, 10);
    graph.addEdge(std::string {"C"}, std::string {"A"}, 50);

    std::cout << graph.toString() << std::endl;
}

// ------------------------------------------------------------------------

void test_graphs_03()
{
    // c) Undirected, Unweighted

    Graph<int> graph{ Direction::Undirected };

    graph.addNodes({ 0, 1, 2, 3 });

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 0);

    std::cout << graph.toString() << std::endl;
}

void test_graphs_03_a()
{
    // c) Undirected, Unweighted

    Graph<std::string> graph{ Direction::Undirected };

    graph.addNodes({ "A", "B", "C", "D" });

    graph.addEdge(std::string {"A"}, std::string {"B"});
    graph.addEdge(std::string {"B"}, std::string {"C"});
    graph.addEdge(std::string {"C"}, std::string {"C"});
    graph.addEdge(std::string {"C"}, std::string {"A"});

    std::cout << graph.toString() << std::endl;
}


// ------------------------------------------------------------------------

void test_graphs_04()
{
    // d) Undirected, Weighted

    Graph<int, size_t> graph{ Direction::Undirected, Weight::Weighted };

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

    std::cout << graph.toString() << std::endl;
}

void test_graphs_04_a()
{
    // d) Undirected, Weighted

    Graph<std::string, int> graph{ Direction::Undirected, Weight::Weighted };

    graph.addNodes({ "A", "B", "C", "D" });

    graph.addEdge("A", "B", 3000);
    graph.addEdge("B", "C", 4000);
    graph.addEdge("B", "A", 5000);
    graph.addEdge("C", "D", 6000);
    graph.addEdge("D", "A", 7000);

    std::cout << graph.toString() << std::endl;
}


// =======================================================================

void test_graphs_10()
{
    // Beispiel von DFS

    std::cout << "Directed, Unweighted" << std::endl;

    Graph<int> graph  { Direction::Directed };

    graph.addNodes({ 0, 1, 2, 3, 4, 5, 6, 7 });

    // Directed
    graph.addEdge(0, 3);
    graph.addEdge(1, 0);
    graph.addEdge(1, 2);
    graph.addEdge(1, 4);
    graph.addEdge(2, 7);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 3);
    graph.addEdge(4, 6);
    graph.addEdge(5, 6);
    graph.addEdge(6, 7);

    std::cout << graph.toString() << std::endl;
}

void test_graphs_11()
{
    // Beispiel von DFS
        
    std::cout << "Undirected, Unweighted" << std::endl;

    Graph<int> graph { Direction::Undirected };

    graph.addNodes({ 0, 1, 2, 3, 4, 5, 6, 7 });

    // Undirected
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 7);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 6);
    graph.addEdge(5, 6);
    graph.addEdge(6, 7);

    std::cout << graph.toString() << std::endl;
}

void test_graphs()
{
    test_graphs_01();
    test_graphs_01_a();
    test_graphs_02();
    test_graphs_02_a();
    test_graphs_03();
    test_graphs_03_a();
    test_graphs_04();
    test_graphs_04_a();

    //test_graphs_10();
    //test_graphs_11();
}

// =====================================================================================
// End-of-File
// =====================================================================================
