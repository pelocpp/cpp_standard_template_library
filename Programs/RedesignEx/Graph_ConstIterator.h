// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Graph_ConstIterator.h
// =====================================================================================

#pragma once

#include "Graph.h"

// =====================================================================================

// Ab Seite 751 ....

// =====================================================================================

// fuer spaeter:
//
//template <typename Key, typename T, typename KeyEqual, typename Hash>
//typename hash_map<Key, T, KeyEqual, Hash>::iterator
//hash_map<Key, T, KeyEqual, Hash>::begin()
//{
//    if (mSize == 0) {
//        // Special case: there are no elements, so return the end iterator.
//        return end();
//    }
//
//    // We know there is at least one element. Find the first element.
//    for (size_t i = 0; i < mBuckets.size(); ++i) {
//        if (!mBuckets[i].empty()) {
//            return hash_map_iterator<hash_map_type>(i, std::begin(mBuckets[i]), this);
//        }
//    }
//    // Should never reach here, but if we do, return the end iterator.
//    return end();
//}

// =====================================================================================


namespace Graph_Theory
{
    template<typename T, typename W = EmptyType>
    class ConstGraphIterator
    {
    public:
        using value_type = typename Graph<T, W>::value_type;
        using difference_type = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using pointer = value_type*;
        using reference = value_type&;
        // using list_iterator_type = typename HashMap::ListType::const_iterator;

        // TODO: evtl. besserer Name
        using list_iterator_type = typename AdjacencyTrackList<W>::const_iterator;

    private:
        size_t mBucketIndex = 0;
        list_iterator_type m_listIterator;
        const Graph<T, W>* m_graph = nullptr;

    public:
        const value_type& operator*() const
        {
            return *m_listIterator;
        }

        // Return type must be something to which -> can be applied.
        // Return a pointer to a pair<const Key, T>, to which the compiler
        // will apply -> again.
        const value_type* operator->() const
        {
            return &(*m_listIterator);
        }

        ConstGraphIterator<Graph<T, W>>& operator++()
        {
            increment();
            return *this;
        }

        ConstGraphIterator<Graph<T, W>> operator++(int)
        {
            auto oldIt = *this;   // TODO:  auch mal ohne auto ....
            increment();
            return oldIt;
        }

        // The following are ok as member functions because we don't
        // support comparisons of different types to this one
        bool operator== (const ConstGraphIterator<Graph<T, W>>& other) const
        {

        }

        bool operator!= (const ConstGraphIterator<Graph<T, W>>& other) const
        {

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
            ++m_listIterator;

            // WEITER: 754 
        }
    };
}

// =====================================================================================
// End-of-File
// =====================================================================================
