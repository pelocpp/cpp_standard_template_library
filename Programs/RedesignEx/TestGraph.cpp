#include "Graph.h"

using namespace Graph_Theory_Redesign;

// Testing only graphs
// a) Undirected,  Unweighted,  Node Descriptions
// b) Undirected,  Weighted,    Node Descriptions
// c) Directed,    Unweighted,  Node Descriptions
// d) Directed,    Weighted,    Node Descriptions
// 
// Same with Weighted Graphs - To be Done

void test_graphs_01()
{
    // c)
    std::cout << "Directed, Unweighted, Node Descriptions" << std::endl;

    Graph<int> graph;

    graph.addNodes({ 22, 11, 33, 44 });

    // graph.sort();

    graph.addEdge(11, 33);
    graph.addEdge(22, 33);
    graph.addEdge(22, 44);
    graph.addEdge(22, 55);
    graph.addEdge(33, 44);
    graph.addEdge(44, 55);

    std::cout << toString(graph) << std::endl;
}

void test_graphs_02()
{
    // c)
    std::cout << "Directed, Unweighted, Node Descriptions" << std::endl;

    Graph<std::string> graph;

    graph.addNodes({
        std::string{"A"},
        std::string{"B"},
        std::string{"C"},
        std::string{"D"}
        }
    );

    graph.addEdge(std::string {"A"}, std::string {"B"});
    graph.addEdge(std::string {"B"}, std::string {"C"});
    graph.addEdge(std::string {"C"}, std::string {"C"});
    graph.addEdge(std::string {"C"}, std::string {"A"});

    std::cout << toString(graph) << std::endl;
}

void test_graphs_03()
{
    // d)
    std::cout << "Directed, Weighted, Node Descriptions" << std::endl;

    Graph<int, size_t> graph { Direction::Directed, Weight::Weighted };

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

    std::cout << toString(graph) << std::endl;
}

void test_graphs_04()
{
    std::cout << "Directed, Unweighted, Node Descriptions" << std::endl;

    Graph<int> graph { Direction::Directed };

    graph.addNodes({ 0, 1, 2, 3, 4, 5, 6, 7 });

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

    std::cout << toString(graph) << std::endl;
}

void test_graphs_05()
{
    std::cout << "Undirected, Unweighted" << std::endl;

    Graph<int> graph { Direction::Undirected };

    graph.addNodes({ 0, 1, 2, 3 });

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 0);

    std::cout << toString(graph) << std::endl;
}

void test_graphs_06()
{
   // std::cout << "Directed, Unweighted, Node Descriptions" << std::endl;

    Graph<std::string, int> graph { Direction::Undirected, Weight::Weighted };

    graph.addNodes({ "A", "B", "C", "D" });

    graph.addEdge("A", "B", 3000);
    graph.addEdge("B", "C", 4000);
    graph.addEdge("B", "A", 5000);
    graph.addEdge("C", "D", 6000);
    graph.addEdge("D", "A", 7000);

    std::cout << toString(graph) << std::endl;
}

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

    std::cout << toString(graph) << std::endl;
}

void test_graphs_11()
{
    // Beispiel von DFS
        
    std::cout << "undirected, Unweighted" << std::endl;

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

    std::cout << toString(graph) << std::endl;
}

void test_graphs()
{
    //test_graphs_01();
    //test_graphs_02();
    //test_graphs_03();
    //test_graphs_04();
    //test_graphs_05();
    test_graphs_06();

    //test_graphs_10();
    //test_graphs_11();
}
