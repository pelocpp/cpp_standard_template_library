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
        const Graph<T>& m_graph;
        std::deque<size_t> m_queue;
        std::vector<bool> m_visited;

    public:
        BFSSolver(const Graph<T>& graph) : m_graph{ graph } {}

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

                // do for all adjacent vertices of the current vertex
                const AdjacencyNodesList<>& neighbours{ m_graph[vertex].getAdjacentNodes() };

                for (const auto& [next, weight] : neighbours) {

                    if (!m_visited.at(next)) {

                        m_queue.push_back(next);
                        m_visited.at(next) = true;
                        previous.at(next) = vertex;
                    }
                }
            }

            return previous;
        }

        Path reconstructPath(size_t source, size_t target, std::vector<std::optional<size_t>> prev) const {

            Path path;
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
            return (path.at(0) == source) ? path : Path{};
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
