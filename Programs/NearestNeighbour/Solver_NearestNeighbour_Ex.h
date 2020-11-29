#pragma once
// =====================================================================================
// Solver_NearestNeighbour
// =====================================================================================

namespace Solver_NearestNeighbour_Ex {

    template <typename EDGE>
    class NearestNeighbourSolverEx {
    private:
        const IGraphEx <EDGE>* m_graph;
        std::stack<IndexType> m_stack;
        int m_totalDistance;

    public:
        // c'tor
        NearestNeighbourSolverEx() : m_graph{ nullptr }, m_totalDistance{ 0 } {}

        // public interface
        void setGraph(const IGraphEx<EDGE>*);
        void solve(IndexType start);
        int total();
        void print();
    };

    template <typename EDGE>
    void NearestNeighbourSolverEx<EDGE>::setGraph(const IGraphEx<EDGE>* graph) {
        m_graph = graph;
    }

    template <typename EDGE>
    void NearestNeighbourSolverEx<EDGE>::solve(IndexType start) {
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
            std::optional<int> min(std::nullopt);
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

    template <typename EDGE>
    void NearestNeighbourSolverEx<EDGE>::print() {

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

    template <typename EDGE>
    int NearestNeighbourSolverEx<EDGE>::total() {
        return m_totalDistance;
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
