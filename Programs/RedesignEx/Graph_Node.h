// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Graph_Node.h
// =====================================================================================

#pragma once

#include "Graph_Common.h"

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



    // -------------------------------------------------------------------------------------

    template<typename T, typename W = EmptyType>
    class GraphNode
    {
    private:
        T m_data;
        size_t m_index;   // Hmmm, das sollte möglicherweise OPTIONAL sein !!!!!!!!!!!!!!!!
        AdjacencyTrackList<W> m_adjacentTracks;

    public:
        // constructing a graph_node for a given value
        GraphNode(const T& data) : m_data{ data }, m_index{} { }

        GraphNode(T&& data) : m_data{ std::move(data) }, m_index{} { }

        // prohibit nodes with no data value
        GraphNode() = delete;

        // direct access to the underlying data
        T& data() noexcept { return m_data; }
        const T& data() const noexcept { return m_data; }

        // returns the number of nodes in the adjacency list
        size_t count() const noexcept {
            return m_adjacentTracks.size();
        }

        size_t getIndex()  const noexcept { return m_index; }
        void setIndex(size_t index) noexcept { m_index = index; }

        // private:
        const AdjacencyTrackList<W>& getAdjacentTracks() const
        {
            // returns a reference to the adjacency list
            return m_adjacentTracks;
        }

        AdjacencyTrackList<W>& getAdjacentTracks()
        {
            return m_adjacentTracks;
        }


        // TO BE DONE:
        // a) AdjacencyTrackList
        // b) AdjacencyEdgesList


        // NEU
        const Track<W>& getTrack(size_t vertex) const {

            auto pos = std::find_if(
                m_adjacentTracks.begin(),
                m_adjacentTracks.end(),
                [=](const auto& track) {
                    const auto& [index, weight] = track;
                    return index == vertex;
                }
            );

            return *pos;
        }


        // TODO: Hmmm, diese ganzen Comparer mal aufräumen ....
        // needed for constructing stl set container with 'GraphNode' objects
        // TODO: Der wird nicht benötigt !!!!!!!!!!!!!
        //bool operator< (const GraphNode& other) 
        //    return m_data < other.m_data;
        //}
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
