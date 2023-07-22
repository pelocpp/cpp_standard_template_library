// =====================================================================================
// Graph Theory Redesign // TestBFS.cpp
// =====================================================================================

#include "Graph.h"
#include "Solver_BFS.h"

using namespace Graph_Theory;
using namespace Graph_Theory_BFS;

void test_bfs_01()
{
    //std::cout << "Redesign Graph Theory - BFS" << std::endl;

    //Graph<int> graph{};

    //graph.addNodes({ 0, 1, 2, 3, 4, 5, 6 });

    //graph.addEdge(0, 3);
    //graph.addEdge(1, 0);
    //graph.addEdge(1, 2);
    //graph.addEdge(1, 4);
    //graph.addEdge(2, 7);
    //graph.addEdge(3, 4);
    //graph.addEdge(3, 5);
    //graph.addEdge(4, 3);
    //graph.addEdge(4, 6);
    //graph.addEdge(5, 6);
    //graph.addEdge(6, 7);

    //std::cout << graph.toString() << std::endl; 
    //
    //BFSSolver bfs{ graph };

    //std::vector<std::optional<size_t>> paths = bfs.solve(0);

    //std::vector<size_t> solution = bfs.reconstructPath(0, 4, paths);

    //bfs.printSolution(solution);

    // Flugverbindungen Nordamerika
    // test_10
    // Flug von New Yort nach Urbana
    // Flug von Houston nach Calgary
    // Am wenigsten Umsteigen
    // In diesem Beispiel ist der Graph UNGERICHTET, man kann also immer in beide
    // Richtungen fliegen

    std::cout << "Flugverbindungen Nordamerika - BFS" << std::endl;
    std::cout << "Flug von New Yort nach Urbana - Am wenigsten Umsteigen" << std::endl;

    Graph<std::string> graph{ Direction::Undirected };

    // 0 New York
    // 1 Toronto
    // 2 Chicago
    // 3 Urbana
    // 4 Houston
    // 5 Denver
    // 6 Calgary
    // 7 Los Angeles

    graph.addNodes({
        "New York",
        "Toronto",
        "Chicago",
        "Urbana",
        "Houston",
        "Denver",
        "Calgary",
        "Los Angeles"
    });

    graph.addEdge("New York", "Toronto");
    graph.addEdge("New York", "Chicago");
    graph.addEdge("New York", "Denver");
    graph.addEdge("Toronto", "Chicago");
    graph.addEdge("Toronto", "Calgary");
    graph.addEdge("Toronto", "Los Angeles");
    graph.addEdge("Chicago", "Denver");
    graph.addEdge("Houston", "Los Angeles");
    graph.addEdge("Denver", "Urbana");
    graph.addEdge("Denver", "Houston");
    graph.addEdge("Denver", "Los Angeles");

    BFSSolver<std::string> bfs{ graph };

    std::vector<std::optional<size_t>> paths = bfs.solve(7);

    std::vector<size_t> solution = bfs.reconstructPath(7, 0, paths);

    bfs.printSolution(solution);
}

void test_bfs()
{
    test_bfs_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
