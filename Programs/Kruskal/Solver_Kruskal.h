//// =====================================================================================
//// Solver_Kruskal
//// =====================================================================================
//
//namespace Solver_Kruskal {
//
//    template <typename NODE, typename EDGE>
//    class KruskalSolver {
//        const IGraph <NODE, EDGE>* m_graph;
//        std::vector<IndexType> m_root;  // root nodes ('Union Find' algorithm)
//        std::vector<EDGE> m_mst;      // minimum spanning tree (described with edges)
//
//    public:
//        // c'tor
//        KruskalSolver() : m_graph(nullptr) {}
//
//        // public interface
//        void setGraph(const IGraph<NODE, EDGE>*);
//        void initRootNodes();
//        void solve();
//        int findSet(IndexType);
//        void unionSet(IndexType, IndexType);
//        void printMST();
//    };
//
//    template <typename NODE, typename EDGE>
//    void KruskalSolver<NODE, EDGE>::setGraph(const IGraph<NODE, EDGE>* graph) {
//        m_graph = graph;
//    }
//
//    template <typename NODE, typename EDGE>
//    void KruskalSolver<NODE, EDGE>::solve() {
//        initRootNodes();
//
//        // retrieve and sort all edges
//        std::vector<EDGE> edges = m_graph->getAllEdges();
//
//        std::sort(
//            std::begin(edges), 
//            std::end(edges), 
//            [](const EDGE& edge1, const EDGE& edge2) -> bool {
//                return getWeight<EDGE, int>(edge1) < getWeight<EDGE, int>(edge2);
//            }
//        );
//
//        for (const EDGE& edge : edges) {
//
//            IndexType source = getSource(edge);
//            IndexType target = getTarget(edge);
//
//            IndexType sourceRepresentative = findSet(source);
//            IndexType targetRepresentative = findSet(target);
//
//            if (sourceRepresentative != targetRepresentative) {
//                m_mst.push_back(edge); // add to minimum spanning tree
//                unionSet(sourceRepresentative, targetRepresentative);
//            }
//        }
//    }
//
//    template <typename NODE, typename EDGE>
//    int KruskalSolver<NODE, EDGE>::findSet(IndexType index) {
//        // if i is the parent of itself, we've found representative of the set
//        if (index == m_root[index]) {
//            return index;
//        }
//        else {
//            // if i is not the parent of itself, then i is not
//            // the representative of this set, so we recursively
//            // call 'findSet' on its parent
//            return findSet(m_root[index]);
//        }
//    }
//
//    template <typename NODE, typename EDGE>
//    void KruskalSolver<NODE, EDGE>::unionSet(IndexType u, IndexType v) {
//        m_root[u] = m_root[v];
//    }
//
//    template <typename NODE, typename EDGE>
//    void KruskalSolver<NODE, EDGE>::initRootNodes() {
//        // initialize root nodes
//        m_root.resize(m_graph->countNodes());
//        std::generate(std::begin(m_root), std::end(m_root), [n = 0]() mutable -> IndexType {
//            return n++;
//        });
//    }
//
//    template <typename NODE, typename EDGE>
//    void KruskalSolver<NODE, EDGE>::printMST() {
//        std::cout << "Edge :" << " Weight" << std::endl;
//        for (EDGE edge : m_mst) {
//            std::cout
//                << getSource(edge) << " - "
//                << getTarget(edge) << " : "
//                << getWeight<EDGE, int>(edge);
//            std::cout << std::endl;
//        }
//    }
//}
//
//// https://www.programiz.com
//void testPeLo01_Kruskal_Programiz()
//{
//    using namespace Solver_Kruskal;
//    using namespace NodeDetailsTest;
//    using namespace EdgeDetailsTest;
//
//    Node<TestNodeDetails> n1{ 0, { std::string("Node a")} };
//    Node<TestNodeDetails> n2{ 1, { std::string("Node b")} };
//    Node<TestNodeDetails> n3{ 2, { std::string("Node c")} };
//    Node<TestNodeDetails> n4{ 3, { std::string("Node d")} };
//    Node<TestNodeDetails> n5{ 4, { std::string("Node e")} };
//    Node<TestNodeDetails> n6{ 5, { std::string("Node f")} };
//
//    WeightedEdge<int, TestEdgeDetails> we1{ 0, 1, 4, "" };
//    WeightedEdge<int, TestEdgeDetails> we2{ 0, 2, 4, "" };
//    WeightedEdge<int, TestEdgeDetails> we3{ 1, 2, 2, "" };
//    WeightedEdge<int, TestEdgeDetails> we4{ 2, 3, 3, "" };
//    WeightedEdge<int, TestEdgeDetails> we5{ 2, 5, 2, "" };
//    WeightedEdge<int, TestEdgeDetails> we6{ 2, 4, 4, "" };
//    WeightedEdge<int, TestEdgeDetails> we7{ 3, 4, 3, "" };
//    WeightedEdge<int, TestEdgeDetails> we8{ 5, 4, 3, "" };
//
//    std::vector<Node<TestNodeDetails>> nodes = {
//        n1, n2, n3, n4, n5, n6
//    };
//
//    std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
//        we1, we2, we3, we4, we5, we6, we7, we8
//    };
//
//    // create graph
//    // GraphAdjList<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(false);
//    GraphAdjMatrix<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(Direction::undirected);
//    graph.addNodes(nodes);
//    graph.addEdges(edges);
//    std::cout << graph.toString() << std::endl;
//
//    // create solver
//    KruskalSolver<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> kruskal;
//    kruskal.setGraph(&graph);
//    kruskal.solve();
//    kruskal.printMST();
//}
//
////void testPeLo01_Kruskal_TUM()
////{
////    using namespace KruskalAlgorithm;
////
////    KruskalGraph g;
////
////    g.setNumberOfVertices(8);
////
////    g.addEdge(1, 5, 11);
////    g.addEdge(1, 2, 9);
////    g.addEdge(1, 6, 10);
////    g.addEdge(1, 7, 13);
////    g.addEdge(1, 0, 5);
////    g.addEdge(1, 4, 14);
////    g.addEdge(5, 1, 11);
////    g.addEdge(5, 4, 3);
////    g.addEdge(5, 6, 2);
////    g.addEdge(5, 2, 7);
////    g.addEdge(2, 5, 7);
////    g.addEdge(2, 1, 9);
////    g.addEdge(2, 3, 12);
////    g.addEdge(2, 6, 8);
////    g.addEdge(6, 2, 8);
////    g.addEdge(6, 5, 2);
////    g.addEdge(6, 7, 4);
////    g.addEdge(6, 3, 17);
////    g.addEdge(3, 6, 17);
////    g.addEdge(3, 2, 12);
////    g.addEdge(3, 0, 6);
////    g.addEdge(3, 7, 16);
////    g.addEdge(7, 3, 16);
////    g.addEdge(7, 6, 4);
////    g.addEdge(7, 4, 1);
////    g.addEdge(7, 0, 18);
////    g.addEdge(0, 4, 15);
////    g.addEdge(0, 1, 5);
////    g.addEdge(0, 3, 6);
////    g.addEdge(0, 7, 18);
////    g.addEdge(4, 1, 14);
////    g.addEdge(4, 5, 3);
////    g.addEdge(4, 7, 1);
////    g.addEdge(4, 0, 15);
////
////    g.kruskal();
////    g.print();
////}
//
//
//// =====================================================================================
//// End-of-File
//// =====================================================================================
