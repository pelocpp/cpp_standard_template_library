// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Graph.h
// =====================================================================================

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <deque>
#include <utility>
#include <algorithm>
#include <optional>
#include <queue>
#include <type_traits>
#include <string_view>
#include <format>
#include <optional>
#include <stdexcept>
#include <cstddef>

#include "Graph_Common.h"
#include "Graph_Node.h"

// =====================================================================================

namespace Graph_Theory
{
    // Hmmm, hätte diese Typen alle gerne zentral gehabt ... das geht auf Grund von GraphNode eher hier nicht ....
    template<typename T, typename W>
    using NodesContainerType = std::vector<GraphNode<T, W>>;

    template<typename T, typename W = EmptyType>
    class Graph
    {
    private:
        NodesContainerType<T, W> m_nodes;
        Direction m_direction;
        Weight m_weight;

    public:
        // c'tors
        Graph() : Graph{ Direction::Directed, Weight::Unweighted } {}

        Graph(Direction direction, Weight weight = Weight::Unweighted) {
            m_direction = direction;
            m_weight = weight;
        }

    public:
        // getter / setter
        bool isDirected() const noexcept {
            return m_direction == Direction::Directed;
        }

        bool isWeighted() const noexcept {
            return m_weight == Weight::Weighted;
        }

        size_t countNodes() const noexcept {
            return m_nodes.size();
        }

        size_t countEdges() const {
            size_t count{};
            for (const auto& node : m_nodes) {
                const auto countEdges = node.count();
                count += countEdges;
            }
            return count;
        }

        // operators
        GraphNode<T, W>& operator[](size_t index) {
            return m_nodes[index];  // no bounds checking
        }

        const GraphNode<T, W>& operator[](size_t index) const {
            return m_nodes[index];
        }

        // public interface
        void addNodes(const std::initializer_list<T> list) {

            for (const auto& node : list) {
                addNode(node);
            }
        }

        template<class InputIt>
        void addNodes(InputIt first, InputIt last) {

            for (; first != last; ++first) {
                addNode(*first);
            }
        }

        // returns true if the edge was successfully created
        bool addEdge(const T& fromNode, const T& toNode) {

            if (m_weight == Weight::Weighted) {
                throw std::logic_error("Graph should be unweighted!");
            }

            const auto from{ findNode(fromNode) };

            const auto to{ findNode(toNode) };

            if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
                return false;
            }

            const size_t toIndex{ getIndexFromNode(to) };

            Track<W> track{toIndex, std::nullopt};

            AdjacencyTrackList<W>& fromList = from->getAdjacentTracks();

            auto [pos, succeeded] = fromList.insert(track);

            if (succeeded) {

                if (m_direction == Direction::Undirected) {

                    GraphNode<T, W>& target = m_nodes[toIndex];

                    const size_t fromIndex{ getIndexFromNode(from) };

                    AdjacencyTrackList<W>& toList = target.getAdjacentTracks();

                    Track<W> track{fromIndex, std::nullopt};

                    auto [pos, succeeded] = toList.insert(track);

                    return succeeded;
                }
                else {
                    return true;
                }
            }
            else {
                return false;
            }
        }

        // TODO: Klären, ob das geht: das mit std::nullopt
        // bool addEdge(const T& fromNode, const T& toNode, const W& weight = std::nullopt) {
        // Dann ist das nur noch eine Methode !!!!!!!!!!!!!!!!!!!!

        bool addEdge(const T& fromNode, const T& toNode, const W& weight) {

            if (m_weight == Weight::Unweighted) {
                throw std::logic_error("Graph should be weighted!");
            }

            const auto from{ findNode(fromNode) };

            const auto to{ findNode(toNode) };

            if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
                return false;
            }

            const size_t toIndex{ getIndexFromNode(to) };

            Track<W> track{toIndex, weight};

            AdjacencyTrackList<W>& fromList = from->getAdjacentTracks();

            auto [pos, succeeded] = fromList.insert(track);

            if (succeeded) {

                if (m_direction == Direction::Undirected) {

                    GraphNode<T, W>& target = m_nodes[toIndex];

                    const size_t fromIndex{ getIndexFromNode(from) };

                    Track<W> track{fromIndex, weight};

                    AdjacencyTrackList<W>& toList = target.getAdjacentTracks();

                    auto [pos, succeeded] = toList.insert(track);

                    return succeeded;
                }
                else {
                    return true;
                }
            }
            else {
                return false;
            }
        }

        bool addEdges(const std::initializer_list<std::pair<T, T>> list) {

            bool totalResult{ true };

            for (const auto& [from, to] : list) {

                bool result = addEdge(from, to);
                totalResult = totalResult && result;
            }

            return totalResult;
        }

        bool addEdges(const std::initializer_list<std::tuple<T, T, W>> list) {

            bool totalResult{ true };

            for (const auto& [from, to, weight] : list) {

                bool result = addEdge(from, to, weight);
                totalResult = totalResult && result;
            }

            return totalResult;
        }

        AdjacencyTrackList<W>& getAdjacentTracks(const T& node_value)
        {
            static AdjacencyTrackList<W> empty {};

            auto node{ findNode(node_value) };

            if (node == std::end(m_nodes)) {

                return empty;
            }

            return node->getAdjacentTracks();
        }

        const AdjacencyTrackList<W>& getAdjacentTracks(const T& node_value) const
        {
            return const_cast<Graph<T, W>*>(this)->getAdjacentTracks(node_value);
        }


        // Neu - for Kruskal needed
        //std::vector<Edge<Weight>> getAllEdges() const {

        //    std::vector<WeightedEdge<Weight>> edges;

        //    for (size_t row = 0; const auto & vertices : m_adjacencyList) {
        //        for (size_t column = 0; auto entry : vertices) {
        //            if (entry.has_value()) {
        //                edges.push_back({ row, column, entry.value() });
        //            }
        //            ++column;
        //        }
        //        ++row;
        //    }
        //    return edges;
        //}


        // TO BE DONE: Das muss DRINGEND mit einem Iterator == Lazy gemacht werden !!!!

        std::vector<Edge<W>> getAllEdges() const {

            std::vector<Edge<W>> edges;

            for (size_t source{}; const GraphNode<T, W>&node : m_nodes) {

                const AdjacencyTrackList<W>& list = node.getAdjacentTracks();

                for (size_t target = 0; const auto& entry : list) {

                    //if (entry.has_value()) {
                    //    edges.push_back({ row, column, entry.value() });
                    //}

                    Edge<W> edge { source, getTrackTarget(entry), getTrackWeight(entry) };

                    edges.push_back(edge);

                    ++target;
                }
                ++source;
            }

            return edges;
        }

    private:
        // Helper method to return an iterator to the given node,
        // or the end iterator if the given node is not in the graph.
        typename NodesContainerType<T, W>::iterator findNode(const T& node_value)
        {
            return std::find_if(
                std::begin(m_nodes),
                std::end(m_nodes),
                [&node_value](const auto& node) {
                    return node.value() == node_value;
                }
            );
        }

        typename NodesContainerType<T, W>::const_iterator findNode(const T& node_value) const
        {
            return const_cast<Graph<T, W>*>(this)->findNode(node_value);
        }

        // given an iterator to a node, returns the index of that node in the nodes container
        size_t getIndexFromNode(const typename NodesContainerType<T, W>::const_iterator& position) const noexcept
        {
            const GraphNode<T, W>& node = *position;

            return node.getIndex();
        }

    public:
        size_t getIndexFromNode(const T& value) const
        {
            const auto position{ findNode(value) };

            if (position == m_nodes.end()) {
                throw std::invalid_argument("Node with specified value not found!");
            }

            const GraphNode<T, W>& node = *position;

            return node.getIndex();
        }

        // brauche ich da beide Versionen
        T getNodeData(size_t index) {
            return m_nodes[index].value();
        }

        const T& getNodeData(size_t index) const {
            return m_nodes[index].value();
        }

        std::string toString(int width = 0) const {

            std::string separator{ isDirected() ? "->" : "<=>" };

            std::ostringstream oss;
            oss << "Graph: ";
            oss << "Nodes: " << countNodes() << ", Edges: " << countEdges();
            oss << " // " << (isDirected() ? "Directed" : "Undirected");
            oss << " - " << (isWeighted() ? "Weighted" : "Unweighted") << std::endl << std::endl;

            for (const GraphNode<T, W>& node : m_nodes) {

                const T& fromValue = node.value();

                oss << "[" << std::setw(width) << std::right << fromValue << "]";

                const AdjacencyTrackList<W>& list = getAdjacentTracks(fromValue);

                if (list.size() != 0) {

                    oss << " " << separator << " [";

                    for (size_t n{}; const auto& [to, weight] : list)
                    {
                        const T& toValue = m_nodes[to].value();
                        oss << toValue;

                        if (weight.has_value()) {
                            oss << " {" << weight.value() << "}";
                        }

                        if (n != list.size() - 1) {
                            oss << ", ";
                        }

                        ++n;
                    }

                    oss << "]";
                }

                oss << std::endl;
            }

            return oss.str();
        }

        std::string toString(const Path& path) const {

            W totalWeight{};

            std::ostringstream oss;

            if (path.size() == 0) {

                oss << "Empty Path!";
            }
            else {

                std::string arrow = isDirected() ? " -> " : " => ";

                for (size_t index{}; index != path.size(); ++index) {

                    const T& value{ m_nodes[path[index]].value() };

                    oss << '[' << value << ']';

                    if (index < path.size() - 1) {

                        oss << arrow;

                        const GraphNode<T, W>& node = m_nodes[path[index]];
                        
                        const auto& [to, weight] = node.getTrack(path[index + 1]);

                        if constexpr (! std::is_same<W, EmptyType>::value)
                        {
                            if (weight.has_value()) {
                                oss << "{" << weight.value() << "} ";

                                // HIER: Concept definieren: Auf Weight muss +  gehen ... oder +=
                                totalWeight = totalWeight + weight.value();
                            }
                        }
                    }
                }
            }

            if constexpr (!std::is_same<W, EmptyType>::value)
            {
                oss << "\nTotal Distance: " << totalWeight << '.';
            }

            return oss.str();
        }

    private:
        bool addNode(const T& data) {

            auto iter{ findNode(data) };

            if (iter != std::end(m_nodes)) {
                // value is already in the graph, return false
                return false;
            }

            T copy{ data };
            m_nodes.emplace_back(std::move(copy));

            size_t size = m_nodes.size();
            m_nodes[size - 1].setIndex(size - 1);

            return true;
        }
    };


}

// =====================================================================================
// End-of-File
// =====================================================================================
