// =====================================================================================
// Edge.h
// =====================================================================================

template<typename T>
using UnweightedEdge = std::tuple<IndexType, IndexType, T>;

template<typename W, typename T>
using WeightedEdge = std::tuple<IndexType, IndexType, W, T>;

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

template<typename E, typename W>
W getWeight(const E& edge) {
    return std::get<2>(edge);
}

template<typename E, typename T>
T getDetailsUnweightedEdge(const E& edge) {
    return std::get<2>(edge);
}

template<typename E, typename T>
T getDetailsWeightedEdge(const E& edge) {
    return std::get<3>(edge);
}

template<typename E>
std::string edgeToString(const E& edge) {
    IndexType source = getSource(edge);
    IndexType target = getTarget(edge);

    std::ostringstream oss;
    oss << source << "->" << target;
    return oss.str();
}

// =====================================================================================
// End-of-File
// =====================================================================================
