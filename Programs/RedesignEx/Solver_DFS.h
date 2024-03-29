// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Solver_DFS.h
// =====================================================================================

#pragma once

#include "Graph.h"

using namespace Graph_Theory;

namespace Graph_Theory_DFS
{
    template <typename T>
    class DFSSolver
    {
    private:
        const Graph<T>& m_graph;
        std::vector<bool> m_visited;
        std::vector<Path> m_paths;
        Path m_components;
        size_t m_count;

    public:
        DFSSolver(const Graph<T>& graph) : m_graph{ graph }, m_count{} {}

        void computeComponents() {

            // setup 'm_visited' vector
            m_visited.resize(m_graph.countNodes());

            m_components.resize(m_graph.countNodes());
            std::fill(std::begin(m_components), std::end(m_components), 0);

            m_count = 0;

            for (size_t node{}; node != m_graph.countNodes(); ++node) {
                if (!m_visited.at(node)) {
                    ++m_count;
                    depthFirstSearch(node);
                }
            }
        }

        size_t getNumberOfComponents() const { return m_count; }

        Path getComponent(size_t mark) const {

            Path result{};

            for (size_t index{}; size_t node : m_components) {

                if (node == mark) {
                    result.push_back(index);
                }

                ++index;
            }

            return result;
        }

        size_t countFoundPaths() const { return m_paths.size(); }

        // function to perform DFS traversal in a graph to find
        // the complete path between source and target vertices
        bool findPathAny(size_t source, size_t target, Path& path) {

            // setup 'm_visited' vector
            m_visited.resize(m_graph.countNodes());

            return findPathAnyHelper(source, target, path);
        }

        void findPathAll(const T& sourceData, const T& targetData) {

            // compute source index
            const size_t source{ m_graph.getIndexFromNode(sourceData) };

            // compute target index
            const size_t target{ m_graph.getIndexFromNode(targetData) };

            // setup 'm_visited' vector
            m_visited.resize(m_graph.countNodes());

            // setup 'currentPath' vector
            Path currentPath{};
            currentPath.push_back(source);

            findPathAllHelper(source, target, currentPath);
        }

        void printPath(const Path& path) const {

            std::for_each(
                std::begin(path),
                std::prev(std::end(path)),
                [](auto vertex) { std::cout << vertex << " -> "; }
            );

            auto last = path.back();
            std::cout << last << std::endl;
        }

        void printPaths() const {
            for (const auto& path : m_paths) {
                printPath(path);
            }
        }

        Path getShortestPath() const {

            auto result = std::min_element(
                m_paths.begin(),
                m_paths.end(),
                [](const auto& path1, const auto& path2) {
                    return path1.size()  < path2.size();
                }
            );

            return *result;
        }

        std::vector<Path> getShortestPaths() const {

            // calculate length of a shortest path
            auto shortestPath = std::min_element(
                m_paths.begin(),
                m_paths.end(),
                [](const auto& path1, const auto& path2) {
                    return path1.size() < path2.size();
                }
            );

            size_t length{ (*shortestPath).size() };

            std::vector<Path> result{};

            for (const auto& path : m_paths) {

                if (path.size() == length) {
                    result.push_back(path);
                }
            }

            return result;
        }

    private:
        void depthFirstSearch(size_t index) {

            m_visited.at(index) = true;          // mark current node as discovered
            m_components.at(index) = m_count;    // set mark

            // do for all adjacent vertices of the current vertex
            const AdjacencyTrackList<>& neighbours { m_graph[index].getAdjacentTracks() };

            for (const auto& [next, weight] : neighbours) {

                // next is not discovered
                if (!m_visited.at(next)) {

                    depthFirstSearch(next);
                }
            }
        }

        bool findPathAnyHelper(size_t source, size_t target, Path& path) {

            // mark current node as discovered
            m_visited.at(source) = true;

            // include current node in the path
            path.push_back(source);

            // if destination vertex is found
            if (source == target) {
                return true;
            }

            // do for all adjacent vertices of the dequeued vertex
            const GraphNode<T>& sourceNode { m_graph[source] };

            const AdjacencyTrackList<>& neighbours {
                m_graph.getAdjacentTracks(sourceNode.data())
            };

            for (const auto& [next, weight] : neighbours) {

                // next is not discovered
                if (!m_visited.at(next)) {

                    // return true if destination is found
                    if (findPathAnyHelper(next, target, path))
                        return true;
                }
            }

            // backtrack: remove current node from the path
            path.pop_back();

            // return false if destination vertex is not reachable from source
            return false;

        }

        void findPathAllHelper(size_t source, size_t target, Path& path) {

            // mark current node as discovered
            m_visited.at(source) = true;

            // if destination vertex is found
            if (source == target) {

                m_paths.push_back(path); // store found solution
                m_visited.at(source) = false;  // unmark current node as discovered
            }
            else {

                // do for every edge
                const GraphNode<T>& sourceNode{ m_graph[source] };

                const AdjacencyTrackList<>& neighbours {
                    m_graph.getAdjacentTracks(sourceNode.data())
                };

                for (const auto& [index, weight] : neighbours) {

                    // next is not discovered
                    if (!m_visited.at(index)) {
                        path.push_back(index);  // include current node in the path
                        findPathAllHelper(index, target, path);
                        path.pop_back();        // remove current node from the path (backtrack)
                    }
                }

                // unmark current node as discovered
                m_visited.at(source) = false;
            }
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
