// =====================================================================================
// Graph Theory Redesign // TestBFS.cpp
// =====================================================================================

#include "Graph.h"
#include "Solver_BFS.h"

#include <numeric>
#include <list>

using namespace Graph_Theory;
using namespace Graph_Theory_BFS;

void test_bfs_01()
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

    std::cout << graph.toString(13) << std::endl;

    BFSSolver<std::string> bfs{ graph };

    const std::string source{ "Boston" };
    const std::string target{ "Miami" };

    //const std::string source{ "Los Angeles" };
    //const std::string target{ "Washington" };

    const size_t sourceIndex{ graph.getIndexOfNode(source) };
    const size_t targetIndex{ graph.getIndexOfNode(target) };

    std::vector<std::optional<size_t>> paths = bfs.solve(sourceIndex);

    Path solution = bfs.reconstructPath(sourceIndex, targetIndex, paths);
    std::cout << graph.toString(solution) << std::endl << std::endl;
}

void test_bfs_02()
{
    // Das Beispiel orientiert sich an einem Online Tutorial von Hans Werner Lang von der Hochschule Flensburg:
    // 3. Aufgabe im Markdown File

    Graph<int> graph{ Direction::Undirected, Weight::Unweighted };

    // create a list of nodes from 0 uo to 22
    std::list<int> l(23);
    std::iota(l.begin(), l.end(), 0);
    graph.addNodes(l.begin(), l.end());

    graph.addEdges({
        {0, 5}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {1, 7}, {5, 8}, {6, 10}, {8, 9},
        {9, 10}, {7, 11}, {8, 15}, {11, 12}, {12, 13}, {13, 14}, {14, 15}, {11, 16},
        {12, 17}, {13, 18}, {15, 19}, {16, 17}, {17, 18}, {19, 20}, {20, 21}, {18, 22}
     });

    std::cout << graph.toString(2) << std::endl;


    BFSSolver<int> bfs{ graph };

    const int source{ 0 };
    const int target{22 };

    const size_t sourceIndex{ graph.getIndexOfNode(source) };
    const size_t targetIndex{ graph.getIndexOfNode(target) };

    std::vector<std::optional<size_t>> paths = bfs.solve(sourceIndex);

    Path solution = bfs.reconstructPath(sourceIndex, targetIndex, paths);
    std::cout << graph.toString(solution) << std::endl << std::endl;
}

void test_bfs_03()
{
    // Das Beispiel orientiert sich an einem Online Tutorial von Hans Werner Lang von der Hochschule Flensburg:
    // "Wir wollen einen ähnlichen Graphen wie aus Abbildung 2 betrachten,
    //  nur dieses Mal soll es sich um einen gerichteten Graphen handeln"
    // 4. Aufgabe im Markdown File

    Graph<int> graph{ Direction::Directed, Weight::Unweighted };

    // create a list of nodes from 0 uo to 22
    std::list<int> l(23);
    std::iota(l.begin(), l.end(), 0);
    graph.addNodes(l.begin(), l.end());

    graph.addEdges({
        {0, 5}, {5, 4}, {4, 3}, {3, 2}, {2, 1}, {5, 6}, {1, 7}, {5, 8}, {6, 10}, {9, 8},
        {10, 9}, {7, 11}, {8, 15}, {15, 14}, {14, 13}, {11, 12}, {12, 13}, {11, 16}, {12, 17},
        {13, 18}, {15, 19}, {16, 17}, {17, 18}, {20, 19}, {21, 20}, {18, 22}
    });

    std::cout << graph.toString(2) << std::endl;

    BFSSolver<int> bfs{ graph };

    const int source{ 0 };
    const int target{ 21 };

    //const int source{ 6 };
    //const int target{ 18 };

    const size_t sourceIndex{ graph.getIndexOfNode(source) };
    const size_t targetIndex{ graph.getIndexOfNode(target) };

    std::vector<std::optional<size_t>> paths = bfs.solve(sourceIndex);

    Path solution = bfs.reconstructPath(sourceIndex, targetIndex, paths);
    std::cout << graph.toString(solution) << std::endl << std::endl;
}

void test_bfs()
{
    test_bfs_01();
    test_bfs_02();
    test_bfs_03();
}

// =====================================================================================
// End-of-File
// =====================================================================================
