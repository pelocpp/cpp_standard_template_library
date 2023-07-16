#include "Graph.h"

namespace Graph_Theory_Graphs
{
    using namespace Graph_Theory_Redesign;

    // testing only graphs
    // a) Undirected, Unweighted, No Node Descriptions
    // b) Undirected, Unweighted, Node Descriptions
    // c) Directed,   Unweighted, No Node Descriptions
    // d) Directed,   Unweighted, Node Descriptions
    // 
    // Same with Weighted Graphs - To be Done

    void test_00()
    {
        Graph<int> graph;

        // Insert some nodes and edges.

        graph.addNode(11);
        graph.addNode(22);
        graph.addNode(33);
        graph.addNode(44);
        graph.addNode(55);

        graph.addEdge(11, 33);
        graph.addEdge(22, 33);
        graph.addEdge(22, 44);
        graph.addEdge(22, 55);
        graph.addEdge(33, 44);
        graph.addEdge(44, 55);

        std::string dot = toDot<int>(graph, "Beispiel");

        std::cout << dot << std::endl;

        std::cout << "Graph: " << toString(graph) << std::endl;
    }

    //void test_a()
    //{
    //    std::cout << "Undirected, Unweighted, No Node Descriptions" << std::endl;

    //    Graph graph{ 4 };

    //    graph.addEdge(0, 1);
    //    graph.addEdge(1, 2);
    //    graph.addEdge(2, 3);
    //    graph.addEdge(3, 0);

    //    std::cout << graph << std::endl;
    //}

    void test_b()
    {
        std::cout << "Undirected, Unweighted, Node Descriptions" << std::endl;

        // TODO: Klären, ob ein Konstruktor mit der Knotenanzahl Sinn ergibt
        //  Graph<std::string> graph{ 4 };
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

        std::string dot = toDot<std::string>(graph, "Beispiel");

        std::cout << dot << std::endl;

        std::cout << "Graph: " << toString(graph) << std::endl;
    }

    //void test_c()
    //{
    //    std::cout << "Directed, Unweighted, No Node Descriptions" << std::endl;

    //    UnweightedDirectedGraphAdjListRepresentation<int> graph{ 4 };

    //    graph.addEdge(0, 1);
    //    graph.addEdge(1, 2);
    //    graph.addEdge(2, 3);
    //    graph.addEdge(3, 0);

    //    std::cout << graph << std::endl;
    //}

    //void test_d()
    //{
    //    std::cout << "Directed, Unweighted, Node Descriptions" << std::endl;

    //    UnweightedDirectedGraphAdjListRepresentation<std::string> graph{ 4 };

    //    graph.seTNodeDatas({
    //        std::string{"A"}, std::string{"B"}, std::string{"C"}, std::string{"C"}
    //        });

    //    graph.addEdge(0, 1);
    //    graph.addEdge(1, 2);
    //    graph.addEdge(2, 3);
    //    graph.addEdge(3, 0);

    //    std::cout << graph << std::endl;
    //}

    void test_04_a()
    {
        // Beispiel "LMU_Muenchen"

        // WEITER: Irgendwie mit Template Specializtion Weigthed und UnWeighted !!!

        Graph<int, size_t> graph;

        graph.addNode(0);
        graph.addNode(1);
        graph.addNode(2);
        graph.addNode(3);
        graph.addNode(4);
        graph.addNode(5);

        graph.addEdge(0, 1, 10);
        graph.addEdge(0, 2, 20);
        graph.addEdge(1, 4, 10);
        graph.addEdge(1, 3, 50);
        graph.addEdge(2, 4, 33);
        graph.addEdge(2, 3, 20);
        graph.addEdge(3, 4, 20);
        graph.addEdge(3, 5, 2);
        graph.addEdge(4, 5, 1);

        std::string dot = toDot<int, size_t>(graph, "Beispiel");

        std::cout << dot << std::endl;

        std::cout << "Graph: " << toString(graph) << std::endl;
    }

    void test_graphs()
    {
        test_00();
    }
}