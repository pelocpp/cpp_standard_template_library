// =====================================================================================
// Program
// =====================================================================================

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>
#include <iomanip>
#include <tuple>
#include <optional>
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

#include "Solver_BFS_Ex.h"

// BFS test functions
//
void test_BFS_NordAmerika();
void test_BFS_SchaumsOutline();

void test_BFS_NordAmerika()
{
    using namespace Solver_BFS_Ex;

    constexpr int NumNodes = 8;

    // Beispiel "Flugverbindungen in Nordamerika"
    using FlightNode = BaseNode<int, std::string>;

    FlightNode n1{ 0, std::string{ "NewYork"} };
    FlightNode n2{ 1, std::string{ "Chicago"} };
    FlightNode n3{ 2, std::string{ "Toronto"} };
    FlightNode n4{ 3, std::string{ "Denver"} };
    FlightNode n5{ 4, std::string{ "Los Angeles"} };
    FlightNode n6{ 5, std::string{ "Calgary"} };
    FlightNode n7{ 6, std::string{ "Houston"} };
    FlightNode n8{ 7, std::string{ "Urbana"} };

    std::vector<FlightNode> nodes = {
       n1, n2, n3, n4, n5, n6, n7, n8
    };

    // vector of graph edges as per above diagram
    std::vector<BaseEdge<>> edges = {

        { 0, 1 },
        { 0, 2 },
        { 0, 3 },
        { 1, 3 },
        { 2, 4 },
        { 2, 1 },
        { 2, 5 },
        { 3, 4 },
        { 3, 6 },
        { 3, 7 },
        { 6, 4 }
    };

    GraphAdjListEx<BaseEdge<>, NotWeighted, NotDirected> flightGraph{ NumNodes };
    // GraphAdjMatrixEx<BaseEdge<>, NotWeighted, NotDirected> flightGraph{ NumNodes };

    flightGraph.setNodesCount(NumNodes);
    flightGraph.addEdges(edges);

    std::cout << flightGraph.toString() << std::endl;

    BFSSolverEx<BaseEdge<>> bfs;
    bfs.setGraph(&flightGraph);
    std::vector<std::optional<IndexType>> paths = bfs.solve(0);
    std::vector<IndexType> solution = bfs.reconstructPath(0, 4, paths);
    bfs.printSolution(solution);

    //std::for_each(std::begin(solution), std::end(solution) - 1, [&](int id) {
    //    FlightNodeInfo info = getDetails<Node<FlightNodeInfo>, FlightNodeInfo>(nodes[id]);
    //    std::cout << info.getDeparture() << " => ";
    //    }
    //);

    //// print last element without trailing comma :-)
    //IndexType last = solution.back();
    //FlightNodeInfo info = getDetails<Node<FlightNodeInfo>, FlightNodeInfo>(nodes[last]);
    //std::cout << info.getDeparture() << "." << std::endl; 

    std::for_each(std::begin(solution), std::end(solution) - 1, [&](int id) {
        std::string departure = getDetail<FlightNode, 1>(nodes[id]);
        std::cout << departure << " => ";
        }
    );

    // print last element without trailing comma :-)
    IndexType last = solution.back();
    std::string departure = getDetail<FlightNode, 1>(nodes[last]);
    std::cout << departure << ".";
}

void test_BFS_SchaumsOutline() {

    using namespace Solver_BFS_Ex;

    constexpr int NumNodes = 9;

    // Beispiel aus "Schaums Outline": Graph mit 9 nodes Knoten

    using Node = BaseNode<int, std::string>;

    std::vector<Node> nodes = {
        { 0, std::string{ "Node 1"} },
        { 1, std::string{ "Node 2"} },
        { 2, std::string{ "Node 3"} },
        { 3, std::string{ "Node 4"} },
        { 4, std::string{ "Node 5"} },
        { 5, std::string{ "Node 6"} },
        { 6, std::string{ "Node 7"} },
        { 7, std::string{ "Node 8"} },
        { 8, std::string{ "Node 9"} }
    };

    // GraphAdjMatrixEx<BaseEdge<>, NotWeighted, NotDirected> schaumsGraph{ NumNodes };
    GraphAdjListEx<BaseEdge<>, NotWeighted, NotDirected> schaumsGraph(NumNodes);

    schaumsGraph.setNodesCount(NumNodes);

    // vector of edges
    std::vector<BaseEdge<>> edges = {
        { 0, 1 },
        { 0, 2 },
        { 0, 5 },
        { 1, 2 },
        { 1, 6 },
        { 2, 5 },
        { 3, 2 },
        { 4, 2 },
        { 4, 3 },
        { 4, 7 },
        { 5, 3 },
        { 6, 2 },
        { 6, 4 },
        { 7, 3 },
        { 7, 8 },
        { 8, 4 },
        { 8, 6 }
    };
    schaumsGraph.addEdges(edges);

    std::cout << "Nodes: " << schaumsGraph.countNodes() << ", Edges: " << schaumsGraph.countEdges() << std::endl;
    std::cout << schaumsGraph.toString() << std::endl;

    std::cout << schaumsGraph.toString() << std::endl;

    BFSSolverEx<BaseEdge<>> bfs;
    bfs.setGraph(&schaumsGraph);

    std::vector<std::optional<IndexType>> paths = bfs.solve(0);
    std::vector<IndexType> solution = bfs.reconstructPath(0, 7, paths);

    bfs.printSolution(solution);
}

int main() {

    test_BFS_NordAmerika();
    test_BFS_SchaumsOutline();
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
