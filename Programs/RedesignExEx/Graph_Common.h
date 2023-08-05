// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Graph_Common.h
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

enum class Direction { Directed, Undirected };

enum class Weight { Weighted, Unweighted };

using NodeIndex = size_t;

using EmptyType = std::nullptr_t;

// ------------------------------------------------------------------


template<typename Weight>
using Track = std::pair<size_t, std::optional<Weight>>;

// TODO: ÜBERALL, wo .first im QUellcode steht:  getTarget einsetzen !!!!!!!!!!!!!!!!
// TODO: HINWEIS: Dieses getTarget wird derzeit nicht verwendet
template<typename Weight>
auto getTrackTarget(const Track<Weight>& edge) {
    return std::get<0>(edge);
}

template<typename Weight>
auto getTrackWeight(const Track<Weight>& edge) {
    return std::get<1>(edge);
}


// ------------------------------------------------------------------

template<typename Weight>
using Edge = std::tuple<size_t, size_t, std::optional<Weight>>;

template<typename Weight>
size_t getEdgeSource(const Edge<Weight>& edge) {
    return std::get<0>(edge);
}

template<typename Weight>
size_t getEdgeTarget(const Edge<Weight>& edge) {
    return std::get<1>(edge);
}

template<typename Weight>
auto getEdgeWeight(const Edge<Weight>& edge) {
    return std::get<2>(edge).value();   // TODO: Hmmm, vielleicht geht das schöner ....
}


// custom function object (functor) to compare weighted edges
//template <typename W>
//struct EdgesComparer
//{
//    bool operator() (const ExtendedEdge<W>& l, const ExtendedEdge<W>& r) const {
//
//        const auto& [vertexLeft, weightLeft] = l;
//        const auto& [vertexRight, weightRight] = r;
//        return weightLeft.value() > weightRight.value();
//    }
//};

// update edge on shortest path
//Edge<W> nextEdge {nextVertex, pathWeight};
//ExtendedEdge<W> extendedEdge{vertex, nextEdge};
//m_shortestPathMap[nextVertex] = extendedEdge;
//
//ExtendedEdge<W> edge{ m_shortestPathMap[end] };
//size_t from{ getFrom(edge) };



// ------------------------------------------------------------------


// custom function object (functor) to compare tracks
template <typename W>
struct TrackComparer
{
    bool operator() (const Track<W>& l, const Track<W>& r) const {

        const auto& [targetLeft, weightLeft] = l;
        const auto& [targetRight, weightRight] = r;
        return targetLeft < targetRight;
    }
};

template<typename Weight = EmptyType>
using AdjacencyNodesList = std::set<Track<Weight>, TrackComparer<Weight>>;

// ------------------------------------------------------------------

using Path = std::vector<size_t>;

// ------------------------------------------------------------------


// =====================================================================================
// End-of-File
// =====================================================================================


