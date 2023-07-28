// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Solver_Dijkstra.h
// =====================================================================================

#pragma once

#include "Graph.h"

using namespace Graph_Theory;

// TODO
// Lesen:
// https://stackoverflow.com/questions/1667963/how-portable-is-casting-1-to-an-unsigned-type

constexpr size_t MaxSize = static_cast<size_t>(-1);

namespace Graph_Theory_Dijkstra
{
    template <typename T, typename W>
    class DijkstraSolver
    {
    private:
        const Graph<T, W>& m_graph;
        size_t m_start;

    public:
        DijkstraSolver(const Graph<T, W>& graph) : m_graph{ graph }, m_start{} {}

        std::vector<size_t> computeShortestPaths(size_t startVertex) {

            std::vector<size_t> distances;

            m_start = startVertex;
            distances.resize(m_graph.countNodes());

            // initialize all possible distances as infinite (-1)
            std::fill(std::begin(distances), std::end(distances), MaxSize);

            // need a lambda to compare Edge elements according to their weight
            auto compareTracks = [](const Edge<size_t>& lhs, const Edge<size_t>& rhs) {
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
                decltype(compareTracks)>
                pq(compareTracks);

            // add source track to priority queue, distance is 0
            Edge<W> startTrack{ m_start, W{} };
            pq.push(startTrack);

            distances[m_start] = size_t{};

            // while priority queue isn't empty...
            while (!pq.empty()) {

                // get minimum distance vertex from priority queue - we call it 'vertex'
                const auto [vertex, weight] = pq.top();
                pq.pop();

                // get all adjacent edges of the dequeued vertex
                const AdjacencyListType<W>& neighbours = m_graph[vertex].getAdjacentNodes();

                for (const auto& [target, weight] : neighbours) {

                    // if the distance to 'target' is shorter by going through 'index' ...
                    if (distances[target] == MaxSize || distances[target] > distances[vertex] + weight.value()) {

                        // update the distance of 'target'
                        distances[target] = distances[vertex] + weight.value();

                        // insert 'target' into the priority queue
                        Edge<W> edge{target, distances[target]};
                        pq.push(edge);
                    }
                }
            }

            return distances;
        }

        void printDistances(const std::vector<size_t>& distances) {

            std::cout << "Printing the shortest paths for Node " << m_start << ':' << std::endl;

            for (size_t index = 0; auto distance : distances) {

                std::cout
                << "Distance from " << m_start
                << " to " << index << " is: "
                << distance << std::endl;

                ++index;
            }
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
