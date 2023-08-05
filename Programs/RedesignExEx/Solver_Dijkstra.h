// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Solver_Dijkstra.h
// =====================================================================================

#pragma once

#include "Graph.h"

using namespace Graph_Theory;

namespace Graph_Theory_Dijkstra
{
    // custom function object (functor) to compare weighted edges
    template <typename W>
    struct WeightedTrackComparer
    {
        bool operator() (const Track<W>& l, const Track<W>& r) const {

            const auto& [vertexLeft, weightLeft] = l;
            const auto& [vertexRight, weightRight] = r;
            return weightLeft.value() > weightRight.value();
        }
    };
    
    template <typename T, typename W>
    class DijkstraSolver
    {
    private:
        const Graph<T, W>& m_graph;
        std::vector<W> m_distances;
        std::vector<W> m_previousVertex;

    public:
        DijkstraSolver(const Graph<T, W>& graph) : m_graph{ graph } {}

        bool computeShortestPaths(const T& root) {

            // adjust sizes of vector containers
            m_distances.resize(m_graph.countNodes());
            std::fill(std::begin(m_distances), std::end(m_distances), W{});

            m_previousVertex.resize(m_graph.countNodes());
            std::fill(std::begin(m_previousVertex), std::end(m_previousVertex), W{});

            // compute start index
            const size_t first{ m_graph.getIndexOfNode(root) };
            m_distances[first] = size_t{};

            // helper container to manage already visited nodes
            std::vector<bool> visited(m_graph.countNodes());
            visited[first] = true;

            // need a priority queue for weighted edges
            std::priority_queue <Track<W>, std::vector<Track<W>>, WeightedTrackComparer<W>> pq;

            // add source edge to priority queue, distance is 0
            Track<W> startEdge{ first, W{} };
            pq.push(startEdge);

            // while priority queue isn't empty...
            while (!pq.empty()) {

                // get vertex with minimum weight (distance) from priority queue
                const auto [vertex, weight] = pq.top();
                pq.pop();

                // get all adjacent edges of the dequeued vertex
                const AdjacencyNodesList<W>& neighbours = m_graph[vertex].getAdjacentNodes();
                
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
                        Track<W> nextEdge {nextVertex, pathWeight};

                        // update current 'from' vertex
                        m_previousVertex[nextVertex] = vertex;

                        // insert current edge into priority queue to be examined later
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

            Path path{};

            size_t vertex{ m_previousVertex[end] };
            path.insert(path.begin(), vertex);

            while (vertex != start) {

                vertex = m_previousVertex[vertex];
                path.insert(path.begin(), vertex);
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
