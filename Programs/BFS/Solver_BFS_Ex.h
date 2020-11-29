#pragma once

// =====================================================================================
// XXX
// =====================================================================================

namespace Solver_BFS_Ex {

    template <typename EDGE>
    class BFSSolverEx {
    private:
        // interface pointer
        const IGraphEx<EDGE>* m_graph;

        std::deque<IndexType> m_queue;
        std::vector<bool> m_visited;

    public:
        // c'tor
        BFSSolverEx() : m_graph(nullptr) {}

        // public interface
        void setGraph(const IGraphEx<EDGE>*);
        std::vector<std::optional<IndexType>> solve(IndexType start);
        std::vector<IndexType> reconstructPath(IndexType source, IndexType target, std::vector<std::optional<IndexType>> prev);
        void printSolution(std::vector<IndexType> path);

        void reset() {
            m_queue.clear();
            m_visited.clear();
        }
    };

    template <typename EDGE>
    void BFSSolverEx<EDGE>::setGraph(const IGraphEx<EDGE>* graph) {
        m_graph = graph;
    }

    template <typename EDGE>
    std::vector<std::optional<IndexType>> BFSSolverEx<EDGE>::solve(IndexType start) {

        // setup 'm_visited' vector
        m_visited.resize(m_graph->countNodes());
        std::fill(std::begin(m_visited), std::end(m_visited), false);
        m_visited.at(start) = true;

        // setup 'previous' vector
        std::vector<std::optional<IndexType>> previous;
        previous.resize(m_graph->countNodes());
        std::fill(std::begin(previous), std::end(previous), std::nullopt);

        m_queue.push_back(start);
        while (!m_queue.empty()) {

            // dequeue a vertex from queue
            int node = m_queue.front();
            m_queue.pop_front();

            // get all adjacent vertices of the dequeued vertex
            std::vector<IndexType> neighbours = m_graph->getNeighbouringNodes(node);
            for (IndexType next : neighbours) {
                if (!m_visited.at(next)) {
                    m_queue.push_back(next);
                    m_visited.at(next) = true;
                    previous.at(next) = node;
                }
            }
        }

        return previous;
    }

    template <typename EDGE>
    std::vector<IndexType> BFSSolverEx<EDGE>::reconstructPath(IndexType source, IndexType target, std::vector<std::optional<IndexType>> prev) {

        // reconstruct path going backwards from 'target'
        std::vector<IndexType> path;

        for (IndexType pos = target; pos != -1; pos = prev.at(pos).has_value() ? prev.at(pos).value() : -1) {
            path.push_back(pos);
        }

        std::reverse(std::begin(path), std::end(path));

        // if 'source' and 'target' are connected, return the path
        if (path.at(0) == source) {
            return path;
        }
        else {
            return {};
        }
    }

    template <typename EDGE>
    void BFSSolverEx<EDGE>::printSolution(std::vector<IndexType> path) {
        if (path.size() == 0) {
            std::cout << "No Solution found !" << std::endl;
            return;
        }

        std::for_each(std::begin(path), std::end(path) - 1, [](int vertex) {
            std::cout << "[" << vertex << "] => ";
            }
        );

        // print last element without trailing comma :-)
        int vertex = path.at(path.size() - 1);
        std::cout << "[" << vertex << "].";
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
