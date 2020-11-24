// =====================================================================================
// Solver_Dijkstra
// =====================================================================================

namespace Solver_Dijkstra {

    template<typename W>
    using Track = std::pair<IndexType, W>;

    template <typename NODE, typename EDGE>
    class DijkstraSolver {
    private:
        const IGraph <NODE, EDGE>* m_graph;
        std::vector<IndexType> m_distances;
        IndexType m_start; // start vertex

    public:
        // c'tor
        DijkstraSolver() : m_start(), m_graph(nullptr) {}

        // public interface
        void setGraph(const IGraph<NODE, EDGE>*);
        bool computeShortestPaths(IndexType startVertex);
        std::vector<IndexType> getDistances();

        // note: template function on a template class :-)
        template<typename NODE_DETAILS>
        void printDistances();
    };

    template <typename NODE, typename EDGE>
    void DijkstraSolver<NODE, EDGE>::setGraph(const IGraph<NODE, EDGE>* graph) {
        m_graph = graph;
    }

    template <typename NODE, typename EDGE>
    bool DijkstraSolver<NODE, EDGE>::computeShortestPaths(IndexType startVertex) {

        m_start = startVertex;
        m_distances.resize(m_graph->countNodes());

        // initialize all possible distances as infinite (-1)
        std::generate(std::begin(m_distances), std::end(m_distances), [] {
            return -1;
            });

        // need a lambda to compare Track elements
        auto compareTracks = [](const Track<int>& lhs, const Track<int>& rhs)  {
            auto [idLeft, weightLeft] = lhs;
            auto [idRight, weightRight] = rhs;
            return weightLeft > weightRight;
        };

        // need a priority queue
        // note: the third template parameter should be the *type* of the comparison function;
        // the function itself is then passed as a parameter in the constructor of priority_queue!
        std::priority_queue <
            Track<int>, std::vector<Track<int>>, decltype(compareTracks) > pq(compareTracks);

        // add source to priority queue, distance is 0
        Track<int> startTrack{ m_start , 0 };
        pq.push(startTrack);

        m_distances[m_start] = 0;

        // while priority queue isn't empty...
        while (!pq.empty()) {

            // get minimum distance vertex from priority queue - we call it 'vertex'
            Track<int> track = pq.top();
            int vertex = track.first;
            pq.pop();

            // get all adjacent vertices of the dequeued vertex
            std::vector<EDGE> neighbours = m_graph->getNeighbouringEdges(vertex);
            for (EDGE edge : neighbours) {

                IndexType target = getTarget<EDGE>(edge);
                IndexType weight = getWeight<EDGE, int>(edge);

                // if the distance to 'target' is shorter by going through 'vertex' ...
                if (m_distances[target] == -1 || m_distances[target] > m_distances[vertex] + weight) {

                    // update the distance of 'target'
                    m_distances[target] = m_distances[vertex] + weight;

                    // insert 'target' into the priority queue
                    Track<int> track{ target , m_distances[target]};
                    pq.push(track);
                }
            }
        }

        return true;
    }

    template <typename NODE, typename EDGE>
    std::vector<IndexType> DijkstraSolver<NODE, EDGE>::getDistances() {
        return m_distances;
    }

    template<typename NODE, typename EDGE>
    template<typename NODE_DETAILS>
    void DijkstraSolver<NODE, EDGE>::printDistances() {

        std::cout << "\nPrinting the shortest paths for node " << m_start << ".\n";

        std::vector<NODE> nodes = m_graph->getAllNodes();
        NODE startNode = nodes[m_start];
        NODE_DETAILS startLocation = getDetails<NODE, NODE_DETAILS>(startNode);

        int i = 0;
        for (NODE node : nodes) {
            NODE_DETAILS targetLocation = getDetails<NODE, NODE_DETAILS>(node);
            std::cout
                << "Distance from " << startLocation
                << " to " << targetLocation << " is: "
                << m_distances[i] << std::endl;
            i++;
        }
    }
}

void test_01_Dijkstra_LMU_Muenchen_Abstract()
{
    using namespace Solver_Dijkstra;
    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    // Beispiel "LMU_Muenchen"

    Node<TestNodeDetails> n1{ 0, {std::string("node a")} };
    Node<TestNodeDetails> n2{ 1, {std::string("node b")} };
    Node<TestNodeDetails> n3{ 2, {std::string("node c")} };
    Node<TestNodeDetails> n4{ 3, {std::string("node d")} };
    Node<TestNodeDetails> n5{ 4, {std::string("node e")} };
    Node<TestNodeDetails> n6{ 5, {std::string("node f")} };

    WeightedEdge<int, TestEdgeDetails> we1{ 0, 1, 10, "a => b [10]"};
    WeightedEdge<int, TestEdgeDetails> we2{ 0, 2, 20, "a => c [20]"};
    WeightedEdge<int, TestEdgeDetails> we3{ 1, 4, 10, "b => e [10]"};
    WeightedEdge<int, TestEdgeDetails> we4{ 1, 3, 50, "b => d [50]"};
    WeightedEdge<int, TestEdgeDetails> we5{ 2, 4, 33, "c => e [33]"};
    WeightedEdge<int, TestEdgeDetails> we6{ 2, 3, 20, "c => d [20]"};
    WeightedEdge<int, TestEdgeDetails> we7{ 3, 4, 20, "d => e [20]"};
    WeightedEdge<int, TestEdgeDetails> we8{ 3, 5,  2, "d => f [ 2]"};
    WeightedEdge<int, TestEdgeDetails> we9{ 4, 5,  1, "e => f [ 1]"};

    std::vector<Node<TestNodeDetails>> nodes = {
        n1, n2, n3, n4, n5, n6
    };

    std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
        we1, we2, we3, we4, we5, we6, we7, we8, we9
    };

    // create graph
    // GraphAdjList<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(true);
    GraphAdjMatrix<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(Direction::undirected);

    graph.addNodes(nodes);
    graph.addEdges(edges);
    std::cout << graph.toString() << std::endl;

    // create solver
    DijkstraSolver<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> dijkstra;
    dijkstra.setGraph(&graph);

    std::cout << "Node:       " << graph.countNodes() << std::endl;
    std::cout << "Edges:      " << graph.countEdges() << std::endl;
    std::cout << "IsDirected: " << graph.isDirected() << std::endl;
    std::cout << "IsWeighted: " << graph.isWeighted() << std::endl;

    dijkstra.computeShortestPaths(0);
    dijkstra.printDistances<TestNodeDetails>();
}

void test_02_Dijkstra_Bleeptrack_Youtube_Tutorial()
{
    using namespace Solver_Dijkstra;
    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    // Beispiel "Bleeptrack Youtube Tutorial"
    constexpr int NumNodes = 9;

    // create graph
    GraphAdjList<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(true);

    Node<TestNodeDetails> n1{ 0, {std::string("Node S")} };
    Node<TestNodeDetails> n2{ 1, {std::string("Node A")} };
    Node<TestNodeDetails> n3{ 2, {std::string("Node B")} };
    Node<TestNodeDetails> n4{ 3, {std::string("Node C")} };
    Node<TestNodeDetails> n5{ 4, {std::string("Node D")} };
    Node<TestNodeDetails> n6{ 5, {std::string("Node E")} };
    Node<TestNodeDetails> n7{ 6, {std::string("Node F")} };
    Node<TestNodeDetails> n8{ 7, {std::string("Node G")} };
    Node<TestNodeDetails> n9{ 8, {std::string("Node Z")} };

    graph.addNodes({
        n1, n2, n3, n4, n5, n6, n7, n8, n9
        }
    );

    constexpr int S = 0;
    constexpr int A = 1;
    constexpr int B = 2;
    constexpr int C = 3;
    constexpr int D = 4;
    constexpr int E = 5;
    constexpr int F = 6;
    constexpr int G = 7;
    constexpr int Z = 8;

    WeightedEdge<int, TestEdgeDetails> we1{ S, A, 5 , "" };
    WeightedEdge<int, TestEdgeDetails> we2{ S, B, 2 , "" };
    WeightedEdge<int, TestEdgeDetails> we3{ S, G, 4 , "" };
    WeightedEdge<int, TestEdgeDetails> we4{ A, C, 3 , "" };
    WeightedEdge<int, TestEdgeDetails> we5{ A, B, 1 , "" };
    WeightedEdge<int, TestEdgeDetails> we6{ C, D, 4 , "" };
    WeightedEdge<int, TestEdgeDetails> we7{ C, E, 6 , "" };
    WeightedEdge<int, TestEdgeDetails> we8{ G, D, 2 , "" };
    WeightedEdge<int, TestEdgeDetails> we9{ D, E, 10, "" };
    WeightedEdge<int, TestEdgeDetails> we10{ D, F, 8 , "" };
    WeightedEdge<int, TestEdgeDetails> we11{ E, Z, 7 , "" };
    WeightedEdge<int, TestEdgeDetails> we12{ F, Z, 11, "" };

    graph.addEdges({ 
        we1, we2, we3, we4, we5, we6, we7, we8, we9, we10, we11, we12 
    });

    // create solver
    DijkstraSolver<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> dijkstra;
    dijkstra.setGraph(&graph);

    dijkstra.computeShortestPaths(0);
    dijkstra.printDistances<TestNodeDetails>();
}

// =========================================================================================================

void test_03_Dijkstra_TUM_Europa ()
{
    using namespace Solver_Dijkstra;
    using namespace NodeDetailsCities;
    using namespace EdgeDetailsCities;

    // Beispiel TUM München Europakarte
    constexpr int a = 0;
    constexpr int b = 1;
    constexpr int c = 2;
    constexpr int d = 3;
    constexpr int e = 4;
    constexpr int f = 5;
    constexpr int g = 6;
    constexpr int h = 7;
    constexpr int i = 8;
    constexpr int j = 9;

    Node<CityDetails> n01{ a, {a, std::string("London"), std::string("a")} };
    Node<CityDetails> n02{ b, {b, std::string("Berlin"), std::string("b")} };
    Node<CityDetails> n03{ c, {c, std::string("Madrid"), std::string("c")} };
    Node<CityDetails> n04{ d, {d, std::string("Kiew"), std::string("d")} };
    Node<CityDetails> n05{ e, {e, std::string("Rom"), std::string("e")} };
    Node<CityDetails> n06{ f, {f, std::string("Paris"), std::string("f")} };
    Node<CityDetails> n07{ g, {g, std::string("Minsk"), std::string("g")} };
    Node<CityDetails> n08{ h, {h, std::string("Stockholm"), std::string("h")} };
    Node<CityDetails> n09{ i, {i, std::string("Dublin"), std::string("i")} };
    Node<CityDetails> n10{ j, {j, std::string("Wien"), std::string("j")} };

    WeightedEdge<int, RouteDetails> we01{ i, a, 464 , "Dublin => London" };
    WeightedEdge<int, RouteDetails> we02{ a, i, 464 , "London => Dublin" };

    WeightedEdge<int, RouteDetails> we03{ c, f, 1054 , "Madrid => Paris" };
    WeightedEdge<int, RouteDetails> we04{ f, c, 1054 , "Paris => Madrid" };

    WeightedEdge<int, RouteDetails> we05{ a, f, 343 , "London => Paris" };
    WeightedEdge<int, RouteDetails> we06{ f, a, 343 , "Paris => London" };

    WeightedEdge<int, RouteDetails> we07{ c, e, 1364 , "Madrid => Rom" };
    WeightedEdge<int, RouteDetails> we08{ e, c, 1364 , "Rom => Madrid" };

    WeightedEdge<int, RouteDetails> we09{ a, h, 1435 , "London => Stockholm" };
    WeightedEdge<int, RouteDetails> we10{ h, a, 1435 , "Stockholm => London" };

    WeightedEdge<int, RouteDetails> we11{ f, b, 879 , "Paris => Berlin" };
    WeightedEdge<int, RouteDetails> we12{ b, f, 879 , "Berlin => Paris" };

    WeightedEdge<int, RouteDetails> we13{ f, e, 1106 , "Paris => Rom" };
    WeightedEdge<int, RouteDetails> we14{ e, f, 1106 , "Rom => Paris" };

    WeightedEdge<int, RouteDetails> we15{ h, g, 837 , "Stockholm => Minsk" };
    WeightedEdge<int, RouteDetails> we16{ g, h, 837 , "Minsk => Stockholm" };

    WeightedEdge<int, RouteDetails> we17{ b, g, 954 , "Berlin => Minsk" };
    WeightedEdge<int, RouteDetails> we18{ g, b, 954 , "Minsk => Berlin" };

    WeightedEdge<int, RouteDetails> we19{ j, d, 1053 , "Wien => Kiew" };
    WeightedEdge<int, RouteDetails> we20{ d, j, 1053 , "Kiew => Wien" };

    WeightedEdge<int, RouteDetails> we21{ g, d, 433 , "Minsk => Kiew" };
    WeightedEdge<int, RouteDetails> we22{ d, g, 433 , "Kiew => Minsk" };

    WeightedEdge<int, RouteDetails> we23{ b, h, 811 , "Berlin => Stockholm" };
    WeightedEdge<int, RouteDetails> we24{ h, b, 811 , "Stockholm => Berlin" };

    WeightedEdge<int, RouteDetails> we25{ b, j, 524 , "Berlin => Wien" };
    WeightedEdge<int, RouteDetails> we26{ j, b, 524 , "Wien => Berlin" };

    WeightedEdge<int, RouteDetails> we27{ j, e, 766 , "Wien => Rom" };
    WeightedEdge<int, RouteDetails> we28{ e, j, 766 , "Rom => Wien" };

    // create graph
    // GraphAdjList<Node<CityDetails>, WeightedEdge<int, RouteDetails>> graph(true);
    GraphAdjMatrix<Node<CityDetails>, WeightedEdge<int, RouteDetails>> graph(Direction::directed);

    graph.addNodes({
        n01, n02, n03, n04, n05, n06, n07, n08, n09, n10
    });

    graph.addEdges({
        we01, we02, we03, we04, we05, we06, we07, we08, we09, we10,
        we11, we12, we13, we14, we15, we16, we17, we18, we19, we20,
        we21, we22, we23, we24, we25, we26, we27, we28
    });

    std::cout << graph.toString() << std::endl;

    // create solver
    DijkstraSolver<Node<CityDetails>, WeightedEdge<int, RouteDetails>> dijkstra;
    dijkstra.setGraph(&graph);

    // travelling from Madrid ('c' == Madrid)
    dijkstra.computeShortestPaths(c);
    dijkstra.printDistances<CityDetails>();
}


// =====================================================================================
// End-of-File
// =====================================================================================
