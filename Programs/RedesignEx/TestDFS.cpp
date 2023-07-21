#include "Graph.h"
#include "Solver_DFS.h"

using namespace Graph_Theory_Redesign;
using namespace Graph_Theory_DFS;

void test_dfs_01()
{
    // Siehe Bild im Markdown - das Beispiel funkioniert !!!

    std::cout << "Graph Theory - DFS" << std::endl;

    // Funktioniert für gerichtete und ungerichtete Graphen !!!
    // Aber die Ergebnisse sind unterschiedlich !!!!!!!!!!!!!!!!!!

    Graph<int> graph { Direction::Directed };

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

     std::cout << "Graph " << toString(graph) << std::endl;

    DFSSolver dfs{ graph };

    const size_t source{ 1 };
    const size_t target{ 6 };

    if (std::vector<size_t> resultPath; dfs.findPathAny(source, target, resultPath))
    {
        std::cout << "Path exists from " << source << " to " << target << ":" << std::endl;
        dfs.printPath(resultPath);
    }
    else {
        std::cout << "No path exists between " << source << " and " << target << "." << std::endl;
    }
    std::cout << std::endl;

    // -------------

    dfs.findPathAll(source, target);

    if (size_t count; (count = dfs.countFoundPaths()) != 0)
    {
        std::cout << "Found " << count << " solutions:" << std::endl;
        dfs.printPaths();
    }
    else {
        std::cout << "No path exists between " << source << " and " << target << "." << std::endl;
    }
}

void test_dfs_02()
{
    // Siehe Bild im Markdown - das Beispiel funkioniert !!!

    std::cout << "Graph Theory - DFS" << std::endl;

    // Funktioniert für gerichtete und ungerichtete Graphen !!!
    // Aber die Ergebnisse sind unterschiedlich !!!!!!!!!!!!!!!!!!

    Graph<int> graph {  Direction::Undirected };

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

    std::cout << "Graph " << toString(graph) << std::endl;

    DFSSolver dfs{ graph };

    const size_t source{ 2 };
    const size_t target{ 7 };

    if (std::vector<size_t> resultPath; dfs.findPathAny(source, target, resultPath))
    {
        std::cout << "Path exists from " << source << " to " << target << ":" << std::endl;
        dfs.printPath(resultPath);
    }
    else {
        std::cout << "No path exists between " << source << " and " << target << "." << std::endl;
    }
    std::cout << std::endl;

    // -------------

    dfs.findPathAll(source, target);

    if (size_t count; (count = dfs.countFoundPaths()) != 0)
    {
        std::cout << "Found " << count << " solutions:" << std::endl;
        dfs.printPaths();
    }
    else {
        std::cout << "No path exists between " << source << " and " << target << "." << std::endl;
    }
}

void test_dfs_03()
{
    // Buch Kopec - Finding the shortest path

    Graph<std::string> graph{ Direction::Undirected, Weight::Unweighted };

    graph.addNodes({
        "Seattle", "San Francisco", "Los Angeles",
        "Riverside", "Phoenix", "Chicago", "Boston", "New York", "Atlanta",
        "Miami", "Dallas", "Houston", "Detroit", "Philadelphia", "Washington"
        }
    );

    graph.addEdge("Seattle", "Chicago");
    graph.addEdge("Seattle", "San Francisco");
    graph.addEdge("San Francisco", "Riverside");
    graph.addEdge("San Francisco", "Los Angeles");
    graph.addEdge("Los Angeles", "Riverside");
    graph.addEdge("Los Angeles", "Phoenix");
    graph.addEdge("Riverside", "Phoenix");
    graph.addEdge("Riverside", "Chicago");
    graph.addEdge("Phoenix", "Dallas");
    graph.addEdge("Phoenix", "Houston");
    graph.addEdge("Dallas", "Chicago");
    graph.addEdge("Dallas", "Atlanta");
    graph.addEdge("Dallas", "Houston");
    graph.addEdge("Houston", "Atlanta");
    graph.addEdge("Houston", "Miami");
    graph.addEdge("Atlanta", "Chicago");
    graph.addEdge("Atlanta", "Washington");
    graph.addEdge("Atlanta", "Miami");
    graph.addEdge("Miami", "Washington");
    graph.addEdge("Chicago", "Detroit");
    graph.addEdge("Detroit", "Boston");
    graph.addEdge("Detroit", "Washington");
    graph.addEdge("Detroit", "New York");
    graph.addEdge("Boston", "New York");
    graph.addEdge("New York", "Philadelphia");
    graph.addEdge("Philadelphia", "Washington");

    std::cout << toString(graph) << std::endl;

    DFSSolver<std::string> dfs{ graph };

    const std::string source{ "Boston" };
    const std::string target{ "Miami" };

    const size_t sourceIndex{ graph.getIndexOfNode (source) };
    const size_t targetIndex{ graph.getIndexOfNode(target) };

    //if (std::vector<size_t> resultPath; dfs.findPathAny(sourceIndex, targetIndex, resultPath))
    //{
    //    std::cout << "Path exists from " << source << " to " << target << ":" << std::endl;
    //    dfs.printPath(resultPath);
    //}
    //else {
    //    std::cout << "No path exists between " << source << " and " << target << "." << std::endl;
    //}

    dfs.findPathAll(sourceIndex, targetIndex);

    if (size_t count; (count = dfs.countFoundPaths()) != 0)
    {
        std::cout << "Found " << count << " solutions:" << std::endl;
        // dfs.printPaths();

        // std::vector<size_t> 
        auto path = dfs.getShortestPath();

        std::cout << "Stopper" << std::endl;
    }
    else {
        std::cout << "No path exists between " << source << " and " << target << "." << std::endl;
    }
}

void test_dfs()
{
    //test_dfs_01();
    //test_dfs_02();
    test_dfs_03();
}
