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
auto make_node(IndexType id, TARGS ... args) {
    return std::tuple<IndexType, TARGS ...> { id, args ... };
}

template<typename ...TARGS>
using BaseNode = std::tuple<IndexType, TARGS ...>;

// or

//template<typename ... TARGS>
//using BaseNodeEx = decltype (make_node(std::declval<IndexType>(), std::declval<TARGS>() ...));



//template<typename NODE, std::size_t N = 0>
//auto getDetail(NODE&& node) {
//    return std::get<N>(std::forward<NODE>(node));
//}

//template<typename NODE, std::size_t N = 0>
//auto getDetail(NODE& node) {
//    return std::get<N>(node);
//}

// ==================================================================

template <unsigned int N>
struct NodeHelper
{
    template <typename ... TARGS>
    static std::string traverse(const std::tuple<TARGS ...>& tuple) {

        // std::cout << "N: " << N << std::endl;

        if constexpr (N == 1) {
            return std::string("");
        }

        std::string tmp = NodeHelper<N - 1>::traverse(tuple);

        using type = typename std::tuple_element<N - 1, std::tuple<TARGS...>>::type;
        auto value = std::get<N - 1>(tuple);

       // std::cout << "auto: " << value << std::endl;

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

template <>
struct NodeHelper<0>
{
    template <typename ... TARGS>
    static std::string traverse(const std::tuple<TARGS ...>& tuple) { return std::string(""); }
};

template <typename ... TARGS>
std::string toStringNODE(const std::tuple<TARGS ...>& tuple)
{
    std::ostringstream oss;

    oss << "["
        << std::get<IndexNodeId>(tuple)
        << "] ";

    std::string result = NodeHelper<sizeof ... (TARGS)>::traverse(tuple);
    oss << result;
    return oss.str();
}


//template <typename ... TARGS>
//std::string toStringNode(const std::tuple<TARGS ...>& tuple)
//{
//    std::string result = NodeHelper<sizeof ... (TARGS)>::traverse(tuple);
//    return result;
//}

template<typename NODE>
std::string toStringNode(NODE node) {
    std::string s;
    s = toStringNODE(node);
    return s;
}

template<typename NODE, typename ITERATOR>
std::string toStringNodes(ITERATOR begin, ITERATOR end) {
    std::ostringstream oss;
    std::string s;
    std::for_each(begin, end, [&](const NODE& node) {
        s = toStringNode(node);
        oss << s << std::endl;
        });
    return oss.str();
}

// ==================================================================



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
