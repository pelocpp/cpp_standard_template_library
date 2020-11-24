// =====================================================================================
// Solver_NearestNeighbour
// =====================================================================================

namespace Solver_NearestNeighbour {

    template <typename NODE, typename EDGE>
    class NearestNeighbourSolver {

    private:
        const IGraph <NODE, EDGE>* m_graph;
        std::stack<IndexType> m_stack;
        int m_totalDistance;

    public:
        // c'tor
        NearestNeighbourSolver() : m_graph{ nullptr }, m_totalDistance{ 0 } {}

        // public interface
        void setGraph(const IGraph<NODE, EDGE>*);
        void solve(IndexType start);
        int total();
        void print();
    };

    template <typename NODE, typename EDGE>
    void NearestNeighbourSolver<NODE, EDGE>::setGraph(const IGraph<NODE, EDGE>* graph) {
        m_graph = graph;
    }

    template <typename NODE, typename EDGE>
    void NearestNeighbourSolver<NODE, EDGE>::solve(IndexType start) {
        int numberOfNodes = m_graph->countNodes();

        // setup 'visited' vector
        std::vector<bool> visited;
        visited.resize(numberOfNodes);
        visited.at(start) = true;

        // push 'start' node on 'travelling path'
        IndexType next = start;
        m_stack.push(start);

        int count = 1;
        m_totalDistance = 0;
        while (count < numberOfNodes) {

            std::vector<EDGE> neighbours = m_graph->getNeighbouringEdges(next);
            std::optional<int> min (std::nullopt);
            IndexType found = -1;

            for (EDGE edge : neighbours) {

                int weight = getWeight<EDGE, int>(edge);
                IndexType target = getTarget(edge);

                if (!visited.at(target)) {
                    if (!min.has_value() or (weight < min.value())) {
                        min = weight;
                        found = target;
                    }
                }
            }

            m_totalDistance += min.value();

            next = found;
            visited.at(next) = true;
            m_stack.push(next);

            count++;
        }

        // need to calculate distance from latest node to start node
        EDGE latest = m_graph->searchEdge(next, start);
        int weight = getWeight<EDGE, int>(latest);
        m_totalDistance += weight;

        m_stack.push(start);
    }

    template <typename NODE, typename EDGE>
    void NearestNeighbourSolver<NODE, EDGE>::print() {

        std::stack<IndexType> reverseStack;

        while (!m_stack.empty()) {

            IndexType id = m_stack.top();
            m_stack.pop();
            reverseStack.push(id);
        }

        int counter = reverseStack.size();
        int linebreak = 10;
        while (counter > 1) {

            IndexType id = reverseStack.top();
            std::cout << std::setw(2) << std::setfill(' ') << id << " => ";
            reverseStack.pop();

            linebreak--;
            counter--;

            if (linebreak == 0) {
                std::cout << std::endl;
                linebreak = 10;
            }
        }

        IndexType id = reverseStack.top();
        std::cout << id << ".";
    }

    template <typename NODE, typename EDGE>
    int NearestNeighbourSolver<NODE, EDGE>::total() {
        return m_totalDistance;
    }
}

void test_01_NearestNeighbour_NFE()
{
    using namespace Solver_NearestNeighbour;
    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    Node<TestNodeDetails> n1{ 0, { std::string("Nbg")} };
    Node<TestNodeDetails> n2{ 1, { std::string("Fth")} };
    Node<TestNodeDetails> n3{ 2, { std::string("Erl")} };

    WeightedEdge<int, TestEdgeDetails> we1{ 0, 1, 10, "" };
    WeightedEdge<int, TestEdgeDetails> we2{ 0, 2, 20, "" };

    WeightedEdge<int, TestEdgeDetails> we3{ 1, 2, 25, "" };
    WeightedEdge<int, TestEdgeDetails> we4{ 1, 0, 10, "" };

    WeightedEdge<int, TestEdgeDetails> we5{ 2, 0, 20, "" };
    WeightedEdge<int, TestEdgeDetails> we6{ 2, 1, 25, "" };

    std::vector<Node<TestNodeDetails>> nodes = {
    n1, n2, n3
    };

    std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
        we1, we2, we3, we4, we5, we6
    };

    // create graph
    GraphAdjList<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(true);
    graph.addNodes(nodes);
    graph.addEdges(edges);

    // create solver
    NearestNeighbourSolver<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> nn;
    nn.setGraph(&graph);
    nn.solve(getId(n1));
    nn.print();
}

void test_01_NearestNeighbour_Fuenf_Staedte()
{
    using namespace Solver_NearestNeighbour;
    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    Node<TestNodeDetails> n1{ 0, { std::string("Nuernberg")} };
    Node<TestNodeDetails> n2{ 1, { std::string("Fuerth")} };
    Node<TestNodeDetails> n3{ 2, { std::string("Erlangen")} };
    Node<TestNodeDetails> n4{ 3, { std::string("Schwaig")} };
    Node<TestNodeDetails> n5{ 4, { std::string("Schwabach")} };

    WeightedEdge<int, TestEdgeDetails> we1{ 0, 1, 10, " bla " };
    WeightedEdge<int, TestEdgeDetails> we2{ 0, 2, 23, " bla " };
    WeightedEdge<int, TestEdgeDetails> we3{ 0, 3,  5, " bla " };
    WeightedEdge<int, TestEdgeDetails> we4{ 0, 4, 20, " bla " };

    WeightedEdge<int, TestEdgeDetails> we5{ 1, 0, 10, " blubber " };
    WeightedEdge<int, TestEdgeDetails> we6{ 1, 2, 15, " blubber " };
    WeightedEdge<int, TestEdgeDetails> we7{ 1, 3, 35, " blubber " };
    WeightedEdge<int, TestEdgeDetails> we8{ 1, 4, 18, " blubber " };

    WeightedEdge<int, TestEdgeDetails> we9{ 2, 0, 23,  " bla " };
    WeightedEdge<int, TestEdgeDetails> we10{ 2, 1, 15, " bla " };
    WeightedEdge<int, TestEdgeDetails> we11{ 2, 3, 25, " bla " };
    WeightedEdge<int, TestEdgeDetails> we12{ 2, 4, 40, " bla " };

    WeightedEdge<int, TestEdgeDetails> we13{ 3, 0, 5,  " blubber " };
    WeightedEdge<int, TestEdgeDetails> we14{ 3, 1, 35, " blubber " };
    WeightedEdge<int, TestEdgeDetails> we15{ 3, 2, 25, " blubber " };
    WeightedEdge<int, TestEdgeDetails> we16{ 3, 4, 30, " blubber " };

    WeightedEdge<int, TestEdgeDetails> we17{ 4, 0, 20, " bla " };
    WeightedEdge<int, TestEdgeDetails> we18{ 4, 1, 18, " bla " };
    WeightedEdge<int, TestEdgeDetails> we19{ 4, 2, 40, " bla " };
    WeightedEdge<int, TestEdgeDetails> we20{ 4, 3, 30, " bla " };

    std::vector<Node<TestNodeDetails>> nodes = {
    n1, n2, n3, n4, n5
    };

    std::vector<WeightedEdge<int, TestEdgeDetails>> edges = {
        we1, we2, we3, we4, we5, we6, we7, we8,we9,we10,we11,
        we12,we13,we14,we15,we16,we17,we18,we19,we20
    };

    // create graph
    GraphAdjList<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(true);
    graph.addNodes(nodes);
    graph.addEdges(edges);

    // print graph with details
    std::cout << "Graph: " << std::endl;
    std::cout << graph.toString() << std::endl;
    std::cout << "Nodes: " << std::endl;
    std::cout << graph.toStringNodes<TestNodeDetails, TestEdgeDetails>() << std::endl;
    std::cout << "Edges: " << std::endl;
    std::cout << graph.toStringEdges<TestNodeDetails, TestEdgeDetails>() << std::endl;

    // create solver
    NearestNeighbourSolver<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> mfr;
    mfr.setGraph(&graph);
    mfr.solve(getId(n1));
    mfr.print();
}

void test_01_NearestNeighbour_TSP(std::string filename)
{
    using namespace Solver_NearestNeighbour;
    using namespace NodeDetailsTest;
    using namespace EdgeDetailsTest;

    // create graph
    GraphAdjList<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> graph(true);
    bool ok = graph.readTSPFile<TestNodeDetails, TestEdgeDetails>(filename);
    if (!ok)
        return;

    std::cout << "Graph from TSP file: " << filename << std::endl;

    // create solver
    NearestNeighbourSolver<Node<TestNodeDetails>, WeightedEdge<int, TestEdgeDetails>> nn;
    nn.setGraph(&graph);
    nn.solve(1);
    std::cout << std::endl;

    std::cout << "Found solution: Tour has length of " << nn.total() << std::endl;
    std::cout << std::endl;
    nn.print();
    std::cout << std::endl;
}


// =====================================================================================
// End-of-File
// =====================================================================================
