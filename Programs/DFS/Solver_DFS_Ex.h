#pragma once

// =====================================================================================
// Solver_DFS
// =====================================================================================

namespace Solver_DFS_Ex {

    template <typename EDGE>
    class DFSSolverEx {
    private:
        const IGraphEx<EDGE>* m_graph;
        std::vector<bool> m_visited;
        std::deque<std::vector<IndexType>> m_paths;

    public:
        // c'tor
        DFSSolverEx() : m_graph(nullptr) {}

        // public interface
        void setGraph(const IGraphEx<EDGE>*);
        bool findPathAny(IndexType source, IndexType target, std::vector<IndexType>& path);
        void findPathAll(IndexType source, IndexType target);

        void printPath(std::vector<IndexType>& path);
        int countFoundPaths();
        void printPaths();
        void reset();

    private:
        bool findPathAnyHelper(IndexType source, IndexType target, std::vector<IndexType>& path);
        void findPathAllHelper(IndexType source, IndexType target, std::vector<IndexType>& path);
    };

    template <typename EDGE>
    void DFSSolverEx<EDGE>::setGraph(const IGraphEx<EDGE>* graph) {
        m_graph = graph;
    }

    template <typename EDGE>
    void DFSSolverEx<EDGE>::reset() {
        m_visited.clear();
        m_paths.clear();
    }

    // function to perform DFS traversal in a directed graph to find
    // the complete path between source and destination vertices
    template <typename EDGE>
    bool DFSSolverEx<EDGE>::findPathAny(IndexType source, IndexType target, std::vector<IndexType>& path) {

        // setup 'm_visited' vector
        m_visited.resize(m_graph->countNodes());
        std::fill(std::begin(m_visited), std::end(m_visited), false);

        return findPathAnyHelper(source, target, path);
    }

    template <typename EDGE>
    bool DFSSolverEx<EDGE>::findPathAnyHelper(IndexType source, IndexType target, std::vector<IndexType>& path) {

        // mark current node as discovered
        m_visited.at(source) = true;

        // include current node in the path
        path.push_back(source);

        // if destination vertex is found
        if (source == target) {
            return true;
        }

        // do for all adjacent vertices of the dequeued vertex (source -> next)
        std::vector<IndexType> neighbours = m_graph->getNeighbouringNodes(source);
        for (IndexType next : neighbours) {

            // next is not discovered
            if (!m_visited.at(next)) {

                // return true if destination is found
                if (findPathAnyHelper(next, target, path))
                    return true;
            }
        }

        // backtrack: remove current node from the path
        path.pop_back();

        // return false if destination vertex is not reachable from source
        return false;
    }

    template <typename EDGE>
    void DFSSolverEx<EDGE>::findPathAll(IndexType source, IndexType target) {

        // setup 'm_visited' vector
        m_visited.resize(m_graph->countNodes());
        std::fill(std::begin(m_visited), std::end(m_visited), false);

        // setup 'currentPath' vector
        std::vector<IndexType> currentPath;
        currentPath.push_back(source);

        findPathAllHelper(source, target, currentPath);
    }

    template <typename EDGE>
    void DFSSolverEx<EDGE>::findPathAllHelper(IndexType source, IndexType target, std::vector<IndexType>& path) {

        // mark current node as discovered
        m_visited.at(source) = true;

        // if destination vertex is found
        if (source == target) {
            m_paths.push_back(path); // store found solution
            m_visited.at(source) = false;  // unmark current node as discovered
        }
        else {
            // do for every edge (source -> next)
            std::vector<IndexType> neighbours = m_graph->getNeighbouringNodes(source);
            for (IndexType next : neighbours) {
                // next is not discovered
                if (!m_visited.at(next)) {
                    path.push_back(next);  // include current node in the path
                    findPathAllHelper(next, target, path);
                    path.pop_back();  // remove current node from the path (backtrack)
                }
            }

            // unmark current node as discovered
            m_visited.at(source) = false;
        }
    }

    template <typename EDGE>
    void DFSSolverEx<EDGE>::printPath(std::vector<IndexType>& path) {
        std::for_each(std::begin(path), std::end(path) - 1, [](IndexType vertex) {
            std::cout << vertex << " -> ";
            }
        );

        IndexType last = *(std::end(path) - 1);
        std::cout << last << std::endl;
    }

    template <typename EDGE>
    void DFSSolverEx<EDGE>::printPaths() {
        for (auto& path : m_paths) {
            printPath(path);
        }
    }

    template <typename EDGE>
    int DFSSolverEx<EDGE>::countFoundPaths() {
        return m_paths.size();
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================


// Altes Zeugs

//
//namespace Solver_DFS {
//
//    template <typename NODE, typename EDGE>
//    class DFSSolver {
//    private:
//        const IGraph <NODE, EDGE>* m_graph;
//        std::vector<bool> m_visited;
//        std::deque<std::vector<IndexType>> m_paths;
//
//    public:
//        // c'tor
//        DFSSolver() : m_graph(nullptr) {}
//
//        // public interface
//        void setGraph(const IGraph<NODE, EDGE>*);
//        bool findPathAny(IndexType source, IndexType target, std::vector<IndexType>& path);
//        void findPathAll(IndexType source, IndexType target);
//
//        void printPath(std::vector<IndexType>& path);
//        int countFoundPaths();
//        void printPaths();
//        void reset();
//
//    private:
//        bool findPathAnyHelper(IndexType source, IndexType target, std::vector<IndexType>& path);
//        void findPathAllHelper(IndexType source, IndexType target, std::vector<IndexType>& path);
//    };
//
//    template <typename NODE, typename EDGE>
//    void DFSSolver<NODE, EDGE>::setGraph(const IGraph<NODE, EDGE>* graph) {
//        m_graph = graph;
//    }
//
//    template <typename NODE, typename EDGE>
//    void DFSSolver<NODE, EDGE>::reset() {
//        m_visited.clear();
//        m_paths.clear();
//    }
//
//    // function to perform DFS traversal in a directed graph to find
//    // the complete path between source and destination vertices
//    template <typename NODE, typename EDGE>
//    bool DFSSolver<NODE, EDGE>::findPathAny(IndexType source, IndexType target, std::vector<IndexType>& path) {
//
//        // setup 'm_visited' vector
//        m_visited.resize(m_graph->countNodes()); 
//        std::fill(std::begin(m_visited), std::end(m_visited), false);
//
//        return findPathAnyHelper(source, target, path);
//    }
//
//    template <typename NODE, typename EDGE>
//    bool DFSSolver<NODE, EDGE>::findPathAnyHelper(IndexType source, IndexType target, std::vector<IndexType>& path) {
//
//        // mark current node as discovered
//        m_visited.at(source) = true;
//
//        // include current node in the path
//        path.push_back(source);
//
//        // if destination vertex is found
//        if (source == target) {
//            return true;
//        }
//
//        // do for all adjacent vertices of the dequeued vertex (source -> next)
//        std::vector<IndexType> neighbours = m_graph->getNeighbouringNodes(source);
//        for (IndexType next : neighbours) {
//
//            // next is not discovered
//            if (!m_visited.at(next)) {
//
//                // return true if destination is found
//                if (findPathAnyHelper(next, target, path))
//                    return true;
//            }
//        }
//
//        // backtrack: remove current node from the path
//        path.pop_back();
//
//        // return false if destination vertex is not reachable from source
//        return false;
//    }
//
//    template <typename NODE, typename EDGE>
//    void DFSSolver<NODE, EDGE>::findPathAll(IndexType source, IndexType target) {
//
//        // setup 'm_visited' vector
//        m_visited.resize(m_graph->countNodes());
//        std::fill(std::begin(m_visited), std::end(m_visited), false);
//
//        // setup 'currentPath' vector
//        std::vector<IndexType> currentPath;
//        currentPath.push_back(source);
//
//        findPathAllHelper(source, target, currentPath);
//    }
//
//    template <typename NODE, typename EDGE>
//    void DFSSolver<NODE, EDGE>::findPathAllHelper(IndexType source, IndexType target, std::vector<IndexType>& path) {
//
//        // mark current node as discovered
//        m_visited.at(source) = true;
//
//        // if destination vertex is found
//        if (source == target) {
//            m_paths.push_back(path); // store found solution
//            m_visited.at(source) = false;  // unmark current node as discovered
//        }
//        else {
//            // do for every edge (source -> next)
//            std::vector<IndexType> neighbours = m_graph->getNeighbouringNodes(source);
//            for (IndexType next : neighbours) {
//                // next is not discovered
//                if (!m_visited.at(next)) {
//                    path.push_back(next);  // include current node in the path
//                    findPathAllHelper(next, target, path);
//                    path.pop_back();  // remove current node from the path (backtrack)
//                }
//            }
//
//            // unmark current node as discovered
//            m_visited.at(source) = false;
//        }
//    }
//
//    template <typename NODE, typename EDGE>
//    void DFSSolver<NODE, EDGE>::printPath(std::vector<IndexType>& path) {
//        std::for_each(std::begin(path), std::end(path) - 1, [](int vertex) {
//            std::cout << vertex << " -> ";
//            }
//        );
//
//        IndexType last = *(std::end(path) - 1);
//        std::cout << last << std::endl;
//    }
//
//    template <typename NODE, typename EDGE>
//    void DFSSolver<NODE, EDGE>::printPaths() {
//        for (auto path : m_paths) {
//            printPath(path);
//        }
//    }
//
//    template <typename NODE, typename EDGE>
//    int DFSSolver<NODE, EDGE>::countFoundPaths() {
//        return m_paths.size();
//    }
//}
//    
//void test_DFS_01()
//{
//    using namespace Solver_DFS;
//    using namespace NodeDetailsTest;
//    using namespace EdgeDetailsTest;
//
//    Node<TestNodeDetails> n1{ 0, { "Node 0"} };
//    Node<TestNodeDetails> n2{ 1, { "Node 1"} };
//    Node<TestNodeDetails> n3{ 2, { "Node 2"} };
//    Node<TestNodeDetails> n4{ 3, { "Node 3"} };
//    Node<TestNodeDetails> n5{ 4, { "Node 4"} };
//    Node<TestNodeDetails> n6{ 5, { "Node 5"} };
//    Node<TestNodeDetails> n7{ 6, { "Node 6"} };
//    Node<TestNodeDetails> n8{ 7, { "Node 7"} };
//
//    std::vector<Node<TestNodeDetails>> nodes = {
//        n1, n2, n3, n4, n5, n6, n7, n8
//    };
//
//    // vector of graph edges as per above diagram
//    std::vector<UnweightedEdge<TestEdgeDetails>> edges = {
//        {0, 3 , {} },
//        {1, 0, {} }, {1, 2, {} }, {1, 4, {} },
//        {2, 7, {} },
//        {3, 4, {} }, {3, 5, {} },
//        {4, 3, {} }, {4, 6, {} },
//        {5, 6, {} },
//        {6, 7, {} }
//    };
//
//    // graph with 8 nodes (vertices)
//    // GraphAdjList<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> testGraph(false);
//    GraphAdjMatrix<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> testGraph(Direction::undirected);
//
//    testGraph.addNodes(nodes);
//    testGraph.addEdges(edges);
//
//    DFSSolver<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> dfs;
//    dfs.setGraph(&testGraph);
//
//    constexpr int Source = 1;
//    constexpr int Target = 6;
//
//    if (std::vector<IndexType> resultPath; dfs.findPathAny(Source, Target, resultPath))
//    {
//        std::cout << "Path exists from vertex " << Source << " to vertex " << Target << std::endl;
//        std::cout << "The complete path is: ";
//        dfs.printPath(resultPath);
//    }
//    else {
//        std::cout << "No path exists between vertices " << Source << " and " << Target;
//    }
//}
//
//
//void test_DFS_02()
//{
//    using namespace Solver_DFS;
//    using namespace NodeDetailsNumbered;
//    using namespace EdgeDetailsEmpty;
//
//    //class NumberedNodeDetails {
//    //private:
//    //    int m_number;
//    //public:
//    //    // c'tors
//    //    NumberedNodeDetails() : m_number(0) {}
//    //    NumberedNodeDetails(int number) : m_number(number) {}
//
//    //    // getter
//    //    int getNumber() const { return m_number; };
//    //};
//
//    //// just for testing 
//    //class EmptyEdgeDetails {
//
//    //public:
//    //    // c'tors
//    //    EmptyEdgeDetails() = default;
//    //};
//
//    Node<NumberedNodeDetails> n1{ 0, 0 };
//    Node<NumberedNodeDetails> n2{ 1, 1 };
//    Node<NumberedNodeDetails> n3{ 2, 2 };
//    Node<NumberedNodeDetails> n4{ 3, 3 };
//    Node<NumberedNodeDetails> n5{ 4, 4 };
//    Node<NumberedNodeDetails> n6{ 5, 5 };
//    Node<NumberedNodeDetails> n7{ 6, 6 };
//    Node<NumberedNodeDetails> n8{ 7, 7 };
//
//    std::vector<Node<NumberedNodeDetails>> nodes = {
//        n1, n2, n3, n4, n5, n6, n7, n8
//    };
//
//    // vector of graph edges as per above diagram
//    std::vector<UnweightedEdge<EmptyEdgeDetails>> edges = {
//        {0, 3 , {} },
//        {1, 0, {} }, {1, 2, {} }, {1, 4, {} },
//        {2, 7, {} },
//        {3, 4, {} }, {3, 5, {} },
//        {4, 3, {} }, {4, 6, {} },
//        {5, 6, {} },
//        {6, 7, {} }
//    };
//
//    // graph with 8 nodes (vertices)
//    // GraphAdjList<Node<NumberedNodeDetails>, UnweightedEdge<EmptyEdgeDetails>> testGraph(false);
//    GraphAdjMatrix<Node<NumberedNodeDetails>, UnweightedEdge<EmptyEdgeDetails>> testGraph(Direction::undirected);
//
//    
//    testGraph.addNodes(nodes);
//    testGraph.addEdges(edges);
//
//    std::cout << "Node:       " << testGraph.countNodes() << std::endl;
//    std::cout << "Edges:      " << testGraph.countEdges() << std::endl;
//    std::cout << "IsDirected: " << testGraph.isDirected() << std::endl;
//    std::cout << "IsWeighted: " << testGraph.isWeighted() << std::endl;
//
//    DFSSolver<Node<NumberedNodeDetails>, UnweightedEdge<EmptyEdgeDetails>> dfs;
//
//    dfs.setGraph(&testGraph);
//
//    constexpr int Source = 1;
//    constexpr int Target = 6;
//
//    dfs.findPathAll(Source, Target);
//
//    if (int count; count = dfs.countFoundPaths())
//    {
//        std::cout << "Found " << count << " solutions:" << std::endl;
//        dfs.printPaths();
//    }
//    else {
//        std::cout << "No path exists between vertices " << Source << " and " << Target;
//    }
//}

