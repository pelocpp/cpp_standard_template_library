// =====================================================================================
// Program Graphs
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>

#include "../Include/Globals.h"
#include "../Include/NodeEx.h"
#include "../Include/EdgeEx.h"

using Node = BaseNode<int, std::string>;

//auto my_make_edge(int id, std::string text) -> MyNodeType {
//    return make_node<int, std::string>(id, text);
//};

using WeightType = int;
using Edge = BaseEdgeWeighted<WeightType, std::string, std::string>;
using UnweightedEdge = BaseEdge<std::string, int>;

using MinimalWeightedEdge = BaseEdgeWeighted<WeightType>;
using MinimalUnweightedEdge = BaseEdge<>;


void test_01_weighted()
{
    Edge edge{ 0, 1, 10, "von a nach b [10]", "XXL" };
    std::string s = toStringEdge<Edge, true>(edge);
    std::cout << s << std::endl;
}

void test_02_unweighted()
{
    UnweightedEdge edge{ 0, 1, "von a nach b",  1001, };
    std::string s = toStringEdge<UnweightedEdge, false>(edge);
    std::cout << s << std::endl;
}

void test_03_weighted()
{
    MinimalWeightedEdge edge{ 1, 2, 999 };
    std::string s = toStringEdge<MinimalWeightedEdge, true>(edge);
    std::cout << s << std::endl;
}

void test_04_unweighted()
{
    MinimalUnweightedEdge edge{ 1, 2 };
    std::string s = toStringEdge<MinimalUnweightedEdge, false>(edge);
    std::cout << s << std::endl;
}

void test_10_weighted ()
{
    Edge edge1{ 0, 1, 10, "a => b [10]", "XXL" };
    Edge edge2{ 0, 2, 20, "a => c [20]", "S" };
    Edge edge3{ 1, 4, 10, "b => e [10]", "M" };
    Edge edge4{ 1, 3, 50, "b => d [50]", "XL" };
    Edge edge5{ 2, 4, 33, "c => e [33]", "S" };
    Edge edge6{ 2, 3, 20, "c => d [20]", "S" };
    Edge edge7{ 3, 4, 20, "d => e [20]", "L" };
    Edge edge8{ 3, 5,  2, "d => f [ 2]", "XL" };
    Edge edge9{ 4, 5,  1, "e => f [ 1]", "XXL" };

    std::vector<Edge> edges = {
        edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9
    };

    std::string s = toStringEdges<Edge, true>(std::begin(edges), std::end(edges));
    std::cout << s << std::endl;
}

void test_11_unweighted()
{
    UnweightedEdge edge1{ 0, 1, "a => b",  1001, };
    UnweightedEdge edge2{ 0, 2, "a => c",  1002, };
    UnweightedEdge edge3{ 1, 4, "b => e",  1003, };
    UnweightedEdge edge4{ 1, 3, "b => d",  1004, };
    UnweightedEdge edge5{ 2, 4, "c => e",  1005, };
    UnweightedEdge edge6{ 2, 3, "c => d",  1006, };
    UnweightedEdge edge7{ 3, 4, "d => e",  1007, };
    UnweightedEdge edge8{ 3, 5, "d => f",  1008, };
    UnweightedEdge edge9{ 4, 5, "e => f",  1009, };

    std::vector<UnweightedEdge> edges = {
        edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9
    };

    std::string s = toStringEdges<UnweightedEdge, false>(std::begin(edges), std::end(edges));
    std::cout << s << std::endl;
}

void test_12_weighted()
{
    MinimalWeightedEdge edge1{ 0, 1, 10 };
    MinimalWeightedEdge edge2{ 0, 2, 20  };
    MinimalWeightedEdge edge3{ 1, 4, 10  };

    std::vector<MinimalWeightedEdge> edges = {
        edge1, edge2, edge3
    };

    std::string s = toStringEdges<MinimalWeightedEdge, true>(std::begin(edges), std::end(edges));
    std::cout << s << std::endl;
}

void test_13_unweighted()
{
    MinimalUnweightedEdge edge1{ 0, 1 };
    MinimalUnweightedEdge edge2{ 0, 2 };
    MinimalUnweightedEdge edge3{ 1, 4 };
    MinimalUnweightedEdge edge4{ 1, 3 };
    MinimalUnweightedEdge edge5{ 2, 4 };
    MinimalUnweightedEdge edge6{ 2, 3 };
    MinimalUnweightedEdge edge7{ 3, 4 };
    MinimalUnweightedEdge edge8{ 3, 5 };
    MinimalUnweightedEdge edge9{ 4, 5 };

    std::vector<MinimalUnweightedEdge> edges = {
        edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9
    };

    std::string s = toStringEdges<MinimalUnweightedEdge, false>(std::begin(edges), std::end(edges));
    std::cout << s << std::endl;
}

void test_10_nodes()
{
    BaseNode<> node;

    //std::string s = toStringNode<BaseNode<>>(node);
    //std::cout << s << std::endl;
}


void test_11_nodes()
{
    Node n1{ 1, std::string("Node a") };
    Node n2{ 2, std::string("Node b") };
    Node n3{ 3, std::string("Node c") };
    Node n4{ 4, std::string("Node d") };
    Node n5{ 5, std::string("Node e") };
    Node n6{ 6, std::string("Node f") };

    std::vector<Node> nodes = {
        n1, n2, n3, n4, n5, n6
    };

    //std::string s = toStringEdges<Edge, true>(std::begin(edges), std::end(edges));
    //std::cout << s << std::endl;
}

void test_10_nodes()
{
    BaseNode<> n1;
    BaseNode<> n2;
    BaseNode<> n3;
    BaseNode<> n4;
    BaseNode<> n5;
    BaseNode<> n6;

    std::vector<BaseNode<>> nodes = {
        n1, n2, n3, n4, n5, n6
    };

    //std::string s = toStringNodes<BaseNode<>>(std::begin(nodes), std::end(nodes));
    //std::cout << s << std::endl;
}


void test_11_nodes()
{
    Node n1{ 1, std::string("Node a") };
    Node n2{ 2, std::string("Node b") };
    Node n3{ 3, std::string("Node c") };
    Node n4{ 4, std::string("Node d") };
    Node n5{ 5, std::string("Node e") };
    Node n6{ 6, std::string("Node f") };

    std::vector<Node> nodes = {
        n1, n2, n3, n4, n5, n6
    };

    //std::string s = toStringEdges<Edge, true>(std::begin(edges), std::end(edges));
    //std::cout << s << std::endl;
}

































// General testing functions for nodes, edges and graphs
//
//
//void test_01_unweighted_undirected()
//{
//    // =====================================================
//    // Haus des Nikolas: ungerichtet, ungewichtet
//
//    using namespace NodeDetailsTest;
//    using namespace EdgeDetailsTest;
//
//    Node<TestNodeDetails> n1{ 0, { "Node 1"} };
//    Node<TestNodeDetails> n2{ 1, { "Node 2"} };
//    Node<TestNodeDetails> n3{ 2, { "Node 3"} };
//    Node<TestNodeDetails> n4{ 3, { "Node 4"} };
//    Node<TestNodeDetails> n5{ 4, { "Node 5"} };
//
//    std::vector<Node<TestNodeDetails>> nodes = {
//        n1, n2, n3, n4, n5
//    };
//
//    // vector of graph edges (Haus des Nikolas, ungerichtet)
//    std::vector<UnweightedEdge<TestEdgeDetails>> edges = {
//        {0, 1, { "Kante zwischen 0 und 1" } }, 
//        {0, 2, { "Kante zwischen 0 und 2" } }, 
//        {0, 3, { "Kante zwischen 0 und 3" } },
//        {1, 2, { "Kante zwischen 1 und 2" } }, 
//        {1, 3, { "Kante zwischen 1 und 3" } },
//        {2, 3, { "Kante zwischen 2 und 3" } }, 
//        {2, 4, { "Kante zwischen 2 und 4" } },
//        {3, 4, { "Kante zwischen 3 und 4" } }
//    };
//
//    // graph with 5 nodes (vertices)
//    GraphAdjMatrix<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> testGraph(Direction::undirected);
//
//    testGraph.addNodes(nodes);
//    testGraph.addEdges(edges);
//
//    std::string graph = testGraph.toString();
//    std::cout << graph << std::endl;
//
//    std::string nodesDisplay = testGraph.toStringNodes();
//    std::cout << nodesDisplay << std::endl;
//
//    std::string edgesDisplay = testGraph.toStringEdges<TestEdgeDetails>();
//    std::cout << edgesDisplay << std::endl;
//}
//
//void test_01_weighted_directed()
//{
//    // =====================================================
//    // Haus des Nikolas: gerichtet, gewichtet
//
//    using namespace NodeDetailsTest;
//    using namespace EdgeDetailsTest;
//
//    Node<TestNodeDetails> n1{ 0, { "Node 1"} };
//    Node<TestNodeDetails> n2{ 1, { "Node 2"} };
//    Node<TestNodeDetails> n3{ 2, { "Node 3"} };
//    Node<TestNodeDetails> n4{ 3, { "Node 4"} };
//    Node<TestNodeDetails> n5{ 4, { "Node 5"} };
//
//    std::vector<Node<TestNodeDetails>> nodes = {
//        n1, n2, n3, n4, n5
//    };
//
//    // vector of graph edges
//    std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
//        {0, 1, 100, { "Kante zwischen 0 und 1" } },
//        {0, 2, 101, { "Kante zwischen 0 und 2" } },
//        {0, 3, 102, { "Kante zwischen 0 und 3" } },
//        {1, 2, 103, { "Kante zwischen 1 und 2" } },
//        {1, 3, 104, { "Kante zwischen 1 und 3" } },
//        {2, 3, 105, { "Kante zwischen 2 und 3" } },
//        {2, 4, 106, { "Kante zwischen 2 und 4" } },
//        {3, 4, 107, { "Kante zwischen 3 und 4" } }
//    };
//
//    // graph with 5 nodes (vertices)
//    GraphAdjMatrix<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> testGraph(Direction::directed);
//
//    testGraph.addNodes(nodes);
//    testGraph.addEdges(edges);
//
//    std::string graph = testGraph.toString();
//    std::cout << graph << std::endl;
//
//    std::string nodesDisplay = testGraph.toStringNodes();
//    std::cout << nodesDisplay << std::endl;
//
//    std::string edgesDisplay = testGraph.toStringEdges<TestEdgeDetails>();
//    std::cout << edgesDisplay << std::endl;
//}
//
//
//void test_01_unweighted_directed()
//{
//    // =====================================================
//    // Haus des Nikolas: gerichtet, ungewichtet
//
//    using namespace NodeDetailsTest;
//    using namespace EdgeDetailsTest;
//
//    Node<TestNodeDetails> n1{ 0, { "Node 1"} };
//    Node<TestNodeDetails> n2{ 1, { "Node 2"} };
//    Node<TestNodeDetails> n3{ 2, { "Node 3"} };
//    Node<TestNodeDetails> n4{ 3, { "Node 4"} };
//    Node<TestNodeDetails> n5{ 4, { "Node 5"} };
//
//    std::vector<Node<TestNodeDetails>> nodes = {
//        n1, n2, n3, n4, n5
//    };
//
//    // vector of graph edges (Haus des Nikolas, ungerichtet)
//    std::vector<UnweightedEdge<TestEdgeDetails>> edges = {
//        {0, 1, { "Kante zwischen 0 und 1" } },
//        {0, 2, { "Kante zwischen 0 und 2" } },
//        {0, 3, { "Kante zwischen 0 und 3" } },
//        {1, 2, { "Kante zwischen 1 und 2" } },
//        {1, 3, { "Kante zwischen 1 und 3" } },
//        {2, 3, { "Kante zwischen 2 und 3" } },
//        {2, 4, { "Kante zwischen 2 und 4" } },
//        {3, 4, { "Kante zwischen 3 und 4" } }
//    };
//
//    // graph with 5 nodes (vertices)
//    GraphAdjMatrix<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> testGraph(Direction::directed);
//
//    testGraph.addNodes(nodes);
//    testGraph.addEdges(edges);
//
//    std::string graph = testGraph.toString();
//    std::cout << graph << std::endl;
//
//    std::string nodesDisplay = testGraph.toStringNodes();
//    std::cout << nodesDisplay << std::endl;
//
//    std::string edgesDisplay = testGraph.toStringEdges<TestEdgeDetails>();
//    std::cout << edgesDisplay << std::endl;
//}
//
//void test_01_weighted_undirected()
//{
//    // =====================================================
//    // Haus des Nikolas: gerichtet, gewichtet
//
//    using namespace NodeDetailsTest;
//    using namespace EdgeDetailsTest;
//
//    Node<TestNodeDetails> n1{ 0, { "Node 1"} };
//    Node<TestNodeDetails> n2{ 1, { "Node 2"} };
//    Node<TestNodeDetails> n3{ 2, { "Node 3"} };
//    Node<TestNodeDetails> n4{ 3, { "Node 4"} };
//    Node<TestNodeDetails> n5{ 4, { "Node 5"} };
//
//    std::vector<Node<TestNodeDetails>> nodes = {
//        n1, n2, n3, n4, n5
//    };
//
//    // vector of graph edges
//    std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
//        {0, 1, 200, { "Kante zwischen 0 und 1" } },
//        {0, 2, 201, { "Kante zwischen 0 und 2" } },
//        {0, 3, 202, { "Kante zwischen 0 und 3" } },
//        {1, 2, 203, { "Kante zwischen 1 und 2" } },
//        {1, 3, 204, { "Kante zwischen 1 und 3" } },
//        {2, 3, 205, { "Kante zwischen 2 und 3" } },
//        {2, 4, 206, { "Kante zwischen 2 und 4" } },
//        {3, 4, 207, { "Kante zwischen 3 und 4" } }
//    };
//
//    // graph with 5 nodes (vertices)
//    GraphAdjMatrix<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> testGraph(Direction::undirected);
//
//    testGraph.addNodes(nodes);
//    testGraph.addEdges(edges);
//
//    std::string graph = testGraph.toString();
//    std::cout << graph << std::endl;
//
//    std::string nodesDisplay = testGraph.toStringNodes();
//    std::cout << nodesDisplay << std::endl;
//
//    std::string edgesDisplay = testGraph.toStringEdges<TestEdgeDetails>();
//    std::cout << edgesDisplay << std::endl;
//}

int main()
{
    std::cout << "General testing functions for nodes, edges and graphs" << std::endl << std::endl;

    //test_01_weighted();
    //test_02_unweighted();
    //test_03_weighted();
    //test_04_unweighted();

    //test_10_weighted();
    //test_11_unweighted();
    //test_12_weighted();
    //test_13_unweighted();

    test_10_nodes();
    //test_11_nodes();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
