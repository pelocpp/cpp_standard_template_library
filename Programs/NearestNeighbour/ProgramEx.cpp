// =====================================================================================
// NearestNeighbour
// =====================================================================================

// PELo tooo much
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

#include "Solver_NearestNeighbour_Ex.h"

// Nearest Neighbour test functions
//
void test_01_NearestNeighbour_NFE();
void test_01_NearestNeighbour_Fuenf_Staedte();
void test_01_NearestNeighbour_TSP(std::string filename);

// Example from Uni Heidelberg
const std::string tspFileName01 = "Danztig.tsp";

// Example from
// https://www.sanfoundry.com/java-program-implement-traveling-salesman-problem-using-nearest-neighbour-algorithm/
const std::string tspFileName02 = "SanFoundry.tsp";

using Node = BaseNode<int, std::string>;

void test_01_NearestNeighbour_NFE()
{
    using namespace Solver_NearestNeighbour_Ex;

    Node n1{ 0, std::string{"Nbg" } };
    Node n2{ 1, std::string{"Fth" } };
    Node n3{ 2, std::string{"Erl" } };

    BaseEdgeWeighted<int> we1{ 0, 1, 10 };
    BaseEdgeWeighted<int> we2{ 0, 2, 20 };

    BaseEdgeWeighted<int> we3{ 1, 2, 25 };
    BaseEdgeWeighted<int> we4{ 1, 0, 10 };

    BaseEdgeWeighted<int> we5{ 2, 0, 20 };
    BaseEdgeWeighted<int> we6{ 2, 1, 25 };

    std::vector<Node> nodes = {
        n1, n2, n3
    };

    std::vector<BaseEdgeWeighted<int>> edges = {
        we1, we2, we3, we4, we5, we6
    };

    // create graph
    // TODO PeLo: Ist dieser Graph gerichtet oder nicht ?????????????????????
    GraphAdjListEx<BaseEdgeWeighted<int>, Weighted> graph(true);
    graph.setNodesCount(3);
    graph.addEdges(edges);

    // create solver
    NearestNeighbourSolverEx<BaseEdgeWeighted<int>> nn;
    nn.setGraph(&graph);
    nn.solve(0);     // getId(n1)  PeLo das liest sich so auch nicht schlecht .......
    nn.print();
}

void test_01_NearestNeighbour_Fuenf_Staedte()
{
    using namespace Solver_NearestNeighbour_Ex;

    using Edge = BaseEdgeWeighted<int, std::string>;

    Node n1{ 0, { std::string("Nuernberg")} };
    Node n2{ 1, { std::string("Fuerth")} };
    Node n3{ 2, { std::string("Erlangen")} };
    Node n4{ 3, { std::string("Schwaig")} };
    Node n5{ 4, { std::string("Schwabach")} };

    Edge we1{ 0, 1, 10, " bla " };
    Edge we2{ 0, 2, 23, " bla " };
    Edge we3{ 0, 3,  5, " bla " };
    Edge we4{ 0, 4, 20, " bla " };

    Edge we5{ 1, 0, 10, " blubber " };
    Edge we6{ 1, 2, 15, " blubber " };
    Edge we7{ 1, 3, 35, " blubber " };
    Edge we8{ 1, 4, 18, " blubber " };

    Edge we9{ 2, 0, 23,  " bla " };
    Edge we10{ 2, 1, 15, " bla " };
    Edge we11{ 2, 3, 25, " bla " };
    Edge we12{ 2, 4, 40, " bla " };

    Edge we13{ 3, 0, 5,  " blubber " };
    Edge we14{ 3, 1, 35, " blubber " };
    Edge we15{ 3, 2, 25, " blubber " };
    Edge we16{ 3, 4, 30, " blubber " };

    Edge we17{ 4, 0, 20, " bla " };
    Edge we18{ 4, 1, 18, " bla " };
    Edge we19{ 4, 2, 40, " bla " };
    Edge we20{ 4, 3, 30, " bla " };

    std::vector<Node> nodes = {
    n1, n2, n3, n4, n5
    };

    std::vector<Edge> edges = {
        we1, we2, we3, we4, we5, we6, we7, we8,we9,we10,we11,
        we12,we13,we14,we15,we16,we17,we18,we19,we20
    };

    // create graph
    GraphAdjListEx<Edge, Weighted> graph(true);
    graph.setNodesCount(5);
    graph.addEdges(edges);

    // print graph with details
    std::cout << "Graph: " << std::endl;
    std::cout << graph.toString() << std::endl;
    std::cout << "Nodes: " << std::endl;

    // TODO PeLo: toStringNodes hier sollte eine generische Implementierung machbar sein !!!!
    //std::cout << graph.toStringNodes<TestNodeDetails, TestEdgeDetails>() << std::endl;
    //std::cout << "Edges: " << std::endl;
    //std::cout << graph.toStringEdges<TestNodeDetails, TestEdgeDetails>() << std::endl;

    // create solver
    NearestNeighbourSolverEx<Edge> mfr;
    mfr.setGraph(&graph);
    mfr.solve(0);      // getId(n1)  PeLo das liest sich so auch nicht schlecht .......
    mfr.print();
}


// PeLo Still to be done !!!!

//void test_01_NearestNeighbour_TSP(std::string filename)
//{
//    using namespace Solver_NearestNeighbour_Ex;
//
//    // create graph
//    GraphAdjList<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(Direction::directed);
//    bool ok = graph.readTSPFile<TestNodeDetails, TestEdgeDetails>(filename);
//    if (!ok)
//        return;
//
//    std::cout << "Graph from TSP file: " << filename << std::endl;
//
//    // create solver
//    NearestNeighbourSolver<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> nn;
//    nn.setGraph(&graph);
//    nn.solve(1);
//    std::cout << std::endl;
//
//    std::cout << "Found solution: Tour has length of " << nn.total() << std::endl;
//    std::cout << std::endl;
//    nn.print();
//    std::cout << std::endl;
//}




int main() {

    test_01_NearestNeighbour_NFE();
    test_01_NearestNeighbour_Fuenf_Staedte();
    test_01_NearestNeighbour_TSP(tspFileName01);
    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
