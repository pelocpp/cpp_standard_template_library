// =====================================================================================
// Graph Theory Redesign // Test_DFS_Connected_Components.cpp
// =====================================================================================

#include "Graph.h"
#include "Solver_DFS.h"

using namespace Graph_Theory;
using namespace Graph_Theory_DFS;

void test_dfs_connected_components_01()
{
    // Siehe Bild im Markdown - das Beispiel funkioniert !!!

    std::cout << "Redesign Graph Theory - DFS - Connected Components" << std::endl;

    Graph<size_t> graph { Direction::Undirected };

    graph.addNodes({ 0, 4, 8, 13, 14, 1, 5, 16, 17, 2, 3, 9, 10, 15, 6, 7, 11, 12 });

    graph.addEdges(
        {
            {  6,  7 },
            {  6, 11 },
            {  7, 11 },

            {  0,  4 },
            {  0,  8 },
            {  0, 13 },
            {  0, 14 },
            {  4,  8 },
            {  8, 14 },
            { 13, 14 },

            {  1,  5 },
            {  5, 17 },
            {  5, 16 },

            {  3,  9 },
            {  9, 15 },
            {  2, 15 },
            {  2,  9 },
            { 10, 15 }
        }
    );

    std::cout << "Graph " << graph.toString() << std::endl;

    DFSSolver dfs{ graph };
    dfs.computeComponents();
    size_t count{ dfs.getNumberOfComponents() };

    for (size_t index{}; index != count; ++index) {

        auto component = dfs.getComponent(index + 1);

        for (size_t index{}; index != count; ++index) {

            auto component = dfs.getComponent(index + 1);

            for (size_t last{}; size_t vertex : component) {

                size_t data = graph.getDataFromNode(vertex);
                std::cout << "[" << data << "]";

                if (last < component.size() - 1) {
                    std::cout << ", ";
                }

                ++last;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void test_dfs_connected_components()
{
    test_dfs_connected_components_01();
}

// =====================================================================================
// End-of-File
// =====================================================================================
