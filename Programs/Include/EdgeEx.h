// =====================================================================================
// EdgeEx.h
// =====================================================================================

// ==================================================================
// experimental

template<typename ... TARGS>
auto make_edge(IndexType from, IndexType to, TARGS ... args) {
    return std::tuple<IndexType, IndexType, TARGS ...> { from, to, args ... };
}

template<typename TWEIGHT, typename ... TARGS>
auto make_weighted_edge(IndexType from, IndexType to, TWEIGHT weight, TARGS ... args) {
    return std::tuple<IndexType, IndexType, TWEIGHT, TARGS ...> { from, to, weight, args ... };
}

//template<typename ... TARGS>
//auto make_empty_edge(TARGS ... args) {
//    return std::tuple<IndexType, IndexType, args ...> { -1, -1, args ... };
//}
//
//template<typename TWEIGHT, typename ... TARGS>
//auto make_empty_weighted_edge(TWEIGHT weight, TARGS ... args) {
//    return std::tuple<IndexType, IndexType, TARGS ...> { -1, -1, TWEIGHT{}, args ... };
//}

template<typename ...TARGS>
using BaseEdge = std::tuple<IndexType, IndexType, TARGS ...>;

template<typename TWEIGHT, typename ...TARGS>
using BaseEdgeWeighted = std::tuple<IndexType, IndexType, TWEIGHT, TARGS ...>;

// PeLo: Same name as NODE template .... is it a problem ????
// DER WIRD NICHT ÜBERSETZUNGSFähig sein !!!
template<typename EDGE>
auto getEdgeDetail(EDGE&& edge, int&& i) {
    return std::get<i>(std::forward<EDGE>(edge));
}

template<typename EDGE>
void setSourceNode(EDGE&& edge, int value) {
    std::get<0>(edge) = value;
}

template<typename EDGE>
void setTargetNode(EDGE&& edge, int value) {
    std::get<1>(edge) = value;
}


// PeLo TESTEN UND AUFRUFEN ... wo wird das aufgerufen !!!
template<typename EDGE, typename ITERATOR, bool WEIGHTED>
std::string toStringEdges(ITERATOR begin, ITERATOR end) {
    std::ostringstream oss;
    std::string details;
    std::for_each(begin, end, [&](const EDGE& edge) {
        if constexpr (! WEIGHTED) {
            // it's a unweighted edge
            details = getDetailsUnweightedEdge<EDGE>(edge);
        }
        if constexpr (WEIGHTED) {
            // it's a weighted edge
            details = getDetailsWeightedEdge<EDGE>(edge);
        }
        oss << edgeToString(edge) << " " << details << '\n';
    });
    return oss.str();
}

// WEITER !!!!!!!!!!!!!!!!

// https://en.cppreference.com/w/cpp/utility/tuple/tuple_cat

//template<typename WEIGHTED_EDGE>
//auto getDetailsWeightedEdge(IndexType from, IndexType to, TWEIGHT weight, E&& edge) {
//
//
//
//    return std::get<2>(std::forward<E>(edge));
//}
//
















template<typename ... TARGS>
using MyEdge1 = decltype (make_edge(std::declval<IndexType>(), std::declval<IndexType>(), std::declval<TARGS>() ...));

// PeLo
// https://stackoverflow.com/questions/26732709/how-to-use-sfinae-to-create-2-different-implementations-of-the-same-method
//
//template<class T>
//typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
//make_edge_ex(T x, T y, int ulp)
//{
//    return std::tuple<IndexType, IndexType, TARGS ...> { from, to, args ... };
//}
//
//template<class T>
//typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
//make_weighted_edge_ex(T x, T y, int ulp)
//{
//    return std::tuple<IndexType, IndexType, TARGS ...> { from, to, args ... };
//}


//
//template<typename T, typename = void> struct EgdeCreator;
//
//template<typename T>
//struct EgdeCreator < T, typename std::enable_if<std::is_pod<T>::type>
//{
//    static auto make_edge_revised()
//    {
//        return std::tuple<IndexType, IndexType, TARGS ...> { from, to, args ... };
//    }
//};
//
//template<typename T>
//struct EgdeCreator < T, typename std::enable_if<!std::is_pod<T>::type>
//{
//    static auto make_edge_revised()
//    {
//        return std::tuple<IndexType, IndexType, TWEIGHT, TARGS ...> { from, to, weight, args ... };
//    };
//};




// =====================================================================================
// REST
// =====================================================================================



// ==================================================================
// rest - needed ??? PeLo


//
//
//template<typename T>
//using UnweightedEdge = std::tuple<IndexType, IndexType, T>;
//
//template<typename W, typename T>
//using WeightedEdge = std::tuple<IndexType, IndexType, W, T>;
//
//// PeLo: umbenennen: make_WeightedEdge
//template<typename W, typename T>
//WeightedEdge<W, T> createWeightedEdge(IndexType to, IndexType target, W weight) {
//    return std::tuple<IndexType, IndexType, W, T> {to, target, weight, T{}};
//}
//
//// helper functions for edges
//template<typename E>
//bool isEmpty(const E& edge) {
//    return (std::get<0>(edge) == -1 && std::get<1>(edge) == -1) ? true : false;
//}

template<typename E>
int getSource(const E& edge) {
    return std::get<0>(edge);
}

template<typename E>
int getTarget(const E& edge) {
    return std::get<1>(edge);
}

//template<typename E>
//void swapSourceTarget(E& edge) {
//    std::swap(std::get<0>(edge), std::get<1>(edge));
//}
//
//// PeLo: entfernen ... der zweite Template Parameter kann so wegfallen
//template<typename E, typename W>
//W getWeight(const E& edge) {
//    return std::get<2>(edge);
//}
//
//// PeLo: Langfristig das 'Ex' entfernen ....
//template<typename E>
//auto getWeightEx(E&& edge) {
//    return std::get<2>(std::forward<E>(edge));
//}
//
//template<typename E, typename T>
//T getDetailsUnweightedEdge(const E& edge) {
//    return std::get<2>(edge);
//}
//
//template<typename E, typename T>
//T getDetailsWeightedEdge(const E& edge) {
//    return std::get<3>(edge);
//}
//
//
//// PeLo: Langfristig das 'Ex' entfernen ....
//template<typename E>
//auto getDetailsUnweightedEdgeEx(E&& edge) {
//    return std::get<2>(std::forward<E>(edge));
//}
//
//// PeLo: Langfristig das 'Ex' entfernen ....
//template<typename E>
//auto  getDetailsWeightedEdgeEx(E&& edge) {
//    return std::get<3>(std::forward<E>(edge));
//}
//
//template<typename E>
//std::string edgeToString(const E& edge) {
//    IndexType source = getSource(edge);
//    IndexType target = getTarget(edge);
//
//    std::ostringstream oss;
//    oss << source << "->" << target;
//    return oss.str();
//}


// =====================================================================================
// End-of-File
// =====================================================================================


