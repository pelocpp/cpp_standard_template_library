// =====================================================================================
// EdgeEx.h
// =====================================================================================

// PeLo
// https://en.cppreference.com/w/cpp/utility/tuple/tuple_cat

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

template<typename ...TARGS>
using BaseEdge = std::tuple<IndexType, IndexType, TARGS ...>;

template<typename ... TARGS>
using BaseEdgeEx = decltype (make_edge(std::declval<IndexType>(), std::declval<IndexType>(), std::declval<TARGS>() ...));

template<typename TWEIGHT, typename ...TARGS>
using BaseEdgeWeighted = std::tuple<IndexType, IndexType, TWEIGHT, TARGS ...>;

template<typename TWEIGHT, typename ... TARGS>
using BaseEdgeWeightedEx = decltype (make_edge(std::declval<IndexType>(), std::declval<IndexType>(), std::declval<TWEIGHT>(), std::declval<TARGS>() ...));

template<typename EDGE>
void setSourceNode(EDGE&& edge, int value) {
    std::get<0>(edge) = value;
}

template<typename EDGE>
void setTargetNode(EDGE&& edge, int value) {
    std::get<1>(edge) = value;
}



// PeLo: Die brauche ich doch, oder ???????????????????????????
//template<typename ... TARGS>
//auto make_empty_edge(TARGS ... args) {
//    return std::tuple<IndexType, IndexType, args ...> { -1, -1, args ... };
//}
//
//template<typename TWEIGHT, typename ... TARGS>
//auto make_empty_weighted_edge(TWEIGHT weight, TARGS ... args) {
//    return std::tuple<IndexType, IndexType, TARGS ...> { -1, -1, TWEIGHT{}, args ... };
//}



// ==================================================================

template <bool WEIGHTED, unsigned int N>
struct EdgeHelper
{
    template <typename ... TARGS>
    static std::string traverse(const std::tuple<TARGS ...>& tuple) {

        if constexpr (WEIGHTED && N == 3) {
            return std::string("");
        }
        else if constexpr ((!WEIGHTED) && N == 2) {
            return std::string("");
        }

        std::string tmp = EdgeHelper<WEIGHTED, N - 1>::traverse(tuple);

        using type = typename std::tuple_element<N - 1, std::tuple<TARGS...>>::type;
        auto value = std::get<N - 1>(tuple);

        std::string seperator = "";
        if constexpr (N < sizeof...(TARGS)) {
            seperator = ", ";
        }

        std::string result = "";
        if constexpr (std::is_same<std::string, type>::value) {
            result = tmp + value + seperator;
        }
        else {
            result = tmp + std::to_string(value) + seperator;
        }

        return result;
    }
};

template <bool WEIGHTED>
struct EdgeHelper<WEIGHTED, 0>
{
    template <typename ... TARGS>
    static std::string traverse(const std::tuple<TARGS ...>& tuple) { return std::string(""); }
};

template <typename ... TARGS>
std::string toStringUnweightedEdge(const std::tuple<TARGS ...>& tuple)
{
    std::ostringstream oss;

    oss << "["
        << std::get<IndexSource>(tuple)
        << "] -> ["
        << std::get<IndexTarget>(tuple)
        << "] ";

    std::string result = EdgeHelper<false, sizeof ... (TARGS)>::traverse(tuple);
    oss << result;
    return oss.str();
}

template <typename ... TARGS>
std::string toStringWeightedEdge(const std::tuple<TARGS ...>& tuple)
{
    std::ostringstream oss;

    oss << "[" 
        << std::get<IndexSource>(tuple)
        << "] -> ["
        << std::get<IndexTarget>(tuple)
        << "] ";

    using TWeight = typename std::tuple_element<IndexWeight, std::tuple<TARGS...>>::type;
    TWeight weight = std::get<IndexWeight>(tuple);

    oss << "("
        << weight
        << ") ";

    std::string result = EdgeHelper<true, sizeof ... (TARGS)>::traverse(tuple);
    oss << result;
    return oss.str();
}

template<typename EDGE, bool WEIGHTED>
std::string toStringEdge(EDGE edge) {
    std::string s;
    if constexpr (!WEIGHTED) {
        s = toStringUnweightedEdge(edge);
    }
    else if constexpr (WEIGHTED) {
        s = toStringWeightedEdge(edge);
    }
    return s;
}

template<typename EDGE, bool WEIGHTED, typename ITERATOR>
std::string toStringEdges(ITERATOR begin, ITERATOR end) {
    std::ostringstream oss;
    std::string s;
    std::for_each(begin, end, [&](const EDGE& edge) {
        if constexpr (! WEIGHTED) {
            s = toStringUnweightedEdge(edge);
        }
        else if constexpr (WEIGHTED) {
            s = toStringWeightedEdge(edge);
        }
        oss << s << std::endl;
    });
    return oss.str();
}

// ==================================================================










//auto my_make_edge(int id, std::string text) -> MyNodeType {
//    return make_node<int, std::string>(id, text);
//};





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



// helper functions for edges
template<typename EDGE>
bool isEmpty(const EDGE& edge) {
    return (std::get<0>(edge) == -1 && std::get<1>(edge) == -1) ? true : false;
}

template<typename EDGE>
int getSource(const EDGE& edge) {
    return std::get<0>(edge);
}

template<typename EDGE>
int getTarget(const EDGE& edge) {
    return std::get<1>(edge);
}

template<typename EDGE>
void swapSourceTarget(EDGE& edge) {
    std::swap(std::get<0>(edge), std::get<1>(edge));
}

template<typename EDGE>
auto getWeight(const EDGE& edge) {
    return std::get<2>(edge);
}

// =====================================================================================
// End-of-File
// =====================================================================================


