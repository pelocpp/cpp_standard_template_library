// =====================================================================================
// Graph Theory Redesign // Dijkstra.cpp
// =====================================================================================

#include "Graph.h"
#include "Solver_Dijkstra.h"

#include <numeric>
#include <list>

using namespace Graph_Theory;
using namespace Graph_Theory_Dijkstra;

void test_dijkstra_01()
{
    // Beispiel "LMU_Muenchen"

    Graph<int, size_t> graph{ Direction::Directed, Weight::Weighted };

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

    // create solver
    DijkstraSolver<int, size_t> dijkstra{ graph };
    dijkstra.computeShortestPaths(0);
    std::vector<size_t> distances = dijkstra.getDistances();

    std::cout << "Distances from " << 0 << ':' << std::endl;  // TODO: Besser: Name des Knoten
    std::cout << dijkstra.toString(distances, 20) << std::endl;
}

void test_dijkstra_02()
{
    // Beispiel "TU München Europakarte"

    Graph<int, size_t> graph{ Direction::Directed, Weight::Weighted };

    // Beispiel TUM München Europakarte
    constexpr int a = 0;
    constexpr int b = 1;
    constexpr int c = 2;
    constexpr int d = 3;
    constexpr int e = 4;
    constexpr int f = 5;
    constexpr int g = 6;
    constexpr int h = 7;
    constexpr int i = 8;
    constexpr int j = 9;

    // create a list of nodes from 0 up to 9
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), 0);
    graph.addNodes(l.begin(), l.end());

    graph.addEdge(i, a, 464);
    graph.addEdge(a, i, 464);
    graph.addEdge(c, f, 1054);
    graph.addEdge(f, c, 1054);
    graph.addEdge(a, f, 343);
    graph.addEdge(f, a, 343);
    graph.addEdge(c, e, 1364);
    graph.addEdge(e, c, 1364);
    graph.addEdge(a, h, 1435);
    graph.addEdge(h, a, 1435);
    graph.addEdge(f, b, 879);
    graph.addEdge(b, f, 879);
    graph.addEdge(f, e, 1106);
    graph.addEdge(e, f, 1106);
    graph.addEdge(h, g, 837);
    graph.addEdge(g, h, 837);
    graph.addEdge(b, g, 954);
    graph.addEdge(g, b, 954);
    graph.addEdge(j, d, 1053);
    graph.addEdge(d, j, 1053);
    graph.addEdge(g, d, 433);
    graph.addEdge(d, g, 433);
    graph.addEdge(b, h, 811);
    graph.addEdge(h, b, 811);
    graph.addEdge(b, j, 524);
    graph.addEdge(j, b, 524);
    graph.addEdge(j, e, 766);
    graph.addEdge(e, j, 766);

    DijkstraSolver<int, size_t> dijkstra{ graph };
    dijkstra.computeShortestPaths(2);
    std::vector<size_t> distances = dijkstra.getDistances();
}

void test_dijkstra_03()
{
    // Buch "David Kopec", Seite 145 ff.

    Graph<std::string, size_t> graph{ Direction::Undirected, Weight::Weighted };

    graph.addNodes({
        "Seattle", "San Francisco", "Los Angeles",
        "Riverside", "Phoenix", "Chicago", "Boston", "New York", "Atlanta",
        "Miami", "Dallas", "Houston", "Detroit", "Philadelphia", "Washington"
        }
    );

    graph.addEdge("Seattle", "Chicago", 1737);
    graph.addEdge("Seattle", "San Francisco", 678);
    graph.addEdge("San Francisco", "Riverside", 386);
    graph.addEdge("San Francisco", "Los Angeles", 348);
    graph.addEdge("Los Angeles", "Riverside", 50);
    graph.addEdge("Los Angeles", "Phoenix", 357);
    graph.addEdge("Riverside", "Phoenix", 307);
    graph.addEdge("Riverside", "Chicago", 1704);
    graph.addEdge("Phoenix", "Dallas", 887);
    graph.addEdge("Phoenix", "Houston", 1015);
    graph.addEdge("Dallas", "Chicago", 805);
    graph.addEdge("Dallas", "Atlanta", 721);
    graph.addEdge("Dallas", "Houston", 225);
    graph.addEdge("Houston", "Atlanta", 702);
    graph.addEdge("Houston", "Miami", 968);
    graph.addEdge("Atlanta", "Chicago", 588);
    graph.addEdge("Atlanta", "Washington", 543);
    graph.addEdge("Atlanta", "Miami", 604);
    graph.addEdge("Miami", "Washington", 923);
    graph.addEdge("Chicago", "Detroit", 238);
    graph.addEdge("Detroit", "Boston", 613);
    graph.addEdge("Detroit", "Washington", 396);
    graph.addEdge("Detroit", "New York", 482);
    graph.addEdge("Boston", "New York", 190);
    graph.addEdge("New York", "Philadelphia", 81);
    graph.addEdge("Philadelphia", "Washington", 123);

    std::cout << graph.toString(13) << std::endl;

    DijkstraSolver<std::string, size_t> dijkstra{ graph };

    dijkstra.computeShortestPaths(std::string {"Los Angeles"});
    std::vector<size_t> distances = dijkstra.getDistances();

    std::cout << "Distances from Los Angeles:" << std::endl << std::endl;
    std::cout << dijkstra.toString(distances, 14) << std::endl;

    std::vector<size_t> shortestPath = dijkstra.computeShortestPath(
        std::string {"Los Angeles"}, std::string {"Boston"}
    );
    std::cout << graph.toString(shortestPath) << std::endl;
}

void test_dijkstra_03_testing_add_edges()
{
    // Buch "David Kopec", Seite 145 ff.

    Graph<std::string, size_t> graph{ Direction::Undirected, Weight::Weighted };

    graph.addNodes({
        "Seattle", "San Francisco", "Los Angeles",
        "Riverside", "Phoenix", "Chicago", "Boston", "New York", "Atlanta",
        "Miami", "Dallas", "Houston", "Detroit", "Philadelphia", "Washington"
        }
    );

    graph.addEdges(
        {
            { "Seattle", "Chicago", 1737 },
            { "Seattle", "San Francisco", 678 },
            { "San Francisco", "Riverside", 386 },
            { "San Francisco", "Los Angeles", 348 },
            { "Los Angeles", "Riverside", 50 },
            { "Los Angeles", "Phoenix", 357 },
            { "Riverside", "Phoenix", 307 },
            { "Riverside", "Chicago", 1704 },
            { "Phoenix", "Dallas", 887 },
            { "Phoenix", "Houston", 1015 },
            { "Dallas", "Chicago", 805 },
            { "Dallas", "Atlanta", 721 },
            { "Dallas", "Houston", 225 },
            { "Houston", "Atlanta", 702 },
            { "Houston", "Miami", 968 },
            { "Atlanta", "Chicago", 588 },
            { "Atlanta", "Washington", 543 },
            { "Atlanta", "Miami", 604 },
            { "Miami", "Washington", 923 },
            { "Chicago", "Detroit", 238 },
            { "Detroit", "Boston", 613 },
            { "Detroit", "Washington", 396 },
            { "Detroit", "New York", 482 },
            { "Boston", "New York", 190 },
            { "New York", "Philadelphia", 81 },
            { "Philadelphia", "Washington", 123 }
        }
    );

    std::cout << graph.toString(13) << std::endl;

    DijkstraSolver<std::string, size_t> dijkstra{ graph };

    dijkstra.computeShortestPaths(std::string {"Los Angeles"});
    std::vector<size_t> distances = dijkstra.getDistances();

    std::cout << "Distances from Los Angeles:" << std::endl << std::endl;
    std::cout << dijkstra.toString(distances, 14) << std::endl;

    std::vector<size_t> shortestPath = dijkstra.computeShortestPath(
        std::string {"Los Angeles"}, std::string {"Boston"}
    );
    std::cout << graph.toString(shortestPath) << std::endl;
}

void test_dijkstra_04()
{
    // Beispiel "TU München Europakarte"

    Graph<std::string, size_t> graph{ Direction::Undirected, Weight::Weighted };

    // Beispiel TUM München Europakarte
    const std::string a { std::string("London") };
    const std::string b { std::string("Berlin") };
    const std::string c { std::string("Madrid") };
    const std::string d { std::string("Kiew") };
    const std::string e { std::string("Rom") };
    const std::string f { std::string("Paris") };
    const std::string g { std::string("Minsk") };
    const std::string h { std::string("Stockholm") };
    const std::string i { std::string("Dublin") };
    const std::string j { std::string("Wien") };

    graph.addNodes({ a, b, c, d, e, f, g, h, i, j});

    graph.addEdge(i, a, 464);
    graph.addEdge(c, f, 1054);
    graph.addEdge(a, f, 343);
    graph.addEdge(c, e, 1364);
    graph.addEdge(a, h, 1435);
    graph.addEdge(f, b, 879);
    graph.addEdge(f, e, 1106);
    graph.addEdge(h, g, 837);
    graph.addEdge(b, g, 954);
    graph.addEdge(j, d, 1053);
    graph.addEdge(g, d, 433);
    graph.addEdge(b, h, 811);
    graph.addEdge(b, j, 524);
    graph.addEdge(j, e, 766);

    std::cout << graph.toString(9) << std::endl;

    DijkstraSolver<std::string, size_t> dijkstra{ graph };

    dijkstra.computeShortestPaths(std::string {"Dublin"});
    std::vector<size_t> distances = dijkstra.getDistances();

    std::cout << "Distances from Dublin:" << std::endl << std::endl;
    std::cout << dijkstra.toString(distances, 10) << std::endl;

    std::vector<size_t> shortestPath = dijkstra.computeShortestPath(
        std::string {"Dublin"}, std::string {"Minsk"}
    );
    std::cout << graph.toString(shortestPath) << std::endl;
}

void test_dijkstra()
{
    //test_dijkstra_01();
    //test_dijkstra_02();
    //test_dijkstra_03();
    test_dijkstra_03_testing_add_edges();
    //test_dijkstra_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
