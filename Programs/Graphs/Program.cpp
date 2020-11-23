// =====================================================================================
// Program
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
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
// #include "../Include/GraphAdjList.h"
#include "../Include/GraphAdjMat.h"

// General testing functions for nodes, edges and graphs
//

void test_01()
{
    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    Node<TestNodeDetails> n1{ 0, {0, "1"} };
    Node<TestNodeDetails> n2{ 1, {1, "2"} };
    Node<TestNodeDetails> n3{ 2, {2, "3"} };
    Node<TestNodeDetails> n4{ 3, {3, "4"} };
    Node<TestNodeDetails> n5{ 4, {4, "5"} };

    std::vector<Node<TestNodeDetails>> nodes = {
        n1, n2, n3, n4, n5
    };

    // vector of graph edges (Haus des Nikolas, ungerichtet)
    std::vector<UnweightedEdge<TestEdgeDetails>> edges = {
        {0, 1, {} }, {0, 2, {} }, {0, 3, {} },
        {1, 2, {} }, {1, 3, {} },
        {2, 3, {} }, {2, 4, {} },
        {3, 4, {} }
    };

    // graph with 5 nodes (vertices)
    GraphAdjMatrix<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> testGraph(false);

    testGraph.addNodes(nodes);
    testGraph.addEdges(edges);

    std::string graph = testGraph.toString();
    std::cout << graph << std::endl;
}


int main()
{
    std::cout << "General testing functions for nodes, edges and graphs" << std::endl;

    test_01();
    return 0;
}


// =====================================================================================
// End-of-File
// =====================================================================================
