// =====================================================================================
// Graph Theory Redesign // TestBFS.cpp
// =====================================================================================

#include "Graph.h"
#include "Solver_BFS.h"

using namespace Graph_Theory;
using namespace Graph_Theory_BFS;

void test_bfs_01()
{
    // Flugverbindungen Nordamerika
    // 
    // Flug von New York nach Urbana
    // Am wenigsten Umsteigen
    // In diesem Beispiel ist der Graph UNGERICHTET, man kann also immer in beide
    // Richtungen fliegen

    std::cout << "Flugverbindungen Nordamerika - BFS" << std::endl;
    std::cout << "Flug von New York nach Urbana - Am wenigsten Umsteigen" << std::endl;

    Graph<std::string> graph{ Direction::Undirected };

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

    const std::string source{ "New York" };
    const std::string target{ "Urbana" };

    //const std::string source{ "Houston" };
    //const std::string target{ "Calgary" };

    const size_t sourceIndex{ graph.getIndexOfNode(source) };
    const size_t targetIndex{ graph.getIndexOfNode(target) };

    std::vector<std::optional<size_t>> paths = bfs.solve(sourceIndex);

    std::vector<size_t> solution = bfs.reconstructPath(sourceIndex, targetIndex, paths);

    bfs.printSolution(solution);
}


void test_bfs_02()
{
    // Flugverbindungen Nordamerika
    // 
    // Flug von New York nach Urbana
    // Am wenigsten Umsteigen
    // In diesem Beispiel ist der Graph GERICHTET, man kann also immer nur in eine
    // Richtung fliegen

    std::cout << "Flugverbindungen Nordamerika - BFS" << std::endl;
    std::cout << "Flug von New York nach Urbana - Am wenigsten Umsteigen" << std::endl;

    Graph<std::string> graph{ Direction::Directed };

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

    const std::string source{ "Urbana" };
    const std::string target{ "New York" };

    const size_t sourceIndex{ graph.getIndexOfNode(source) };
    const size_t targetIndex{ graph.getIndexOfNode(target) };

    std::vector<std::optional<size_t>> paths = bfs.solve(sourceIndex);

    std::vector<size_t> solution = bfs.reconstructPath(sourceIndex, targetIndex, paths);

    bfs.printSolution(solution);
}

void test_bfs()
{
    test_bfs_01();
    test_bfs_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
