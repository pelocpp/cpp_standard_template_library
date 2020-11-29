//// =====================================================================================
//// XXX
//// =====================================================================================
//
//namespace Solver_BFS {
//
//    template <typename NODE, typename EDGE>
//    class BFSSolver {
//    private:
//        // interface pointer
//        const IGraph <NODE, EDGE>* m_graph;
//
//        std::deque<IndexType> m_queue;
//        std::vector<bool> m_visited;
//
//    public:
//        // c'tor
//        BFSSolver() : m_graph(nullptr) {}
//
//        // public interface
//        void setGraph(const IGraph<NODE, EDGE>*);
//        std::vector<std::optional<IndexType>> solve(IndexType start);
//        std::vector<IndexType> reconstructPath(IndexType source, IndexType target, std::vector<std::optional<IndexType>> prev);
//        void printSolution(std::vector<IndexType> path);
//
//        void reset() {
//            m_queue.clear();
//            m_visited.clear();
//        }
//    };
//
//    template <typename NODE, typename EDGE>
//    void BFSSolver<NODE, EDGE>::setGraph(const IGraph<NODE, EDGE>* graph) {
//        m_graph = graph;
//    }
//
//    template <typename NODE, typename EDGE>
//    std::vector<std::optional<IndexType>> BFSSolver<NODE, EDGE>::solve(IndexType start) {
//
//        // setup 'm_visited' vector
//        m_visited.resize(m_graph->countNodes());
//        std::fill(std::begin(m_visited), std::end(m_visited), false);
//        m_visited.at(start) = true;
//
//        // setup 'previous' vector
//        std::vector<std::optional<IndexType>> previous;
//        previous.resize(m_graph->countNodes());
//        std::fill(std::begin(previous), std::end(previous), std::nullopt);
//
//        m_queue.push_back(start);
//        while (!m_queue.empty()) {
//
//            // dequeue a vertex from queue
//            int node = m_queue.front();
//            m_queue.pop_front();
//
//            // get all adjacent vertices of the dequeued vertex
//            std::vector<IndexType> neighbours = m_graph->getNeighbouringNodes(node);
//            for (IndexType next : neighbours) {
//                if (!m_visited.at(next)) {
//                    m_queue.push_back(next);
//                    m_visited.at(next) = true;
//                    previous.at(next) = node;
//                }
//            }
//        }
//
//        return previous;
//    }
//
//    template <typename NODE, typename EDGE>
//    std::vector<IndexType> BFSSolver<NODE, EDGE>::reconstructPath(IndexType source, IndexType target, std::vector<std::optional<IndexType>> prev) {
//        
//        // reconstruct path going backwards from 'target'
//        std::vector<IndexType> path;
//
//        for (IndexType pos = target; pos != -1; pos = prev.at(pos).has_value() ? prev.at(pos).value() : -1) {
//            path.push_back(pos);
//        }
//
//        std::reverse(std::begin(path), std::end(path));
//
//        // if 'source' and 'target' are connected, return the path
//        if (path.at(0) == source) {
//            return path;
//        }
//        else {
//            return {};
//        }
//    }
//
//    template <typename NODE, typename EDGE>
//    void BFSSolver<NODE, EDGE>::printSolution(std::vector<IndexType> path) {
//        if (path.size() == 0) {
//            std::cout << "No Solution found !" << std::endl;
//            return;
//        }
//
//        std::for_each(std::begin(path), std::end(path) - 1, [](int vertex) {
//            std::cout << "[" << vertex << "] => ";
//            }
//        );
//
//        // print last element without trailing comma :-)
//        int vertex = path.at(path.size() - 1);
//        std::cout << "[" << vertex << "].";
//    }
//}
//
//void test_BFS_NordAmerika()
//{
//    using namespace Solver_BFS;
//    using namespace NodeDetailsFlightInfo;
//    using namespace EdgeDetailsFlightInfo;
//
//    // Beispiel "Flugverbindungen in Nordamerika"
//    using FlightNode = Node<FlightNodeInfo>;
//
//    Node<FlightNodeInfo> n1{ 0, { "NewYork"} };
//    Node<FlightNodeInfo> n2{ 1, { "Chicago"} };
//    Node<FlightNodeInfo> n3{ 2, { "Toronto"} };
//    Node<FlightNodeInfo> n4{ 3, { "Denver"} };
//    Node<FlightNodeInfo> n5{ 4, { "Los Angeles"} };
//    Node<FlightNodeInfo> n6{ 5, { "Calgary"} };
//    Node<FlightNodeInfo> n7{ 6, { "Houston"} };
//    Node<FlightNodeInfo> n8{ 7, { "Urbana"} };
//
//    std::vector<Node<FlightNodeInfo>> nodes = {
//       n1, n2, n3, n4, n5, n6, n7, n8
//    };
//
//    // vector of graph edges as per above diagram
//    std::vector<UnweightedEdge<FlightEdgeInfo>> edges = {
//
//        {0, 1, {}},
//        {0, 2, {}},
//        {0, 3, {}},
//        {1, 3, {}},
//        {2, 4, {}},
//        {2, 1, {}},
//        {2, 5, {}},
//        {3, 4, {}},
//        {3, 6, {}},
//        {3, 7, {}},
//        {6, 4, {}}
//    };
//
//    GraphAdjList<Node<FlightNodeInfo>, UnweightedEdge<FlightEdgeInfo>> flightGraph(false);
//    // GraphAdjMatrix<Node<FlightNodeInfo>, UnweightedEdge<FlightEdgeInfo>> flightGraph(false);
//    
//    flightGraph.addNodes(nodes);
//    flightGraph.addEdges(edges);
//
//    std::cout << flightGraph.toString() << std::endl;
//
//    BFSSolver<Node<FlightNodeInfo>, UnweightedEdge<FlightEdgeInfo>> bfs;
//    bfs.setGraph(&flightGraph);
//    std::vector<std::optional<IndexType>> paths = bfs.solve(0);
//    std::vector<IndexType> solution = bfs.reconstructPath(0, 4, paths);
//    bfs.printSolution(solution);
//
//    std::for_each(std::begin(solution), std::end(solution) - 1, [&](int id) {
//        FlightNodeInfo info = getDetails<Node<FlightNodeInfo>, FlightNodeInfo>(nodes[id]);
//        std::cout << info.getDeparture() << " => ";
//        }
//    );
//
//    // print last element without trailing comma :-)
//    IndexType last = solution.back();
//    FlightNodeInfo info = getDetails<Node<FlightNodeInfo>, FlightNodeInfo>(nodes[last]);
//    std::cout << info.getDeparture() << "." << std::endl;
//}
//
//void test_BFS_SchaumsOutline() {
//
//    using namespace Solver_BFS;
//    using namespace NodeDetailsTest;
//    using namespace EdgeDetailsTest;
//
//    // Beispiel aus "Schaums Outline": Graph mit 9 nodes Knoten
//
//    // GraphAdjList<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> schaumsGraph(false);
//    GraphAdjMatrix<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> schaumsGraph(Direction::undirected);
//
//    schaumsGraph.addNodes({
//        { 0, { "Node 1"} },
//        { 1, { "Node 2"} },
//        { 2, { "Node 3"} },
//        { 3, { "Node 4"} },
//        { 4, { "Node 5"} },
//        { 5, { "Node 6"} },
//        { 6, { "Node 7"} },
//        { 7, { "Node 8"} },
//        { 8, { "Node 9"} }
//        });
//
//    // vector of edges
//    std::vector<UnweightedEdge<TestEdgeDetails>> edges = {
//        { 0, 1, { ""}},
//        { 0, 2, { ""}},
//        { 0, 5, { ""}},
//        { 1, 2, { ""}},
//        { 1, 6, { ""}},
//        { 2, 5, { ""}},
//        { 3, 2, { ""}},
//        { 4, 2, { ""}},
//        { 4, 3, { ""}},
//        { 4, 7, { ""}},
//        { 5, 3, { ""}},
//        { 6, 2, { ""}},
//        { 6, 4, { ""}},
//        { 7, 3, { ""}},
//        { 7, 8, { ""}},
//        { 8, 4, { ""}},
//        { 8, 6, { ""}}
//    };
//    schaumsGraph.addEdges(edges);
//
//    std::cout << "Nodes: " << schaumsGraph.countNodes() << ", Edges: " << schaumsGraph.countEdges() << std::endl;
//    std::cout << schaumsGraph.toString() << std::endl;
//
//    BFSSolver<Node<TestNodeDetails>, UnweightedEdge<TestEdgeDetails>> bfs;
//    bfs.setGraph(&schaumsGraph);
//
//    std::vector<std::optional<IndexType>> paths = bfs.solve(0);
//    std::vector<IndexType> solution = bfs.reconstructPath(0, 7, paths);
//    bfs.printSolution(solution);
//}
//
//
//// =====================================================================================
//// End-of-File
//// =====================================================================================
