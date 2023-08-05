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


    // TODO: Hmmm, Namensgebung
    // Entweder:  W oder Weight oder TWeight ...


    using EmptyType = std::nullptr_t;

    template<typename Weight>
    using Edge = std::pair<size_t, std::optional<Weight>>;


    // TODO: ÜBERALL, wo .first im QUellcode steht:  getTarget einsetzen !!!!!!!!!!!!!!!!
    template<typename TEdge>
    size_t getTarget(const TEdge& edge) {
        return std::get<0>(edge);
    }

    // needed as key compare function for std::set
    template<typename Weight = EmptyType>
    auto cmp = [] (Edge<Weight> edge1, Edge<Weight> edge2) {

        auto [vertex1, weight1] = edge1;
        auto [vertex2, weight2] = edge2;

        return vertex1 < vertex2;
    };

    template<typename Weight = EmptyType>
    using AdjacencyListType = std::set<Edge<Weight>, decltype(cmp<Weight>)>;

    // NEU

    template<typename Weight>
    using ExtendedEdge = std::pair<size_t, Edge<Weight>>;

    template<typename Weight>
    size_t getFrom(const ExtendedEdge<Weight>& edge) {
        return std::get<0>(edge);
    }

    // custom function object (functor) to compare weighted edges
    template <typename W>
    struct EdgesComparer
    {
        bool operator() (const Edge<W>& l, const Edge<W>& r) const {

            const auto& [vertexLeft, weightLeft] = l;
            const auto& [vertexRight, weightRight] = r;
            return weightLeft.value() > weightRight.value();
        }
    };

    // update edge on shortest path
    //Edge<W> nextEdge {nextVertex, pathWeight};
    //ExtendedEdge<W> extendedEdge{vertex, nextEdge};
    //m_shortestPathMap[nextVertex] = extendedEdge;

    //ExtendedEdge<W> edge{ m_shortestPathMap[end] };
    //size_t from{ getFrom(edge) };

    // -------------------------------------------------------------------------------------

    template<typename T, typename W = EmptyType>
    class GraphNode
    {
    private:
        size_t m_index;
        T m_data;
        AdjacencyListType<W> m_adjacentNodes;

    public:
        // constructing a graph_node for a given value
        GraphNode(const T& data) : m_data{ data } { }

        GraphNode(T&& data) : m_data{ std::move(data) } { }

        // prohibit nodes with no data value
        GraphNode() = delete;

        // returns a reference to the stored value
        T& value() noexcept { return m_data; }
        const T& value() const noexcept { return m_data; }

        // returns the number of nodes in the adjacency list
        size_t count() const noexcept
        {
            return m_adjacentNodes.size();
        }

        size_t getIndex()  const noexcept { return m_index; }
        void setIndex(size_t index) noexcept { m_index = index; }

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


        // NEU
        const Edge<W>& getEdge(size_t vertex) const {

            // Hmmmm, was, wenn verte nicht passt ?????????????????????????????

            const auto x = std::find_if(
                m_adjacentNodes.begin(), 
                m_adjacentNodes.end(),
                [=](const auto& edge) {
                    size_t target = edge.first;
                    return target == vertex;
                }
            );

          //  std::cout << "Stopper" << std::endl;

            return *x;
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
