// =====================================================================================
// Program
// =====================================================================================

// PeLo hier ausmisten
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <cassert>

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../Include/Globals.h"
#include "../Include/NodeEx.h"
#include "../Include/EdgeEx.h"

#include "../Include/GraphInterfaceEx.h"
#include "../Include/GraphAdjListEx.h"
#include "../Include/GraphAdjMatEx.h"

#include "Solver_FloydWarshallEx.h"

using NodeType = BaseNode<int, std::string>;
using EdgeType = BaseEdgeWeighted<int, std::string>;

// General testing functions
//
void test_01()
{
    // =====================================================
    // Beispiel Graph: https://www.programiz.com/dsa/floyd-warshall-algorithm

    using namespace SolverFloydWarshallEx;

    constexpr int NumNodes = 4;

    NodeType node1{ 0, "Node 1" };
    NodeType node2{ 1, "Node 2" };
    NodeType node3{ 2, "Node 3" };
    NodeType node4{ 3, "Node 4" };

    std::vector<NodeType> nodes = {
        node1, node2, node3, node4
    };

    // vector of graph edges
    std::vector<EdgeType> edges = {
        {0, 1, 3, { "Von 1 nach 2" } },
        {1, 0, 2, { "Von 2 nach 1" } },
        {0, 3, 5, { "Von 1 nach 4" } },
        {1, 3, 4, { "Von 2 nach 4" } },
        {2, 1, 1, { "Von 3 nach 2" } },
        {3, 2, 2, { "Von 4 nach 3" } }
    };

    // GraphAdjMatrixEx<EdgeType, Weighted, Directed> graph(NumNodes);
    GraphAdjListEx<EdgeType, Weighted, Directed> graph(NumNodes);
    graph.addEdges(edges);

    std::string graphDisplay = graph.toString();
    std::cout << graphDisplay << std::endl;

    //std::string nodesDisplay = graph.toStringNodes();
    //std::cout << nodesDisplay << std::endl;

    //std::string edgesDisplay = graph.toStringEdges<TestEdgeDetails>();
    //std::cout << edgesDisplay << std::endl;

    // create solver
    FloydWarshallSolverEx<EdgeType> fw;
    fw.setGraph(&graph);
    fw.solve();
    fw.printPath(1, 2);
    fw.printPath(3, 0);
}

int main()
{
    std::cout << "Floyd-Warshall Algorithm: Test Graph" << std::endl;
    test_01();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
