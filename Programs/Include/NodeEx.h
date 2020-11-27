// =====================================================================================
// NodeEx.h
// =====================================================================================


// ==================================================================
// experimental

template<typename ... TARGS>
auto make_node(TARGS ... args) {
    return std::tuple<TARGS ...> { args ... };
}

template<typename NODE>
auto getDetail(NODE&& node, int&& i) {
    return std::get<i>(std::forward<NODE>(node));
}

template<typename ...TARGS>
using BaseNode = std::tuple<TARGS ...>;

//template<typename WEIGHT, typename ... ARGS>
//auto make_weighted_edge(IndexType to, IndexType target, WEIGHT weight, ARGS ... args) {
//    return std::tuple<IndexType, IndexType, ARGS ...> { to, target, weight, args ... };
//}
//
//template<typename ...ARGS>
//using BaseEdge = std::tuple<IndexType, IndexType, ARGS ...>;
//
//template<typename WEIGHT, typename ...ARGS>
//using BaseEdgeWeighted = std::tuple<IndexType, IndexType, WEIGHT, ARGS ...>;
//
//template<typename ... ARGS>
//using MyEdge1 = decltype (make_edge(std::declval<IndexType>(), std::declval<IndexType>(), std::declval<ARGS>()...));

// ==================================================================
// rest - needed ??? PeLo



// PeLo
//template<typename T>
//using Node = std::pair<IndexType, T>;

// PeLo
//template<typename T>
//using Node = std::tuple<IndexType, T>;

//// helper functions for nodes
//template<typename N>
//int getId(const N& node) {
//    return std::get<0>(node);
//}
//
//// PeLo: entfernen ... der zweite Template Parameter kann so wegfallen
//template<typename N, typename T>
//T getDetails(const N& node) {
//    return std::get<1>(node);
//}
//
//// PeLo: Langfristig das 'Ex' entfernen ....
//template<typename N>
//auto getDetailsEx(const N& node) {
//    return std::get<1>(node);
//}

//template<typename N>
//std::string nodeToString(const N& node) {
//    return std::to_string(getId(node));
//}

// =====================================================================================
// End-of-File
// =====================================================================================
