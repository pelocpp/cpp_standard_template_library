// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Solver_BFS.h
// =====================================================================================

#pragma once

#include "Graph.h"

using namespace Graph_Theory;

namespace Graph_Theory_BFS
{
    template <typename T>
    class BFSSolver
    {
    private:

        // TODO: zu klären: Ist dieser Algo für gerichtete oder ungerichtete Graphen ???? !!!!!!!!!!

        Graph<T>& m_graph;  
        std::deque<size_t> m_queue;
        std::vector<bool> m_visited;

    public:
        BFSSolver(Graph<T>& graph) : m_graph{ graph } {}

        std::vector<std::optional<size_t>> solve(size_t start) {

            // setup 'm_visited' vector
            m_visited.resize(m_graph.countNodes());
            std::fill(std::begin(m_visited), std::end(m_visited), false);
            m_visited.at(start) = true;

            // setup 'previous' vector
            std::vector<std::optional<size_t>> previous(m_graph.countNodes());
            std::fill(std::begin(previous), std::end(previous), std::nullopt);

            m_queue.push_back(start);
            while (!m_queue.empty()) {

                // dequeue a vertex from queue
                size_t vertex{ m_queue.front() };
                m_queue.pop_front();

                // get all adjacent vertices of the dequeued vertex
                // std::vector<size_t> neighbours{ m_graph.getNeighbouringNodes(vertex) };

                // do for all adjacent vertices of the current vertex
                const AdjacencyListType<>& neighbours = m_graph[vertex].getAdjacentNodes();

                for (const auto& [next, weight] : neighbours) {
                //for (size_t next : neighbours) {
                    if (!m_visited.at(next)) {
                        m_queue.push_back(next);
                        m_visited.at(next) = true;
                        previous.at(next) = vertex;
                    }
                }
            }

            return previous;
        }

        std::vector<size_t> reconstructPath(size_t source, size_t target, std::vector<std::optional<size_t>> prev) {

            std::vector<size_t> path;
            bool done{ false };
            size_t pos{ target };

            // reconstruct path going backwards from 'target'
            while (!done) {
                path.push_back(pos);
                if (prev.at(pos).has_value()) {
                    pos = prev.at(pos).value();
                }
                else {
                    done = true;
                }
            }

            // need to reverse the constructed path
            std::reverse(std::begin(path), std::end(path));

            // if 'source' and 'target' are connected, return the path
            return (path.at(0) == source) ? path : std::vector<size_t>{};
        }

        void printSolution(std::vector<size_t> path) {
            if (path.size() == 0) {
                std::cout << "No Solution found !" << std::endl;
            }
            else {
                std::for_each(
                    std::begin(path),
                    std::prev(std::end(path)),
                    [&](size_t vertex) {
                        //  std::cout << "[" << vertex << "] => ";

                        const GraphNode<T>& node{ m_graph[vertex] };

                        const T& description = node.value();

                        // std::optional<T> description{ m_graph.getNodeDescription(vertex) };  

                        // if (description.has_value()) {

                            using TNodeType = std::remove_cv<T>::type;

                            if constexpr (!std::is_same<TNodeType, std::string>::value) {
                                std::string s{ std::to_string(description) };
                                std::cout << "[" << s << "] => ";
                            }
                            else {
                                std::cout << "[" << description << "] => ";
                            }


                            // std::cout << "[" << vertex << "] => ";
                        //}
                        //else {
                        //    std::cout << "[" << vertex << "] => ";
                        //}
                    }
                );

                // print last element without trailing comma :-)
                size_t vertex = path.back();
                // TODO: Hmmm, da muss man jetzt dieselbe std::optional Umwandlung machen wir kurz zuvor... das ist lästing
                // Da könnte man eine Methode konzipieren, die ein std::pair zurückliefert ... und structured binding verwendet....
                std::cout << "[" << vertex << "].";
            }
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
