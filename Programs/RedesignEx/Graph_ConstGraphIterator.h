// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Graph_ConstIterator.h
// =====================================================================================

#pragma once

#include "Graph_Common.h"
#include "Graph_Node.h"
#include "Graph.h"

// =====================================================================================

// Ab Seite 754 .... Marc Gregoire ...

// =====================================================================================


namespace Graph_Theory
{
    template<typename T, typename W>
    class Graph;

    template<typename T, typename W>
    class ConstGraphIterator
    {
        friend class Graph<T, W>;

    public:
        // i) TO BE DONE: Was soll iteriert werden: Tracks oder BESSER Edges 
        // ii) TO BE DONE: Muss das mit oder ohne typename sein ?????????????

        using value_type = Track<W>;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        using pointer = value_type*;
        using reference = value_type&;
        // using list_iterator_type = typename HashMap::ListType::const_iterator;

        // i) TODO: evtl. besserer Name
        // ii) ist das jetzt const oder non-const ...
        // using list_iterator_type = typename AdjacencyTrackList<W>::const_iterator;
        
        // ALSO: std::set<Track<Weight>, TrackComparer<Weight>>::iterator
        using list_iterator_type = typename AdjacencyTrackList<W>::iterator;

    private:
        size_t m_indexNodes = 0;

        list_iterator_type m_adjListIterator;

        const Graph<T, W>* m_graph = nullptr;

    public:
        // c'tor(s)
        ConstGraphIterator() = default; // should never be called !!!

        ConstGraphIterator(size_t indexNodes, list_iterator_type& listIt, const Graph<T, W>* graph)
            : m_indexNodes{ indexNodes }, m_adjListIterator{ listIt }, m_graph{ graph } {}

        // operators
        const value_type& operator*() const
        {
            return *m_adjListIterator;
        }

        // Return type must be something to which -> can be applied.
        // Return a pointer to a pair<const Key, T>, to which the compiler
        // will apply -> again.
        const value_type* operator->() const
        {
            return &(*m_adjListIterator);
        }

        ConstGraphIterator<T, W>& operator++()
        {
            increment();
            return *this;
        }

        ConstGraphIterator<T, W> operator++(int)
        {
            ConstGraphIterator<T, W> copy = *this;
            increment();
            return copy;
        }

        bool operator== (const ConstGraphIterator<T, W>& other) const
        {
            if (m_graph != other.m_graph) {
                return false;
            }
            else if (m_indexNodes != other.m_indexNodes) {
                return false;
            }
            else if (m_adjListIterator != other.m_adjListIterator) {
                return false;
            }
            else {
                return true;
            }
        }

        bool operator!= (const ConstGraphIterator<T, W>& other) const
        {
            return ! (*this == other);
        }

    private:
        // helper methods for operator++
        void increment()
        {
            // Behavior is undefined if m_listIterator already refers to the past-the-end
            // element, or is otherwise invalid.

            // nur zum merken, später wieder LÖSCHEN: increment wird aufgerufen,
            // wenn es vom ersten zum zweiten Element geht !!!

            // m_listIterator is an iterator into a single adjacency track list - increment it
            ++m_adjListIterator;

            // WEITER: 754
             
            // take either next iterator object in the current list
            // or skip to the next adjacency list
            auto endOfAdjListIter = m_graph->m_nodes[m_indexNodes].getAdjacentTracks().end();

            if (m_adjListIterator == endOfAdjListIter) {

                for (size_t i = m_indexNodes + 1; i < m_graph->countNodes(); ++i) {

                    // store index of current adjacency list
                    m_indexNodes = i;

                    if (m_graph->m_nodes[i].getAdjacentTracks().size() != 0) {

                        m_adjListIterator = m_graph->m_nodes[i].getAdjacentTracks().begin();
                        return;
                    }
                }

                // no more graph node found - return end iterator object of last adjacency list
                size_t index = m_graph->countNodes() - 1;
                m_adjListIterator = m_graph->m_nodes[index].getAdjacentTracks().end();
            }
        }
    };

}

// =====================================================================================
// End-of-File
// =====================================================================================
