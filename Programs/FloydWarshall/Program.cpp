// =====================================================================================
// Program
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
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
#include "../Include/GraphAdjMat.h"

#include "Solver_FloydWarshall.h"

// General testing functions
//
void test_01()
{
    // =====================================================
    // Beispiel Graph: https://www.programiz.com/dsa/floyd-warshall-algorithm

    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;
    using namespace SolverFloydWarshall;

    Node<TestNodeDetails> n1{ 0, { "Node 1"} };
    Node<TestNodeDetails> n2{ 1, { "Node 2"} };
    Node<TestNodeDetails> n3{ 2, { "Node 3"} };
    Node<TestNodeDetails> n4{ 3, { "Node 4"} };

    std::vector<Node<TestNodeDetails>> nodes = {
        n1, n2, n3, n4
    };

    // vector of graph edges
    std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
        {0, 1, 3, { "Von 1 nach 2" } },
        {1, 0, 2, { "Von 2 nach 1" } },
        {0, 3, 5, { "Von 1 nach 4" } },
        {1, 3, 4, { "Von 2 nach 4" } },
        {2, 1, 1, { "Von 3 nach 2" } },
        {3, 2, 2, { "Von 4 nach 3" } }
    };

    GraphAdjMatrix<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(Direction::directed);

    graph.addNodes(nodes);
    graph.addEdges(edges);

    std::string graphDisplay = graph.toString();
    std::cout << graphDisplay << std::endl;

    std::string nodesDisplay = graph.toStringNodes();
    std::cout << nodesDisplay << std::endl;

    std::string edgesDisplay = graph.toStringEdges<TestEdgeDetails>();
    std::cout << edgesDisplay << std::endl;

    // create solver
    FloydWarshallSolver<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> fw;
    fw.setGraph(&graph);
    fw.solve();
    //fw.print();
}


int main()
{
    std::cout << "Floyd-Warshall Algorithm: Test Graph" << std::endl << std::endl;

    test_01();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
