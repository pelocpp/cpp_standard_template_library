// =====================================================================================
// Edge.h
// =====================================================================================

template<typename T>
using UnweightedEdge = std::tuple<IndexType, IndexType, T>;

template<typename W, typename T>
using WeightedEdge = std::tuple<IndexType, IndexType, W, T>;

// PeLo: umbenennen: make_WeightedEdge
template<typename W, typename T>
WeightedEdge<W, T> createWeightedEdge(IndexType source, IndexType target, W weight) {
    return std::tuple<IndexType, IndexType, W, T> {source, target, weight, T{}};
}

// helper functions for edges
template<typename E>
bool isEmpty(const E& edge) {
    return (std::get<0>(edge) == -1 && std::get<1>(edge) == -1) ? true : false;
}

template<typename E>
int getSource(const E& edge) {
    return std::get<0>(edge);
}

template<typename E>
int getTarget(const E& edge) {
    return std::get<1>(edge);
}

template<typename E>
void swapSourceTarget(E& edge) {
    std::swap(std::get<0>(edge), std::get<1>(edge));
}

// PeLo: entfernen ... der zweite Template Parameter kann so wegfallen
template<typename E, typename W>
W getWeight(const E& edge) {
    return std::get<2>(edge);
}

// PeLo: Langfristig das 'Ex' entfernen ....
template<typename E>
auto getWeightEx(E&& edge) {
    return std::get<2>(std::forward<E>(edge));
}

template<typename E, typename T>
T getDetailsUnweightedEdge(const E& edge) {
    return std::get<2>(edge);
}

template<typename E, typename T>
T getDetailsWeightedEdge(const E& edge) {
    return std::get<3>(edge);
}


// PeLo: Langfristig das 'Ex' entfernen ....
template<typename E>
auto getDetailsUnweightedEdgeEx(E&& edge) {
    return std::get<2>(std::forward<E>(edge));
}

// PeLo: Langfristig das 'Ex' entfernen ....
template<typename E>
auto  getDetailsWeightedEdgeEx(E&& edge) {
    return std::get<3>(std::forward<E>(edge));
}

template<typename E>
std::string edgeToString(const E& edge) {
    IndexType source = getSource(edge);
    IndexType target = getTarget(edge);

    std::ostringstream oss;
    oss << source << "->" << target;
    return oss.str();
}

// ==================================================================
// experimental

template<typename ... ARGS>
auto make_edge(IndexType source, IndexType target, ARGS ... args) {
    return std::tuple<IndexType, IndexType, ARGS ...> { source, target, args ... };
}

template<typename ...ARGS>
using BaseEdge = std::tuple<IndexType, IndexType, ARGS ...>;

template<typename ... ARGS>
using MyEdge1 =  decltype (make_edge(std::declval<IndexType>(), std::declval<IndexType>(), std::declval<ARGS>()...));


// =====================================================================================
// End-of-File
// =====================================================================================


