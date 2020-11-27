// =====================================================================================
// Program // Experimental
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
#include "../Include/NodeEx.h"
#include "../Include/EdgeEx.h"

#include "../Include/GraphInterfaceEx.h"
#include "../Include/GraphAdjMatEx.h"

#include "Solver_Experimental.h"

using MyEdgeType = BaseEdge<std::string, double>;

auto my_make_edge(IndexType source, IndexType target, std::string s , double d) -> MyEdgeType {
    return make_edge<std::string, double> (source, target, s, d );
}

// General testing functions
//
void test_01_experimental ()
{
    auto edge1 = make_edge(10, 22, "sdasda", 22.22);

    MyEdgeType edge2 { 1, 2 , "sdasda", 22.22 };

    MyEdgeType edge3 = make_edge<std::string, double >(10, 22, "sdasda", 22.22 );

    MyEdgeType edge4 = my_make_edge(10, 22, "sdasda", 22.22);

    using XXX = MyEdge1<std::string, double>;
}


void test_02_experimental()
{
    using namespace SolverFloydWarshallEx;

    constexpr int NumNodes = 4;

    using TestEdgeType = BaseEdgeWeighted<int, std::string>;

    TestEdgeType edge1 { 0, 1, 3, std::string { "Von 1 nach 2" } };
    TestEdgeType edge2 { 1, 0, 2, std::string { "Von 2 nach 1" } };
    TestEdgeType edge3 { 0, 3, 5, std::string { "Von 1 nach 4" } };
    TestEdgeType edge4 { 1, 3, 4, std::string { "Von 2 nach 4" } };
    TestEdgeType edge5 { 2, 1, 1, std::string { "Von 3 nach 2" } };
    TestEdgeType edge6 { 3, 2, 2, std::string { "Von 4 nach 3" } };

    // vector of graph edges
    std::vector<TestEdgeType> edges = {
        edge1,
        edge2,
        edge3,
        edge4,
        edge5,
        edge6,
    };

    // or

    std::vector<TestEdgeType> edges2 = {
        { 0, 1, 3, std::string { "Von 1 nach 2" } },
        { 1, 0, 2, std::string { "Von 2 nach 1" } },
        { 0, 3, 5, std::string { "Von 1 nach 4" } },
        { 1, 3, 4, std::string { "Von 2 nach 4" } },
        { 2, 1, 1, std::string { "Von 3 nach 2" } },
        { 3, 2, 2, std::string { "Von 4 nach 3" } }
    };

    GraphAdjMatrixEx<TestEdgeType> graph(Directed, Weighted);

    graph.setNodesCount(NumNodes);
    graph.addEdges(edges);

    std::string graphDisplay = graph.toString();
    std::cout << graphDisplay << std::endl;

    //std::string nodesDisplay = graph.toStringNodes();
    //std::cout << nodesDisplay << std::endl;

    //std::string edgesDisplay = graph.toStringEdges<TestEdgeDetails>();
    //std::cout << edgesDisplay << std::endl;

    // create solver
    FloydWarshallSolverEx<TestEdgeType> fw;
    fw.setGraph(&graph);
    fw.solve();
    fw.printPath(1, 2);
    fw.printPath(3, 0);

}

int main()
{
    std::cout << "Floyd-Warshall Algorithm - Experimental Version: Test Graph" << std::endl;

    // test_01_experimental();
    test_02_experimental();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
