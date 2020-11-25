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
#include "../Include/Node.h"
#include "../Include/NodeDetails.h"
#include "../Include/Edge.h"
#include "../Include/EdgeDetails.h"

#include "../Include/GraphInterface.h"
#include "../Include/GraphAdjMat.h"

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

    XXX a;

    int dummy = 99;

    //using namespace NodeDetailsTest;
    //using namespace EdgeDetailsTest;

    //Node<TestNodeDetails> n1{ 0, { "Node 1"} };
    //Node<TestNodeDetails> n2{ 1, { "Node 2"} };
    //Node<TestNodeDetails> n3{ 2, { "Node 3"} };
    //Node<TestNodeDetails> n4{ 3, { "Node 4"} };

    //std::vector<Node<TestNodeDetails>> nodes = {
    //    n1, n2, n3, n4
    //};

    //// vector of graph edges
    //std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
    //    {0, 1, 3, { "Von 1 nach 2" } },
    //    {1, 0, 2, { "Von 2 nach 1" } },
    //    {0, 3, 5, { "Von 1 nach 4" } },
    //    {1, 3, 4, { "Von 2 nach 4" } },
    //    {2, 1, 1, { "Von 3 nach 2" } },
    //    {3, 2, 2, { "Von 4 nach 3" } }
    //};

    //GraphAdjMatrix<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(Direction::directed);

    //graph.addNodes(nodes);
    //graph.addEdges(edges);

    //std::string graphDisplay = graph.toString();
    //std::cout << graphDisplay << std::endl;

    //std::string nodesDisplay = graph.toStringNodes();
    //std::cout << nodesDisplay << std::endl;

    //std::string edgesDisplay = graph.toStringEdges<TestEdgeDetails>();
    //std::cout << edgesDisplay << std::endl;

}

int main()
{
    std::cout << "Floyd-Warshall Algorithm: Test Graph" << std::endl;

    test_01_experimental();

    return 0;
}

// =====================================================================================
// End-of-File
// =====================================================================================
