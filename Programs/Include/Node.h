// =====================================================================================
// Node.h
// =====================================================================================

template<typename T>
using Node = std::pair<IndexType, T>;

// helper functions for nodes
template<typename N>
int getId(const N& node) {
    return std::get<0>(node);
}

// PeLo: entfernen ... der zweite Template Parameter kann so wegfallen
template<typename N, typename T>
T getDetails(const N& node) {
    return std::get<1>(node);
}

// PeLo: Langfristig das 'Ex' entfernen ....
template<typename N>
auto getDetailsEx(const N& node) {
    return std::get<1>(node);
}

template<typename N>
std::string nodeToString(const N& node) {
    return to_string(getId(node));
}

// =====================================================================================
// End-of-File
// =====================================================================================
