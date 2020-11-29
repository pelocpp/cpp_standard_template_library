// =====================================================================================
// Program
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../Include/Globals.h"
#include "../Include/NodeEx.h"
#include "../Include/EdgeEx.h"

#include "../Include/GraphInterfaceEx.h"
#include "../Include/GraphAdjListEx.h"
#include "../Include/GraphAdjMatEx.h"

#include "Solver_Kruskal_Ex.h"

// Kruskal test functions
//
void testPeLo01_Kruskal_Programiz();
void testPeLo01_Kruskal_TUM();

using NodeType = BaseNode<int, std::string>;
using EdgeType = BaseEdgeWeighted<int, std::string>;

// https://www.programiz.com
void testPeLo01_Kruskal_Programiz()
{
    using namespace Solver_Kruskal_Ex;

    constexpr int NumNodes = 6;

    NodeType n1{ 0, std::string("Node a") };
    NodeType n2{ 1, std::string("Node b") };
    NodeType n3{ 2, std::string("Node c") };
    NodeType n4{ 3, std::string("Node d") };
    NodeType n5{ 4, std::string("Node e") };
    NodeType n6{ 5, std::string("Node f") };

    EdgeType we1{ 0, 1, 4, "" };
    EdgeType we2{ 0, 2, 4, "" };
    EdgeType we3{ 1, 2, 2, "" };
    EdgeType we4{ 2, 3, 3, "" };
    EdgeType we5{ 2, 5, 2, "" };
    EdgeType we6{ 2, 4, 4, "" };
    EdgeType we7{ 3, 4, 3, "" };
    EdgeType we8{ 5, 4, 3, "" };

    std::vector<NodeType> nodes = {
        n1, n2, n3, n4, n5, n6
    };

    std::vector<EdgeType> edges = {
        we1, we2, we3, we4, we5, we6, we7, we8
    };

    // create graph
    GraphAdjListEx<EdgeType, Weighted> graph(NotDirected);
    // GraphAdjMatrixEx<EdgeType, Weighted> graph(NotDirected);

    graph.setNodesCount(NumNodes);
    graph.addEdges(edges);
    std::cout << graph.toString() << std::endl;

    // create solver
    KruskalSolverEx<EdgeType> kruskal;
    kruskal.setGraph(&graph);
    kruskal.solve();
    kruskal.printMST();
}

void testPeLo01_Kruskal_TUM()
{
    using namespace Solver_Kruskal_Ex;

    constexpr int NumNodes = 8;

    // create graph
    GraphAdjListEx<EdgeType, Weighted> graph(NotDirected);
    // GraphAdjMatrixEx<EdgeType, Weighted> graph(NotDirected);

    graph.setNodesCount(NumNodes);

    std::vector<EdgeType> edges = {
        { 1, 5, 11, "" },
        { 1, 2, 9, "" },
        { 1, 6, 10, "" },
        { 1, 7, 13, "" },
        { 1, 0, 5, "" },
        { 1, 4, 14, "" },
        { 5, 1, 11, "" },
        { 5, 4, 3, "" },
        { 5, 6, 2, "" },
        { 5, 2, 7, "" },
        { 2, 5, 7, "" },
        { 2, 1, 9, "" },
        { 2, 3, 12, "" },
        { 2, 6, 8, "" },
        { 6, 2, 8, "" },
        { 6, 5, 2, "" },
        { 6, 7, 4, "" },
        { 6, 3, 17, "" },
        { 3, 6, 17, "" },
        { 3, 2, 12, "" },
        { 3, 0, 6, "" },
        { 3, 7, 16, "" },
        { 7, 3, 16, "" },
        { 7, 6, 4, "" },
        { 7, 4, 1, "" },
        { 7, 0, 18, "" },
        { 0, 4, 15, "" },
        { 0, 1, 5, "" },
        { 0, 3, 6, "" },
        { 0, 7, 18, "" },
        { 4, 1, 14, "" },
        { 4, 5, 3, "" },
        { 4, 7, 1, "" },
        { 4, 0, 15, ""}
    };

    graph.addEdges(edges);
    std::cout << graph.toString() << std::endl;

    // create solver
    KruskalSolverEx<EdgeType> kruskal;
    kruskal.setGraph(&graph);
    kruskal.solve();
    kruskal.printMST();
}

int main() {

   //testPeLo01_Kruskal_Programiz();
    testPeLo01_Kruskal_TUM();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
