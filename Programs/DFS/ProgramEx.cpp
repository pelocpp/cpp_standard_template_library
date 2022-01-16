// =====================================================================================
// Program DFS
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
#include "../Include/NodeEx.h"
#include "../Include/EdgeEx.h"

#include "../Include/GraphInterfaceEx.h"
#include "../Include/GraphAdjListEx.h"
#include "../Include/GraphAdjMatEx.h"

#include "Solver_DFS_Ex.h"


// PeLo: Hmmm, ist das eine zentrale Stelle ???
using MyNodeType = BaseNode<int, std::string>;
//
//auto my_make_edge(int id, std::string text) -> MyNodeType {
//    return make_node<int, std::string>(id, text);
//};

void test_DFS_01()
{
    using namespace Solver_DFS_Ex;

    constexpr int NumNodes = 8;

    MyNodeType node1{ 0, "Node 1" };
    MyNodeType node2{ 1, "Node 2" };
    MyNodeType node3{ 2, "Node 3" };
    MyNodeType node4{ 3, "Node 4" };
    MyNodeType node5{ 4, "Node 5" };
    MyNodeType node6{ 5, "Node 6" };
    MyNodeType node7{ 7, "Node 7" };
    MyNodeType node8{ 7, "Node 8" };

    std::vector<MyNodeType> nodes = {
        node1, node2, node3, node4, node5, node6, node7, node8
    };

    // vector of graph edges as per above diagram
    std::vector<BaseEdge<>> edges = {
        {0, 3 },
        {1, 0}, {1, 2}, {1, 4},
        {2, 7},
        {3, 4}, {3, 5},
        {4, 3}, {4, 6},
        {5, 6},
        {6, 7}
    };

    // graph with 8 nodes (vertices)
    //GraphAdjListEx<BaseEdge<>, NotWeighted, NotDirected> graph(NumNodes);
    GraphAdjMatrixEx<BaseEdge<>, NotWeighted, NotDirected> graph(NumNodes);
    graph.addEdges(edges);

    std::string graphDisplay = graph.toString();
    std::cout << graphDisplay << std::endl;

    DFSSolverEx<BaseEdge<>> dfs;
    dfs.setGraph(&graph);

    constexpr int Source = 1;
    constexpr int Target = 6;

    if (std::vector<IndexType> resultPath; dfs.findPathAny(Source, Target, resultPath))
    {
        std::cout << "Path exists from vertex " << Source << " to vertex " << Target << std::endl;
        std::cout << "The complete path is: ";
        dfs.printPath(resultPath);
    }
    else {
        std::cout << "No path exists between vertices " << Source << " and " << Target;
    }
}


void test_DFS_02()
{
    using namespace Solver_DFS_Ex;

    constexpr int NumNodes = 8;

    // vector of graph edges as per above diagram
    std::vector<BaseEdge<>> edges = {
        {0, 3 },
        {1, 0 }, {1, 2 }, {1, 4 },
        {2, 7 },
        {3, 4 }, {3, 5 },
        {4, 3 }, {4, 6 },
        {5, 6 },
        {6, 7 }
    };

    // graph with 8 nodes (vertices)
    //GraphAdjListEx<BaseEdge<>, NotWeighted, Directed> graph(NumNodes);
    GraphAdjMatrixEx<BaseEdge<>, NotWeighted, Directed> graph(NumNodes);
    graph.addEdges(edges);

    std::cout << "Node:       " << graph.countNodes() << std::endl;
    std::cout << "Edges:      " << graph.countEdges() << std::endl;
    std::cout << "IsDirected: " << graph.isDirected() << std::endl;
    std::cout << "IsWeighted: " << graph.isWeighted() << std::endl;

    DFSSolverEx<BaseEdge<>> dfs;
    dfs.setGraph(&graph);

    constexpr int Source = 1;
    constexpr int Target = 6;

    dfs.findPathAll(Source, Target);

    if (int count; count = dfs.countFoundPaths())
    {
        std::cout << "Found " << count << " solutions:" << std::endl;
        dfs.printPaths();
    }
    else {
        std::cout << "No path exists between vertices " << Source << " and " << Target;
    }
}

// DFS test functions
//
void test_DFS_01();
void test_DFS_02();

int main() {
    test_DFS_01();
    test_DFS_02();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
