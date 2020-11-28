// =====================================================================================
// Solver_Dijkstra
// =====================================================================================

namespace Solver_Dijkstra_Ex {

    template<typename W>
    using Track = std::pair<IndexType, W>;

    template <typename EDGE>
    class DijkstraSolverEx {
    private:
        const IGraphEx<EDGE>* m_graph;
        std::vector<IndexType> m_distances;
        IndexType m_start; // start vertex

    public:
        // c'tor
        DijkstraSolverEx() : m_start(), m_graph(nullptr) {}

        // public interface
        void setGraph(const IGraphEx<EDGE>*);
        bool computeShortestPaths(IndexType startVertex);
        std::vector<IndexType> getDistances();

        // note: template function on a template class :-)
        template<typename NODE_DETAILS>
        void printDistances();
    };

    template <typename EDGE>
    void DijkstraSolverEx<EDGE>::setGraph(const IGraphEx<EDGE>* graph) {
        m_graph = graph;
    }

    template <typename EDGE>
    bool DijkstraSolverEx<EDGE>::computeShortestPaths(IndexType startVertex) {

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

    template <typename EDGE>
    std::vector<IndexType> DijkstraSolverEx<EDGE>::getDistances() {
        return m_distances;
    }

    //template<typename EDGE>
    //template<typename NODE_DETAILS>
    //void DijkstraSolverEx<EDGE>::printDistances() {

    //    std::cout << "\nPrinting the shortest paths for node " << m_start << ".\n";

        //std::vector<NODE> nodes = m_graph->getAllNodes();
        //NODE startNode = nodes[m_start];
        //NODE_DETAILS startLocation = getDetails<NODE_DETAILS>(startNode);

        //int i = 0;
        //for (NODE node : nodes) {
        //    NODE_DETAILS targetLocation = getDetails<NODE_DETAILS>(node);
        //    std::cout
        //        << "Distance from " << startLocation
        //        << " to " << targetLocation << " is: "
        //        << m_distances[i] << std::endl;
        //    i++;
        //}
   // }
}

using MyNodeType = BaseNode<int, std::string>;

auto my_make_edge(int id, std::string text) -> MyNodeType {
    return make_node<int, std::string>(id, text);
};

using MyEdgeType = BaseEdgeWeighted<int, std::string>;

void printDistances(IndexType start, IndexType numNodes, std::vector<IndexType>& distances) {

    std::cout << "\nPrinting the shortest paths for node " << start << ".\n";

    //std::vector<NODE> nodes = m_graph->getAllNodes();
    //NODE startNode = nodes[m_start];
    //NODE_DETAILS startLocation = getDetails<NODE_DETAILS>(startNode);

    //int i = 0;
    //for (NODE node : nodes) {

    for (IndexType i = 0; i < numNodes; ++i) {
       // NODE_DETAILS targetLocation = getDetails<NODE_DETAILS>(node);
        std::cout
            << "Distance from " << start
            << " to " << i << " is: "
            << distances[i] << std::endl;
    }
}


void test_01_Dijkstra_LMU_Muenchen_Abstract_Ex()
{
    using namespace Solver_Dijkstra_Ex;

    // Beispiel "LMU_Muenchen"

    constexpr int NumNodes = 6;

    MyNodeType n1{ 0, std::string("node a") };
    MyNodeType n2{ 1, std::string("node b") };
    MyNodeType n3{ 2, std::string("node c") };
    MyNodeType n4{ 3, std::string("node d") };
    MyNodeType n5{ 4, std::string("node e") };
    MyNodeType n6{ 5, std::string("node f") };

    MyEdgeType edge1{ 0, 1, 10, "a => b [10]" };
    MyEdgeType edge2{ 0, 2, 20, "a => c [20]" };
    MyEdgeType edge3{ 1, 4, 10, "b => e [10]" };
    MyEdgeType edge4{ 1, 3, 50, "b => d [50]" };
    MyEdgeType edge5{ 2, 4, 33, "c => e [33]" };
    MyEdgeType edge6{ 2, 3, 20, "c => d [20]" };
    MyEdgeType edge7{ 3, 4, 20, "d => e [20]" };
    MyEdgeType edge8{ 3, 5,  2, "d => f [ 2]" };
    MyEdgeType edge9{ 4, 5,  1, "e => f [ 1]" };

    std::vector<MyNodeType> nodes = {
        n1, n2, n3, n4, n5, n6
    };

    std::vector<MyEdgeType> edges = {
        edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9
    };

    // create graph
    // GraphAdjListEx<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(true);
    GraphAdjMatrixEx<MyEdgeType, Weighted> graph(Directed);

    graph.setNodesCount(6);
    graph.addEdges(edges);
    std::cout << graph.toString() << std::endl;

    // create solver
    DijkstraSolverEx<MyEdgeType> dijkstra;
    dijkstra.setGraph(&graph);

    std::cout << "Node:       " << graph.countNodes() << std::endl;
    std::cout << "Edges:      " << graph.countEdges() << std::endl;
    std::cout << "IsDirected: " << graph.isDirected() << std::endl;
    std::cout << "IsWeighted: " << graph.isWeighted() << std::endl;

    dijkstra.computeShortestPaths(0);
    std::vector<IndexType> distances = dijkstra.getDistances();
    printDistances(0, NumNodes, distances);
}

void test_02_Dijkstra_Bleeptrack_Youtube_Tutorial_Ex()
{
    using namespace Solver_Dijkstra_Ex;

    // Beispiel "Bleeptrack Youtube Tutorial"
    constexpr int NumNodes = 9;

    // create graph
    GraphAdjListEx<MyEdgeType, Weighted> graph(Directed);

    graph.setNodesCount(NumNodes);

    MyNodeType n1{ 0, std::string("Node S") };
    MyNodeType n2{ 1, std::string("Node A") };
    MyNodeType n3{ 2, std::string("Node B") };
    MyNodeType n4{ 3, std::string("Node C") };
    MyNodeType n5{ 4, std::string("Node D") };
    MyNodeType n6{ 5, std::string("Node E") };
    MyNodeType n7{ 6, std::string("Node F") };
    MyNodeType n8{ 7, std::string("Node G") };
    MyNodeType n9{ 8, std::string("Node Z") };

    constexpr int S = 0;
    constexpr int A = 1;
    constexpr int B = 2;
    constexpr int C = 3;
    constexpr int D = 4;
    constexpr int E = 5;
    constexpr int F = 6;
    constexpr int G = 7;
    constexpr int Z = 8;

    MyEdgeType we1{ S, A, 5 , "" };
    MyEdgeType we2{ S, B, 2 , "" };
    MyEdgeType we3{ S, G, 4 , "" };
    MyEdgeType we4{ A, C, 3 , "" };
    MyEdgeType we5{ A, B, 1 , "" };
    MyEdgeType we6{ C, D, 4 , "" };
    MyEdgeType we7{ C, E, 6 , "" };
    MyEdgeType we8{ G, D, 2 , "" };
    MyEdgeType we9{ D, E, 10, "" };
    MyEdgeType we10{ D, F, 8 , "" };
    MyEdgeType we11{ E, Z, 7 , "" };
    MyEdgeType we12{ F, Z, 11, "" };

    graph.addEdges({ 
        we1, we2, we3, we4, we5, we6, we7, we8, we9, we10, we11, we12 
    });

    std::cout << graph.toString() << std::endl;

    // create solver
    DijkstraSolverEx<MyEdgeType> dijkstra;
    dijkstra.setGraph(&graph);

    dijkstra.computeShortestPaths(0);
    std::vector<IndexType> distances = dijkstra.getDistances();
    printDistances(0, NumNodes, distances);
}

// =========================================================================================================

void test_03_Dijkstra_TUM_Europa_Ex ()
{
    using namespace Solver_Dijkstra_Ex;

    constexpr int NumNodes = 10;

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

    //Node<CityDetails> n01{ a, {a, std::string("London"), std::string("a")} };
    //Node<CityDetails> n02{ b, {b, std::string("Berlin"), std::string("b")} };
    //Node<CityDetails> n03{ c, {c, std::string("Madrid"), std::string("c")} };
    //Node<CityDetails> n04{ d, {d, std::string("Kiew"), std::string("d")} };
    //Node<CityDetails> n05{ e, {e, std::string("Rom"), std::string("e")} };
    //Node<CityDetails> n06{ f, {f, std::string("Paris"), std::string("f")} };
    //Node<CityDetails> n07{ g, {g, std::string("Minsk"), std::string("g")} };
    //Node<CityDetails> n08{ h, {h, std::string("Stockholm"), std::string("h")} };
    //Node<CityDetails> n09{ i, {i, std::string("Dublin"), std::string("i")} };
    //Node<CityDetails> n10{ j, {j, std::string("Wien"), std::string("j")} };

    MyEdgeType we01{ i, a, 464 , "Dublin => London" };
    MyEdgeType we02{ a, i, 464 , "London => Dublin" };

    MyEdgeType we03{ c, f, 1054 , "Madrid => Paris" };
    MyEdgeType we04{ f, c, 1054 , "Paris => Madrid" };

    MyEdgeType we05{ a, f, 343 , "London => Paris" };
    MyEdgeType we06{ f, a, 343 , "Paris => London" };

    MyEdgeType we07{ c, e, 1364 , "Madrid => Rom" };
    MyEdgeType we08{ e, c, 1364 , "Rom => Madrid" };

    MyEdgeType we09{ a, h, 1435 , "London => Stockholm" };
    MyEdgeType we10{ h, a, 1435 , "Stockholm => London" };

    MyEdgeType we11{ f, b, 879 , "Paris => Berlin" };
    MyEdgeType we12{ b, f, 879 , "Berlin => Paris" };

    MyEdgeType we13{ f, e, 1106 , "Paris => Rom" };
    MyEdgeType we14{ e, f, 1106 , "Rom => Paris" };

    MyEdgeType we15{ h, g, 837 , "Stockholm => Minsk" };
    MyEdgeType we16{ g, h, 837 , "Minsk => Stockholm" };

    MyEdgeType we17{ b, g, 954 , "Berlin => Minsk" };
    MyEdgeType we18{ g, b, 954 , "Minsk => Berlin" };

    MyEdgeType we19{ j, d, 1053 , "Wien => Kiew" };
    MyEdgeType we20{ d, j, 1053 , "Kiew => Wien" };

    MyEdgeType we21{ g, d, 433 , "Minsk => Kiew" };
    MyEdgeType we22{ d, g, 433 , "Kiew => Minsk" };

    MyEdgeType we23{ b, h, 811 , "Berlin => Stockholm" };
    MyEdgeType we24{ h, b, 811 , "Stockholm => Berlin" };

    MyEdgeType we25{ b, j, 524 , "Berlin => Wien" };
    MyEdgeType we26{ j, b, 524 , "Wien => Berlin" };

    MyEdgeType we27{ j, e, 766 , "Wien => Rom" };
    MyEdgeType we28{ e, j, 766 , "Rom => Wien" };

    // create graph
    GraphAdjListEx<MyEdgeType, Weighted> graph(Directed);
    // GraphAdjMatrixEx<MyEdgeType, Weighted> graph(Directed);

    graph.setNodesCount(NumNodes);

    //graph.addNodes({
    //    n01, n02, n03, n04, n05, n06, n07, n08, n09, n10
    //});

    graph.addEdges({
        we01, we02, we03, we04, we05, we06, we07, we08, we09, we10,
        we11, we12, we13, we14, we15, we16, we17, we18, we19, we20,
        we21, we22, we23, we24, we25, we26, we27, we28
    });

    std::cout << graph.toString() << std::endl;

    // create solver
    DijkstraSolverEx<MyEdgeType> dijkstra;
    dijkstra.setGraph(&graph);

    // travelling from Madrid ('c' == Madrid)
    dijkstra.computeShortestPaths(c);
    std::vector<IndexType> distances = dijkstra.getDistances();
    printDistances(0, NumNodes, distances);
}

//Printing the shortest paths for node 2.
//Distance from[c] Madrid to[a] London is : 1397
//Distance from[c] Madrid to[b] Berlin is : 1933
//Distance from[c] Madrid to[c] Madrid is : 0
//Distance from[c] Madrid to[d] Kiew is : 3183
//Distance from[c] Madrid to[e] Rom is : 1364
//Distance from[c] Madrid to[f] Paris is : 1054
//Distance from[c] Madrid to[g] Minsk is : 2887
//Distance from[c] Madrid to[h] Stockholm is : 2744
//Distance from[c] Madrid to[i] Dublin is : 1861
//Distance from[c] Madrid to[j] Wien is : 2130

// =====================================================================================
// End-of-File
// =====================================================================================
