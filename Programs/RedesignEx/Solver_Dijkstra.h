// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Solver_Dijkstra.h
// =====================================================================================

#pragma once

#include "Graph.h"

#include  <unordered_map>

using namespace Graph_Theory;

template<typename Weight>
using ExtendedEdge = std::pair<size_t, Edge<Weight>>;

template<typename Weight>
size_t getFrom(const ExtendedEdge<Weight>& edge) {
    return std::get<0>(edge);
}

namespace Graph_Theory_Dijkstra
{
    template <typename T, typename W>
    class DijkstraSolver
    {
    private:
        const Graph<T, W>& m_graph;
        std::vector<W> m_distances;

        std::unordered_map<size_t, ExtendedEdge<W>> m_shortestPathMap;

    public:
        DijkstraSolver(const Graph<T, W>& graph) : m_graph{ graph } {}

        bool computeShortestPaths(const T& root) {

            // compute start index
            const size_t first{ m_graph.getIndexOfNode(root) };

            m_distances.resize(m_graph.countNodes());
            m_distances[first] = size_t{};

            std::vector<bool> visited(m_graph.countNodes());
            visited[first] = true;

            // need a lambda to compare weighted edges according to their weight
            auto compareEdges = [](const Edge<W>& lhs, const Edge<W>& rhs) {
                const auto& [vertexLeft, weightLeft] = lhs;
                const auto& [vertexRight, weightRight] = rhs;
                return weightLeft.value() > weightRight.value();
            };

            // need a priority queue
            // note: the third template parameter should be the *type* of the comparison function;
            // the function itself is then passed as a parameter in the constructor of priority_queue!
            std::priority_queue <
                Edge<W>,
                std::vector<Edge<W>>,
                decltype(compareEdges)>
                pq(compareEdges);

            // add source edge to priority queue, distance is 0
            Edge<W> startEdge{ first, W{} };
            pq.push(startEdge);

            // while priority queue isn't empty...
            while (!pq.empty()) {

                // get vertex with minimum weight (distance) from priority queue
                const auto [vertex, weight] = pq.top();
                pq.pop();

                // get all adjacent edges of the dequeued vertex
                const AdjacencyListType<W>& neighbours = m_graph[vertex].getAdjacentNodes();
                
                // examine next edges
                for (const auto& [nextVertex, nextWeight] : neighbours) {

                    // calculate new weight (distance) of current vertex
                    const W pathWeight = nextWeight.value() + m_distances[vertex];

                    // found new node (vertex) or shorter path ...
                    if (! visited[nextVertex] || (m_distances[nextVertex] > pathWeight)) {

                        visited[nextVertex] = true;

                        // update the distance of current vertex
                        m_distances[nextVertex] = pathWeight;

                        // update edge on shortest path
                        Edge<W> nextEdge {nextVertex, pathWeight};
                        ExtendedEdge<W> extendedEdge{vertex, nextEdge};
                        m_shortestPathMap[nextVertex] = extendedEdge;

                        // insert current edge into priority queue
                        pq.push(nextEdge);
                    }
                }
            }

            return true;
        }

        std::vector<size_t> getDistances() {
            return m_distances;
        }

        Path computeShortestPath(const T& startValue, const T& endValue) {

            const size_t start{ m_graph.getIndexOfNode(startValue) };
            const size_t end{ m_graph.getIndexOfNode(endValue) };

            ExtendedEdge<W> edge{ m_shortestPathMap[end] };
            size_t from{ getFrom(edge) };

            Path path{};
            path.insert(path.begin(), from);

            while (getFrom(edge) != start) {

                edge = m_shortestPathMap[getFrom(edge)];
                size_t from{ getFrom(edge) };
                path.insert(path.begin(), from);
            }

            path.push_back(end);

            return path;
        }

        std::string toString(const Path& distances, int width = 0) const {

            std::ostringstream oss;

            for (size_t index = 0; auto distance : distances) {

                const T& value = m_graph[index].value();
                oss << "Distance to " << std::setw(width) << std::left << value << ": ";
                oss << distance << std::endl;

                ++index;
            }

            return oss.str();
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
