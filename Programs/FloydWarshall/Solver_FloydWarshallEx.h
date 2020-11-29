#pragma once
// =====================================================================================
// Solver_FloydWarshall
// =====================================================================================

namespace SolverFloydWarshallEx {

    template <typename EDGE>
    class FloydWarshallSolverEx {

    private:
        const IGraphEx<EDGE>* m_graph;
        std::vector<std::vector<int>> m_floyd;

        std::vector<std::vector<int>> mat_distances;
        std::vector<std::vector<int>> mat_nodes_before;

    public:
        // c'tor
        FloydWarshallSolverEx() : m_graph{ nullptr } {}

        // public interface
        void setGraph(const IGraphEx<EDGE>*);
        void solve();
        void printPath(IndexType from, IndexType to);

    private:
        void printPathEx(IndexType from, IndexType to);
    };

    template <typename EDGE>
    void FloydWarshallSolverEx<EDGE>::setGraph(const IGraphEx<EDGE>* graph) {
        m_graph = graph;
    }

    template <typename EDGE>
    void FloydWarshallSolverEx<EDGE>::solve() {

        constexpr int infinite = std::numeric_limits<int>::max();

        // setup 2-dim arrays
        int numNodes = m_graph->countNodes();
        mat_distances = std::vector<std::vector<int>>(numNodes, std::vector<int>(numNodes, infinite));
        mat_nodes_before = std::vector<std::vector<int>>(numNodes, std::vector<int>(numNodes, -1));

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
    }

    template <typename EDGE>
    void FloydWarshallSolverEx<EDGE>::printPath(IndexType from, IndexType to) {

        // NODE start = m_graph->getNode(from);
        IndexType start = from;

        std::cout << "von Stadt: " << from << std::endl;

        printPathEx(from, to);

        std::cout << "nach Stadt: " << to << std::endl;

        std::cout << "macht Kilometer: " << mat_distances[from][to] << std::endl;
    }

    template <typename EDGE>
    void FloydWarshallSolverEx<EDGE>::printPathEx(IndexType from, IndexType to) {

        int k;

        k = mat_nodes_before[from][to];
        if (k == -1) {   //  PeLo  ist das -1 okay ???
            return;
        }

        printPathEx(from, k);
        std::cout << " ==> " << k << std::endl;
        printPathEx(k, to);
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
