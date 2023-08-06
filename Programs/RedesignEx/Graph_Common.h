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
#include <tuple>
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
    return std::get<2>(edge);
}

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
using AdjacencyTrackList = std::set<Track<Weight>, TrackComparer<Weight>>;

// ------------------------------------------------------------------

using Path = std::vector<size_t>;

// =====================================================================================
// End-of-File
// =====================================================================================


