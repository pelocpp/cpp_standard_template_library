// =====================================================================================
// Graph Theory Redesign
// =====================================================================================

#include "GraphNode.h"

using namespace Graph_Theory;

void test_graph_nodes_01()
{
    GraphNode<int> node{1};

    //std::cout << node << std::endl;

    GraphNode<int> node10{10};
    GraphNode<int> node11{11};
    GraphNode<int> node12{12};

    //template<typename Weight>
    //using Edge = std::pair<size_t, std::optional<Weight>>;

    Edge<EmptyType> edge1{ 0, std::nullopt };
    Edge<EmptyType> edge2{ 1, std::nullopt };
    Edge<EmptyType> edge3{ 2, std::nullopt };

    auto& list = node.getAdjacentNodes();

    list.insert(edge1);
    list.insert(edge2);
    list.insert(edge3);

    std::cout << "Stopper" << std::endl;
}

void test_graph_nodes()
{
    test_graph_nodes_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
