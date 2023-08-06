// =====================================================================================
// Graph Theory Redesign // Summer 2023 // GraphNode.h
// =====================================================================================

#pragma once

#include "Graph_Common.h"

// =====================================================================================

namespace Graph_Theory
{
    // TODO:
    // Hmmm, eigentlich m�sste das man in der Klasse GraphNode verstecken ...
    // Obwohl es ein R�ckgabeparameter ist
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
        size_t m_index;
        T m_data;
        AdjacencyTrackList<W> m_adjacentTracks;

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
            return m_adjacentTracks.size();
        }

        size_t getIndex()  const noexcept { return m_index; }
        void setIndex(size_t index) noexcept { m_index = index; }

        // private:
        // 
        // TODO: Das sollte m�glicherweise nur die const Version ausreichen
        // 

        // returns a reference to the adjacency list
        const AdjacencyTrackList<W>& getAdjacentTracks() const
        {
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

            // Hmmmm, was, wenn verte nicht passt ?????????????????????????????

            const auto pos = std::find_if(
                m_adjacentTracks.begin(),
                m_adjacentTracks.end(),
                [=](const auto& track) {
                    size_t target = track.first;   // TODO: da geht entweder structured binding oder getTarget ..
                    return target == vertex;
                }
            );

            return *pos;
        }


        // needed for constructing stl set container with 'GraphNode' objects

        // TODO: Der wird nicht ben�tigt !!!!!!!!!!!!!

        bool operator< (const GraphNode& other) {

            return m_data < other.m_data;
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
