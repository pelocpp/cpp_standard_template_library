// =====================================================================================
// Graph Theory Redesign // Summer 2023 // GraphNode.h
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

// =====================================================================================

namespace Graph_Theory
{
    // TODO:
    // Hmmm, eigentlich müsste das man in der Klasse GraphNode verstecken ...
    // Obwohl es ein Rückgabeparameter ist
    // Aber:
    // Mit den Iterator-Datentypen wird es in C++ genau so gemacht !!!

    // Fazit : Sollte in die Klasse GraphNode verlagert werden

    using EmptyType = std::nullptr_t;

    template<typename Weight>
    using Edge = std::pair<size_t, std::optional<Weight>>;

    // needed as key compare function for std::set
    template<typename Weight = EmptyType>
    auto cmp = [](Edge<Weight> edge1, Edge<Weight> edge2) {

        auto [key1, weight1] = edge1;
        auto [key2, weight2] = edge2;

        return key1 < key2;
    };

    template<typename Weight = EmptyType>
    using AdjacencyListType = std::set<Edge<Weight>, decltype(cmp<Weight>)>;

    // -------------------------------------------------------------------------------------

    template<typename T, typename W = EmptyType>
    class GraphNode
    {
    private:
        T m_data;
        AdjacencyListType<W> m_adjacentNodes;

    public:
        // constructing a graph_node for a given value
        GraphNode(const T& data) : m_data{ data } { }

        GraphNode(T&& data) : m_data{ std::move(data) } { }

        // returns a reference to the stored value
        T& value() noexcept { return m_data; }
        const T& value() const noexcept { return m_data; }

        // Returns the number of nodes in the adjacency list
        size_t count() const noexcept
        {
            return m_adjacentNodes.size();
        }

        // private:
        // 
        // TODO: Das sollte möglicherweise nur die const Version ausreichen
        // 

        // returns a reference to the adjacency list
        const AdjacencyListType<W>& getAdjacentNodes() const
        {
            return m_adjacentNodes;
        }

        AdjacencyListType<W>& getAdjacentNodes()
        {
            return m_adjacentNodes;
        }

        // needed for constructing stl set container with 'GraphNode' objects
        bool operator< (const GraphNode& other) {

            return m_data < other.m_data;
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
