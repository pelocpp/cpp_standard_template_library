// =====================================================================================
// Program
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <stack>
#include <deque>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <tuple>
#include <optional>
#include <functional>
#include <utility>
#include <cassert>

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../Include/Globals.h"
#include "../Include/Node.h"
#include "../Include/NodeDetails.h"
#include "../Include/Edge.h"
#include "../Include/EdgeDetails.h"

#include "../Include/GraphInterface.h"
//#include "../Include/GraphAdjList.h"
#include "../Include/GraphAdjMat.h"

// General testing functions for nodes, edges and graphs
//

void test_01_unweighted_undirected()
{
    // =====================================================
    // Haus des Nikolas: ungerichtet, ungewichtet

    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    Node<TestNodeDetails> n1{ 0, { "Node 1"} };
    Node<TestNodeDetails> n2{ 1, { "Node 2"} };
    Node<TestNodeDetails> n3{ 2, { "Node 3"} };
    Node<TestNodeDetails> n4{ 3, { "Node 4"} };
    Node<TestNodeDetails> n5{ 4, { "Node 5"} };

    std::vector<Node<TestNodeDetails>> nodes = {
        n1, n2, n3, n4, n5
    };

    // vector of graph edges (Haus des Nikolas, ungerichtet)
    std::vector<UnweightedEdge<TestEdgeDetails>> edges = {
        {0, 1, { "Kante zwischen 0 und 1" } }, 
        {0, 2, { "Kante zwischen 0 und 2" } }, 
        {0, 3, { "Kante zwischen 0 und 3" } },
        {1, 2, { "Kante zwischen 1 und 2" } }, 
        {1, 3, { "Kante zwischen 1 und 3" } },
        {2, 3, { "Kante zwischen 2 und 3" } }, 
        {2, 4, { "Kante zwischen 2 und 4" } },
        {3, 4, { "Kante zwischen 3 und 4" } }
    };

    // graph with 5 nodes (vertices)
    GraphAdjMatrix<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> testGraph(Direction::undirected);

    testGraph.addNodes(nodes);
    testGraph.addEdges(edges);

    std::string graph = testGraph.toString();
    std::cout << graph << std::endl;

    std::string nodesDisplay = testGraph.toStringNodes();
    std::cout << nodesDisplay << std::endl;

    std::string edgesDisplay = testGraph.toStringEdges<TestEdgeDetails>();
    std::cout << edgesDisplay << std::endl;
}

void test_01_weighted_directed()
{
    // =====================================================
    // Haus des Nikolas: gerichtet, gewichtet

    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    Node<TestNodeDetails> n1{ 0, { "Node 1"} };
    Node<TestNodeDetails> n2{ 1, { "Node 2"} };
    Node<TestNodeDetails> n3{ 2, { "Node 3"} };
    Node<TestNodeDetails> n4{ 3, { "Node 4"} };
    Node<TestNodeDetails> n5{ 4, { "Node 5"} };

    std::vector<Node<TestNodeDetails>> nodes = {
        n1, n2, n3, n4, n5
    };

    // vector of graph edges
    std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
        {0, 1, 100, { "Kante zwischen 0 und 1" } },
        {0, 2, 101, { "Kante zwischen 0 und 2" } },
        {0, 3, 102, { "Kante zwischen 0 und 3" } },
        {1, 2, 103, { "Kante zwischen 1 und 2" } },
        {1, 3, 104, { "Kante zwischen 1 und 3" } },
        {2, 3, 105, { "Kante zwischen 2 und 3" } },
        {2, 4, 106, { "Kante zwischen 2 und 4" } },
        {3, 4, 107, { "Kante zwischen 3 und 4" } }
    };

    // graph with 5 nodes (vertices)
    GraphAdjMatrix<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> testGraph(Direction::directed);

    testGraph.addNodes(nodes);
    testGraph.addEdges(edges);

    std::string graph = testGraph.toString();
    std::cout << graph << std::endl;

    std::string nodesDisplay = testGraph.toStringNodes();
    std::cout << nodesDisplay << std::endl;

    std::string edgesDisplay = testGraph.toStringEdges<TestEdgeDetails>();
    std::cout << edgesDisplay << std::endl;
}


void test_01_unweighted_directed()
{
    // =====================================================
    // Haus des Nikolas: gerichtet, ungewichtet

    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    Node<TestNodeDetails> n1{ 0, { "Node 1"} };
    Node<TestNodeDetails> n2{ 1, { "Node 2"} };
    Node<TestNodeDetails> n3{ 2, { "Node 3"} };
    Node<TestNodeDetails> n4{ 3, { "Node 4"} };
    Node<TestNodeDetails> n5{ 4, { "Node 5"} };

    std::vector<Node<TestNodeDetails>> nodes = {
        n1, n2, n3, n4, n5
    };

    // vector of graph edges (Haus des Nikolas, ungerichtet)
    std::vector<UnweightedEdge<TestEdgeDetails>> edges = {
        {0, 1, { "Kante zwischen 0 und 1" } },
        {0, 2, { "Kante zwischen 0 und 2" } },
        {0, 3, { "Kante zwischen 0 und 3" } },
        {1, 2, { "Kante zwischen 1 und 2" } },
        {1, 3, { "Kante zwischen 1 und 3" } },
        {2, 3, { "Kante zwischen 2 und 3" } },
        {2, 4, { "Kante zwischen 2 und 4" } },
        {3, 4, { "Kante zwischen 3 und 4" } }
    };

    // graph with 5 nodes (vertices)
    GraphAdjMatrix<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> testGraph(Direction::directed);

    testGraph.addNodes(nodes);
    testGraph.addEdges(edges);

    std::string graph = testGraph.toString();
    std::cout << graph << std::endl;

    std::string nodesDisplay = testGraph.toStringNodes();
    std::cout << nodesDisplay << std::endl;

    std::string edgesDisplay = testGraph.toStringEdges<TestEdgeDetails>();
    std::cout << edgesDisplay << std::endl;
}

void test_01_weighted_undirected()
{
    // =====================================================
    // Haus des Nikolas: gerichtet, gewichtet

    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    Node<TestNodeDetails> n1{ 0, { "Node 1"} };
    Node<TestNodeDetails> n2{ 1, { "Node 2"} };
    Node<TestNodeDetails> n3{ 2, { "Node 3"} };
    Node<TestNodeDetails> n4{ 3, { "Node 4"} };
    Node<TestNodeDetails> n5{ 4, { "Node 5"} };

    std::vector<Node<TestNodeDetails>> nodes = {
        n1, n2, n3, n4, n5
    };

    // vector of graph edges
    std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
        {0, 1, 200, { "Kante zwischen 0 und 1" } },
        {0, 2, 201, { "Kante zwischen 0 und 2" } },
        {0, 3, 202, { "Kante zwischen 0 und 3" } },
        {1, 2, 203, { "Kante zwischen 1 und 2" } },
        {1, 3, 204, { "Kante zwischen 1 und 3" } },
        {2, 3, 205, { "Kante zwischen 2 und 3" } },
        {2, 4, 206, { "Kante zwischen 2 und 4" } },
        {3, 4, 207, { "Kante zwischen 3 und 4" } }
    };

    // graph with 5 nodes (vertices)
    GraphAdjMatrix<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> testGraph(Direction::undirected);

    testGraph.addNodes(nodes);
    testGraph.addEdges(edges);

    std::string graph = testGraph.toString();
    std::cout << graph << std::endl;

    std::string nodesDisplay = testGraph.toStringNodes();
    std::cout << nodesDisplay << std::endl;

    std::string edgesDisplay = testGraph.toStringEdges<TestEdgeDetails>();
    std::cout << edgesDisplay << std::endl;
}

int main()
{
    std::cout << "General testing functions for nodes, edges and graphs" << std::endl << std::endl;

    test_01_unweighted_undirected();
    test_01_weighted_directed();
    test_01_unweighted_directed();
    test_01_weighted_undirected();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
