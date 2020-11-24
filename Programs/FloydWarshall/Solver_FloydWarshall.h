// =====================================================================================
// Solver_FloydWarshall
// =====================================================================================

namespace SolverFloydWarshall {

    template <typename NODE, typename EDGE>
    class FloydWarshallSolver {

    private:
        const IGraph <NODE, EDGE>* m_graph;
        std::vector<std::vector<int>> m_floyd;

    public:
        // c'tor
        FloydWarshallSolver() : m_graph{ nullptr } {}

        // public interface
        void setGraph(const IGraph<NODE, EDGE>*);
        void solve();
        int total();
        void print();
    };

    template <typename NODE, typename EDGE>
    void FloydWarshallSolver<NODE, EDGE>::setGraph(const IGraph<NODE, EDGE>* graph) {
        m_graph = graph;
    }

    template <typename NODE, typename EDGE>
    void FloydWarshallSolver<NODE, EDGE>::solve() {

        int infinite = std::numeric_limits<int>::max();

        // setup 2-dim arrays
        int numNodes = m_graph->countNodes();
        std::vector<std::vector<int>> mat_distances(numNodes, std::vector<int>(numNodes, infinite));
        std::vector<std::vector<int>> mat_nodes_before(numNodes, std::vector<int>(numNodes, -1));

        // fill 2-dim array with the distance from the i-th node to the j-th node
        // (if there is no path from i-th node to the j-th node, the cell is left as infinity)
        std::vector<EDGE> edges = m_graph->getAllEdges();
        for (const EDGE& edge : edges) {
            IndexType row = getSource(edge);
            IndexType col = getTarget(edge);
            auto distance = getWeightEx(edge);
            mat_distances[row][col] = distance;
        }

        // need to set the distance from all nodes to itself to zero
        for (int i = 0; i < numNodes; ++i) {
            mat_distances[i][i] = 0;
        }

        // now applying Floyd-Warshall algorithm
        for (int k = 0; k < numNodes; k++) {
            for (int i = 0; i < numNodes; i++) {
                for (int j = 0; j < numNodes; j++) {

                    if (mat_distances[i][k] == infinite) continue;
                    if (mat_distances[k][j] == infinite) continue;

                    if (mat_distances[i][k] + mat_distances[k][j] < mat_distances[i][j]) {
                        mat_distances[i][j] = mat_distances[i][k] + mat_distances[k][j];
                        mat_nodes_before[i][j] = k;
                    }
                }
            }
        }



        int dummy = 99;


    }

}

// =====================================================================================
// End-of-File
// =====================================================================================
