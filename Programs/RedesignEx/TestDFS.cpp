#include "Graph.h"

namespace Graph_Theory_DFS
{
    using namespace Graph_Theory_Redesign;

    void test_20()
    {
        std::cout << "Redesign Graph Theory - DFS" << std::endl;

        Graph<int> graph;

        graph.addNodes({ 0, 1, 2, 3, 4, 5, 6, 7 });

        graph.addEdge(0, 3);
        graph.addEdge(1, 0);
        graph.addEdge(1, 2);
        graph.addEdge(1, 4);
        graph.addEdge(2, 7);
        graph.addEdge(3, 4);
        graph.addEdge(3, 5);
        graph.addEdge(4, 3);
        graph.addEdge(4, 6);
        graph.addEdge(5, 6);
        graph.addEdge(6, 7);

        std::cout << "Graph " << toString(graph) << std::endl;

        DFSSolver dfs{ graph };

        //constexpr size_t Source{ 1 };
        //constexpr size_t Target{ 6 };

        constexpr size_t Source{ 2 };
        constexpr size_t Target{ 7 };

        if (std::vector<size_t> resultPath; dfs.findPathAny(Source, Target, resultPath))
        {
            std::cout << "Path exists from " << Source << " to " << Target << ":" << std::endl;
            dfs.printPath(resultPath);
        }
        else {
            std::cout << "No path exists between " << Source << " and " << Target << "." << std::endl;
        }

        // -------------

        dfs.findPathAll(Source, Target);

        if (size_t count; (count = dfs.countFoundPaths()) != 0)
        {
            std::cout << "Found " << count << " solutions:" << std::endl;
            dfs.printPaths();
        }
        else {
            std::cout << "No path exists between " << Source << " and " << Target << "." << std::endl;
        }
    }

    void test_22()
    {
        std::cout << "Redesign Graph Theory - DFS - Connected Components" << std::endl;

        Graph<int> graph;

        graph.addNodes({ 0, 3, 6, 7, 11, 4, 8, 13, 14, 1, 5, 17, 16, 9, 15, 2, 10});

        graph.addEdge(0, 3);

        graph.addEdge(6, 7);
        graph.addEdge(6, 11);
        graph.addEdge(7, 11);

        graph.addEdge(0, 4);
        graph.addEdge(0, 8);
        graph.addEdge(0, 13);
        graph.addEdge(0, 14);
        graph.addEdge(4, 8);
        graph.addEdge(8, 14);
        graph.addEdge(13, 14);

        graph.addEdge(1, 5);
        graph.addEdge(5, 17);
        graph.addEdge(5, 16);

        graph.addEdge(3, 9);
        graph.addEdge(9, 15);
        graph.addEdge(2, 15);
        graph.addEdge(2, 9);
        graph.addEdge(10, 15);

        //std::string dot = toDot<int>(graph, "Beispiel");

        //std::cout << dot << std::endl;

        std::cout << "Graph: " << toString(graph) << std::endl;

        //graph.addEdges({

        //    {6, 7},
        //    {6, 11},
        //    {7, 11},

        //    {0, 4},
        //    {0, 8},
        //    {0, 13},
        //    {0, 14},
        //    {4, 8},
        //    {8, 14},
        //    {13, 14},

        //    {1, 5},
        //    {5, 17},
        //    {5, 16},

        //    {3, 9},
        //    {9, 15},
        //    {2, 15},
        //    {2, 9},
        //    {10, 15}
        //    }
        //);


        DFSSolver dfs{ graph };

        dfs.computeComponents();

        size_t count{ dfs.getNumberOfComponents() };

        for (size_t index{}; index != count; ++index) {

            auto component = dfs.getComponent(index + 1);

            for (size_t last{}; size_t vertex : component) {
                std::cout << "[" << vertex << "]";
                if (last < component.size() - 1) {
                    std::cout << ", ";
                }
                ++last;
            }
            std::cout << std::endl;
        }
    }
}

