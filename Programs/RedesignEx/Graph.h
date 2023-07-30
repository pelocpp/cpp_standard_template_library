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

#include "GraphNode.h"

// =====================================================================================

namespace Graph_Theory
{
    enum class Direction { Directed, Undirected };

    enum class Weight { Weighted, Unweighted };

    template<typename T, typename W>
    using NodesContainerType = std::vector<GraphNode<T, W>>;

    using Path = std::vector<size_t>;

    // --------------------------------------------------------------------------------

    template<typename T, typename W = EmptyType>
    class Graph
    {
    private:
        NodesContainerType<T, W> m_nodes;
        Direction m_isDirected;
        Weight m_isWeighted;

    public:
        // c'tors
        Graph() : Graph{ Direction::Directed, Weight::Unweighted } {}

        Graph(Direction isDirected, Weight isWeighted = Weight::Unweighted) {
            m_isDirected = isDirected;
            m_isWeighted = isWeighted;
        }

    public:
        // getter / setter
        Direction isDirected() const noexcept {
            return m_isDirected;
        }

        Weight isWeighted() const noexcept {
            return m_isWeighted; 
        }

        size_t countNodes() const noexcept
        {
            return m_nodes.size();
        }

        size_t countEdges() const
        {
            size_t count{};

            for (const auto& node : m_nodes) {
                const auto countEdges = node.count();
                count += countEdges;
            }

            return count;
        }

        // operators
        GraphNode<T, W>& operator[](size_t index)
        {
            return m_nodes[index];  // no bounds checking
        }

        const GraphNode<T, W>& operator[](size_t index) const
        {
            return m_nodes[index];
        }

        // public interface
        void addNodes(const std::initializer_list<T> list) {

            for (const auto& node : list) {
                addNode(node);
            }

            // TODO: Entfernen !!!
    //        sort();
        }

        template<class InputIt>
        void addNodes(InputIt first, InputIt last) {

            for (; first != last; ++first) {
                addNode(*first);
            }

            sort();
        }

        // TODO: Allgemein: Es müssen / sollten 2 Varianten an Methoden vorhanden sein:
        // addEdge mit Indices
        // addEdge mit Werten von Knoten
        // Oder auch nicht ...


        bool addEdges(const std::initializer_list<std::pair<T, T>> list) {

            bool totalResult{ true };

            for (const auto& [from, to] : list) {

                bool result = addEdge(from, to);
                totalResult = totalResult && result;
            }

            return totalResult;
        }


        // returns true if the edge was successfully created
        bool addEdge(const T& fromNode, const T& toNode)
        {
            if (m_isWeighted == Weight::Weighted) {
                throw std::logic_error("Graph should be unweighted!");
            }

            const auto from{ findNode(fromNode) };

            const auto to{ findNode(toNode) };

            if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
                return false;
            }

            const size_t toIndex{ getIndexOfNode(to) };

            AdjacencyListType<W>& fromList = from->getAdjacentNodes();

            Edge<W> edge{toIndex, std::nullopt};

            auto [pos, succeeded] = fromList.insert(edge);

            if (succeeded) {

                if (m_isDirected == Direction::Undirected) {

                    GraphNode<T, W>& target = m_nodes[toIndex];

                    AdjacencyListType<W>& toList = target.getAdjacentNodes();

                    const size_t fromIndex{ getIndexOfNode(from) };

                    Edge<W> edge{fromIndex, std::nullopt};

                    auto [pos, succeeded] = toList.insert(edge);

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

            if (m_isWeighted == Weight::Unweighted) {
                throw std::logic_error("Graph should be weighted!");
            }

            const auto from{ findNode(fromNode) };

            const auto to{ findNode(toNode) };

            if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
                return false;
            }

            const size_t toIndex{ getIndexOfNode(to) };

            AdjacencyListType<W>& fromList = from->getAdjacentNodes();

            Edge<W> edge{toIndex, weight};

            auto [pos, succeeded] = fromList.insert(edge);

            if (succeeded) {

                if (m_isDirected == Direction::Undirected) {

                    GraphNode<T, W>& target = m_nodes[toIndex];

                    AdjacencyListType<W>& toList = target.getAdjacentNodes();

                    const size_t fromIndex{ getIndexOfNode(from) };

                    Edge<W> edge{fromIndex, weight};

                    auto [pos, succeeded] = toList.insert(edge);

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

        AdjacencyListType<W>& getAdjacentNodes(const T& node_value)
        {
            static AdjacencyListType<W> empty {};

            auto node{ findNode(node_value) };

            if (node == std::end(m_nodes)) {

                return empty;
            }

            return node->getAdjacentNodes();
        }

        const AdjacencyListType<W>& getAdjacentNodes(const T& node_value) const
        {
            return const_cast<Graph<T, W>*>(this)->getAdjacentNodes(node_value);
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
        size_t getIndexOfNode(const typename NodesContainerType<T, W>::const_iterator& node) const noexcept
        {
            const auto index{ std::distance(std::cbegin(m_nodes), node) };

            return static_cast<size_t>(index);
        }

    public:
        size_t getIndexOfNode(const T& value) const
        {
            const auto position{ findNode(value) };

            if (position == m_nodes.end()) {
                throw std::invalid_argument("Node with specified value not found!");
            }

            const auto index{ std::distance(std::cbegin(m_nodes), position) };

            return static_cast<size_t>(index);
        }

        // eher nicht benötigt - ich arbeite nicht Index Orientiert ...................
        //T getNodeData(size_t index) {
        //    return m_nodes[index].value();
        //}

        std::string toString(int width = 0) const {

            bool isDirected = this->isDirected() == Direction::Directed;
            bool isWeighted = this->isWeighted() == Weight::Weighted;

            std::string separator{ isDirected ? "->" : "<=>" };

            std::ostringstream oss;
            oss << "Graph: ";
            oss << "Nodes: " << countNodes() << ", Edges: " << countEdges();
            oss << " // " << (isDirected ? "Directed" : "Undirected");
            oss << " - " << (isWeighted ? "Weighted" : "Unweighted") << std::endl << std::endl;

            for (const GraphNode<T, W>& node : m_nodes) {

                const T& fromValue = node.value();

                oss << "[" << std::setw(width) << std::right << fromValue << "]";

                const AdjacencyListType<W>& list = getAdjacentNodes(fromValue);

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

                std::string arrow = isDirected() == Direction::Directed ? " -> " : " => ";

                for (size_t index{}; index != path.size(); ++index) {

                    const T& value{ m_nodes[path[index]].value() };

                    oss << '[' << value << ']';

                    if (index < path.size() - 1) {

                        oss << arrow;

                        const GraphNode<T, W>& node = m_nodes[path[index]];
                        
                        const auto& [to, weight] = node.getEdge(path[index + 1]);

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

            oss << "\nTotal Distance: " << totalWeight << '.';

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
            return true;
        }

        void sort() {

            std::sort(
                std::begin(m_nodes),
                std::end(m_nodes)
            );
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
