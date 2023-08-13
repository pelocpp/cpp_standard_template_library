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
        // adding STL support 
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;

        // c'tors
        Graph();
        Graph(Direction direction, Weight weight = Weight::Unweighted);

        // getter / setter
        bool isDirected() const noexcept;
        bool isWeighted() const noexcept;

        size_t countNodes() const noexcept;
        size_t countEdges() const;

        T& getDataFromNode(size_t index);
        const T& getDataFromNode(size_t index) const;

        size_t getIndexFromNode(const T& value) const;

        // operators
        GraphNode<T, W>& operator[](size_t index);
        const GraphNode<T, W>& operator[](size_t index) const;

        // public interface
        void addNodes(const std::initializer_list<T> list);

        template<class InputIt>
        void addNodes(InputIt first, InputIt last);

        // returns true if the edge was successfully created
        bool addEdge(const T& fromValue, const T& toValue);
        bool addEdge(const T& fromValue, const T& toValue, const W& weight);

        bool addEdges(const std::initializer_list<std::pair<T, T>> list);
        bool addEdges(const std::initializer_list<std::tuple<T, T, W>> list);

        const AdjacencyTrackList<W>& getAdjacentTracks(const T& value) const;

        // Neu - for Kruskal needed
        // TO BE DONE: Das muss DRINGEND mit einem Iterator == Lazy gemacht werden !!!!
        std::vector<Edge<W>> getAllEdges() const;

        std::string toString(int width = 0) const;
        std::string toStringRaw(int width = 0) const;
        std::string toString(const Path& path) const;

    private:
        // helper methods
        GraphNode<T, W>& findNode(const T& value);
        const GraphNode<T, W>& findNode(const T& value) const;

        bool contains(const T& data) const;
        bool addNode(const T& data);
    };

    // ---------------------------------------------------------------------------------
    // implementation

    // c'tors
    template<typename T, typename W>
    Graph<T, W>::Graph() : Graph<T, W>::Graph{ Direction::Directed, Weight::Unweighted } {}

    template<typename T, typename W>
    Graph<T, W>::Graph(Direction direction, Weight weight) {
        m_direction = direction;
        m_weight = weight;
    }

    // getter / setter
    template<typename T, typename W>
    bool Graph<T, W>::isDirected() const noexcept {
        return m_direction == Direction::Directed;
    }

    template<typename T, typename W>
    bool Graph<T, W>::isWeighted() const noexcept {
        return m_weight == Weight::Weighted;
    }

    template<typename T, typename W>
    size_t Graph<T, W>::countNodes() const noexcept {
        return m_nodes.size();
    }

    template<typename T, typename W>
    size_t Graph<T, W>::countEdges() const {
        size_t count{};
        for (const auto& node : m_nodes) {
            const auto countEdges = node.count();
            count += countEdges;
        }
        return count;
    }

    template<typename T, typename W>
    T& Graph<T, W>::getDataFromNode(size_t index)
    {
        return const_cast<T&>(static_cast<const Graph<T, W>&>(*this).getDataFromNode(index));
    }

    template<typename T, typename W>
    const T& Graph<T, W>::getDataFromNode(size_t index) const
    {
        return m_nodes[index].data();
    }

    template<typename T, typename W>
    size_t Graph<T, W>::getIndexFromNode(const T& value) const
    {
        const GraphNode<T, W>& node{ findNode(value) };
        return node.getIndex();
    }

    // operators
    template<typename T, typename W>
    GraphNode<T, W>& Graph<T, W>::operator[](size_t index) {
        return m_nodes[index];  // no bounds checking
    }

    template<typename T, typename W>
    const GraphNode<T, W>& Graph<T, W>::operator[](size_t index) const {
        return m_nodes[index];
    }

    // public interface
    template<typename T, typename W>
    void Graph<T, W>::addNodes(const std::initializer_list<T> list) {

        for (const auto& node : list) {
            addNode(node);
        }
    }

    template<typename T, typename W>
    template<class InputIt>
    void Graph<T, W>::addNodes(InputIt first, InputIt last) {

        for (; first != last; ++first) {
            addNode(*first);
        }
    }

    template<typename T, typename W>
    bool Graph<T,W>::addEdge(const T& fromValue, const T& toValue) {

        if (m_weight == Weight::Weighted) {
            throw std::logic_error("Graph should be unweighted!");
        }

        GraphNode<T, W>& from{ findNode(fromValue) };

        GraphNode<T, W>& to{ findNode(toValue) };

        size_t toIndex{ to.getIndex() };

        Track<W> track{toIndex, std::nullopt};

        AdjacencyTrackList<W>& fromList = from.getAdjacentTracks();

        auto [pos, succeeded] = fromList.insert(track);

        if (succeeded) {

            if (m_direction == Direction::Undirected) {

                GraphNode<T, W>& target = m_nodes[toIndex];

                size_t fromIndex{ from.getIndex() };

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

    template<typename T, typename W>
    bool Graph<T, W>::addEdge(const T& fromValue, const T& toValue, const W& weight)
    {
        if (m_weight == Weight::Unweighted) {
            throw std::logic_error("Graph should be Weighted!");
        }

        GraphNode<T, W>& from{ findNode(fromValue) };

        GraphNode<T, W>& to{ findNode(toValue) };

        size_t toIndex{ to.getIndex() };

        Track<W> track{ toIndex, weight };

        AdjacencyTrackList<W>& fromList = from.getAdjacentTracks();

        auto [pos, succeeded] = fromList.insert(track);

        if (succeeded) {

            if (m_direction == Direction::Undirected) {

                GraphNode<T, W>& target = m_nodes[toIndex];

                const size_t fromIndex{ from.getIndex() };

                Track<W> track{ fromIndex, weight };

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

    template<typename T, typename W>
    bool Graph<T, W>::addEdges(const std::initializer_list<std::pair<T, T>> list) {

        bool totalResult{ true };

        for (const auto& [from, to] : list) {

            bool result = addEdge(from, to);
            totalResult = totalResult && result;
        }

        return totalResult;
    }

    template<typename T, typename W>
    bool Graph<T, W>::addEdges(const std::initializer_list<std::tuple<T, T, W>> list) {

        bool totalResult{ true };

        for (const auto& [from, to, weight] : list) {

            bool result = addEdge(from, to, weight);
            totalResult = totalResult && result;
        }

        return totalResult;
    }

    template<typename T, typename W>
    const AdjacencyTrackList<W>& Graph<T, W>::getAdjacentTracks(const T& value) const
    {
        static AdjacencyTrackList<W> empty{};

        if (!contains(value)) {

            return empty;
        }

        const GraphNode<T, W>& node{ findNode(value) };

        return node.getAdjacentTracks();
    }

    template<typename T, typename W>
    std::vector<Edge<W>> Graph<T, W>::getAllEdges() const
    {
        std::vector<Edge<W>> edges;

        for (size_t source{}; const GraphNode<T, W>&node : m_nodes) {

            const AdjacencyTrackList<W>& list = node.getAdjacentTracks();

            for (const auto& entry : list) {

                Edge<W> edge{ source, getTrackTarget(entry), getTrackWeight(entry) };

                edges.push_back(edge);
            }

            ++source;
        }

        return edges;
    }

    // private helper methods
    template<typename T, typename W>
    bool Graph<T, W>::contains(const T& data) const
    {

        typename NodesContainerType<T, W>::const_iterator position = std::find_if(
            std::begin(m_nodes),
            std::end(m_nodes),
            [&](const auto& node) {
                return node.data() == data;
            }
        );

        return (position == std::end(m_nodes)) ? false : true;
    }

    template<typename T, typename W>
    bool Graph<T, W>::addNode(const T& data)
    {

        if (contains(data)) {
            return false;
        }

        T copy{ data };
        m_nodes.emplace_back(std::move(copy));

        size_t size = m_nodes.size();
        m_nodes[size - 1].setIndex(size - 1);

        return true;
    }

    template<typename T, typename W>
    GraphNode<T, W>& Graph<T, W>::findNode(const T& value)
    {
        typename NodesContainerType<T, W>::iterator position = std::find_if(
            std::begin(m_nodes),
            std::end(m_nodes),
            [&value](const auto& node) {
                return node.data() == value;
            }
        );

        if (position == std::end(m_nodes)) {
            throw std::invalid_argument("Node with specified value not found!");
        }

        GraphNode<T, W>& tmp = *position;

        return tmp;
    }

    template<typename T, typename W>
    const GraphNode<T, W>& Graph<T, W>::findNode(const T& value) const
    {
        const typename NodesContainerType<T, W>::const_iterator position = std::find_if(
            std::begin(m_nodes),
            std::end(m_nodes),
            [&value](const auto& node) {
                return node.data() == value;
            }
        );

        if (position == std::end(m_nodes)) {
            throw std::invalid_argument("Node with specified value not found!");
        }

        const GraphNode<T, W>& tmp = *position;

        return tmp;
    }

    template<typename T, typename W>
    std::string Graph<T, W>::toStringRaw(int width) const
    {

        std::string separator{ isDirected() ? "->" : "<=>" };

        std::ostringstream oss;
        oss << "Graph: ";
        oss << "Nodes: " << countNodes() << ", Edges: " << countEdges();
        oss << " // " << (isDirected() ? "Directed" : "Undirected");
        oss << " - " << (isWeighted() ? "Weighted" : "Unweighted") << std::endl << std::endl;

        for (const GraphNode<T, W>& node : m_nodes) {

            size_t index = node.getIndex();

            oss << "[" << std::setw(width) << std::right << index << "]";

            const AdjacencyTrackList<W>& list = m_nodes[index].getAdjacentTracks();

            if (list.size() != 0) {

                oss << " " << separator << " [";

                for (size_t n{}; const auto & [to, weight] : list)
                {
                    oss << to;

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

    template<typename T, typename W>
    std::string Graph<T, W>::toString(int width) const
    {

        std::string separator{ isDirected() ? "->" : "<=>" };

        std::ostringstream oss;
        oss << "Graph: ";
        oss << "Nodes: " << countNodes() << ", Edges: " << countEdges();
        oss << " // " << (isDirected() ? "Directed" : "Undirected");
        oss << " - " << (isWeighted() ? "Weighted" : "Unweighted") << std::endl << std::endl;

        for (const GraphNode<T, W>& node : m_nodes) {

            const T& fromValue = node.data();

            oss << "[" << std::setw(width) << std::right << fromValue << "]";

            const AdjacencyTrackList<W>& list = getAdjacentTracks(fromValue);

            if (list.size() != 0) {

                oss << " " << separator << " [";

                for (size_t n{}; const auto & [to, weight] : list)
                {
                    // const T& toValue = m_nodes[to].value();
                    const T& toValue{ getDataFromNode(to) };

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

    template<typename T, typename W>
    std::string Graph<T, W>::toString(const Path& path) const
    {
        W totalWeight{};

        std::ostringstream oss;

        if (path.size() == 0) {

            oss << "Empty Path!";
        }
        else {

            std::string arrow = isDirected() ? " -> " : " => ";

            for (size_t index{}; index != path.size(); ++index) {

                // const T& value{ m_nodes[path[index]].value() };
                const T& value{ getDataFromNode(index) };

                oss << '[' << value << ']';

                if (index < path.size() - 1) {

                    oss << arrow;

                    const GraphNode<T, W>& node = m_nodes[path[index]];

                    const auto& [to, weight] = node.getTrack(path[index + 1]);

                    if constexpr (!std::is_same<W, EmptyType>::value)
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
}

// =====================================================================================
// End-of-File
// =====================================================================================
