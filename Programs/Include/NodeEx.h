// =====================================================================================
// NodeEx.h
// =====================================================================================

// ==================================================================
// PeLo
// Generell zu erledigen: Wie werden bei Templates die Files organisiert ....

// https://stackoverflow.com/questions/32606464/why-can-we-not-access-elements-of-a-tuple-by-index

// ==================================================================
// experimental

template<typename ... TARGS>
auto make_node(TARGS ... args) {
    return std::tuple<TARGS ...> { args ... };
}

template<typename ...TARGS>
using BaseNode = std::tuple<TARGS ...>;

//template<typename NODE, std::size_t N = 0>
//auto getDetail(NODE&& node) {
//    return std::get<N>(std::forward<NODE>(node));
//}

template<typename NODE, std::size_t N = 0>
auto getDetail(NODE& node) {
    return std::get<N>(node);
}






//template <std::size_t N>
//std::integral_constant<std::size_t, N> ic;




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
