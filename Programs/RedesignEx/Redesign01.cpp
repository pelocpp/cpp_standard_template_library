//// =====================================================================================
//// Graph Theory Redesign // Summer 2023
//// =====================================================================================
//
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <sstream>
//#include <vector>
//#include <set>
//#include <deque>
//#include <utility>
//#include <algorithm>
//#include <optional>
//#include <queue>
//#include <type_traits>
//#include <string_view>
//#include <format>
//#include <optional>
//#include <stdexcept>
//#include <cstddef>
//
//// =====================================================================================
//
//namespace Graph_Theory_Redesign
//{
//    // hmmm, muss das mit der Vorbelegung sein ...
//    //template <typename NodeDescription>
//    //class IGraphRepresentation
//    //{
//    //public:
//    //    virtual bool isDirected() const = 0;
//    //    virtual bool isWeighted() const = 0;
//
//    //    virtual size_t countNodes() const = 0;
//    //    virtual size_t countEdges() const = 0;
//
//    //    virtual void seTNodeData(size_t index, const NodeDescription& description) = 0;
//    //    virtual void seTNodeDatas(const std::initializer_list<NodeDescription> list) = 0;
//    //    virtual std::optional<NodeDescription> geTNodeData(size_t index) = 0;
//
//    //    virtual std::string toString() const = 0;
//    //};
//
//    // -------------------------------------------------------------------------------------
//
//
//    // TODO:
//    // Hmmm, eigentlich m�sste das man in der Klasse GraphNode verstecken ...
//    // Obwohl es ein R�ckgabeparameter ist
//    // Aber:
//    // Mit den Iterator-Datentypen wird es in C++ genau so gemacht !!!
//
//    // Fazit : Sollte in die Klasse GraphNode verlagert werden
//
//
//    template<typename Weight>
//    using Edge = std::pair<size_t, std::optional<Weight>>;
//
//    //template<typename Weight>
//    //using AdjacencyListType = std::set<Edge<Weight>>;
//
//    template<typename Weight = std::nullptr_t>
//    using AdjacencyListType = std::set<Edge<Weight>>;
//
//    // -------------------------------------------------------------------------------------
//
//
//    //class Empty
//    //{
//    //public:
//    //    Empty() = default;
//
//    //    // bool operator<(const Empty&) const { return true; }
//    //};
//
//    // -------------------------------------------------------------------------------------
//
//    template<typename TData, typename TWeight = std::nullptr_t>
//    class GraphNode
//    {
//    public:
//
//        // added: PeLo -  wird derzeit noch nicht ben�tigt
//        using GraphNodeValueType = TData;
//        using GraphNodeWeightType = TWeight;
//
//        // TODO: Hmmm, das sollte irgendwie generell global oder �berhaupt nicht deklariert werden
//        // type alias for the container type used to store the adjacency list
//        // using adjacency_list_type = std::set<size_t>;
//
//        // mit Gewicht
//        // using adjacency_list_type = std::set<Edge<Weight>>;
//
//    private:
//        TData m_data;
//        AdjacencyListType<TWeight> m_adjacentNodeIndices;
//
//    public:
//        // constructs a graph_node for the given value
//        GraphNode(const TData& data)
//            : m_data{ data } { }
//
//        GraphNode(TData&& data)
//            : m_data{ std::move(data) } { }
//
//        // returns a reference to the stored value
//        TData& value() noexcept { return m_data; }
//        const TData& value() const noexcept { return m_data; }
//
//   // private:
//   // 
//   // TODO: Das sollte m�glicherweise nur die const Version ausreichen
//   // 
//        // returns a reference to the adjacency list
//        AdjacencyListType<TWeight>& getAdjacentNodesIndices()
//        {
//            return m_adjacentNodeIndices;
//        }
//
//        const AdjacencyListType<TWeight>& getAdjacentNodesIndices() const
//        {
//            return m_adjacentNodeIndices;
//        }
//    };
//
//
//    // -------------------------------------------------------------------------------------
//    // -------------------------------------------------------------------------------------
//    // -------------------------------------------------------------------------------------
//
//
//    //using nodes_container_type = std::vector<GraphNode<T, W>>;
//
//    //template<typename Weight>
//    //using Edge = std::pair<size_t, std::optional<Weight>>;
//
//    ////template<typename Weight>
//    ////using AdjacencyListType = std::set<Edge<Weight>>;
//
//    template<typename T, typename W>
//    using NodesContainerType = std::vector<GraphNode<T, W>>;
//
//    template<typename T, typename W = std::nullptr_t>
//    class Graph
//    {
//        using GraphNodeValueType = T;
//        using GraphNodeWeightType = W;
//
//    private:
//        friend GraphNode<T, W>;  // hmm, wo wird da in GraphNode reingelangt ....
//
//        NodesContainerType<T, W> m_nodes;
//
//        bool m_isDirected;
//        bool m_isWeighted;
//
//    public:
//
//        Graph() {
//            m_isDirected = true;
//            m_isWeighted = false;
//        }
//
//        Graph(bool isDirected, bool isWeighted) {
//            m_isDirected = isDirected;
//            m_isWeighted = isWeighted;
//        }
//
//
//        // For an insert to be successful, the value shall not be in the graph yet. 
//        // Returns true if a new node with given value has been added to
//        // the graph, and false if there was already a node with the given value.
//        
//        bool addNode(const T& value) {
//
//            T copy{ value };
//            return addNode(std::move(copy));
//        }
//
//        bool addNode(T&& value) {
//
//            auto iter{ findNode(value) };
//
//            if (iter != std::end(m_nodes)) {
//                // value is already in the graph, return false
//                return false;
//            }
//
//            m_nodes.emplace_back(std::move(value));
//            return true;
//        }
//
//        void addNodes(const std::initializer_list<T> list) {
//
//            std::for_each(
//                list.begin(), 
//                list.end(),
//                [&](const auto& value) {
//                    addNode(value);
//                }
//            );
//        }
//
//
//        // TODO: Allgemein: Es m�ssen / sollten 2 Varianten an Methoden vorhanden sein:
//        // addEdge mit Indices
//        // addEdge mit Werten von Knoten
//
//
//
//        // Returns true if the edge was successfully created, false otherwise.
//        bool addEdge(const T& from_node_value, const T& to_node_value)
//        {
//            if (m_isWeighted) {
//                throw std::logic_error("Graph should be unweighted!");
//            }
//
//            const auto from{ findNode(from_node_value) };
//
//            const auto to{ findNode(to_node_value) };
//
//            if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
//                return false;
//            }
//
//            const size_t to_index{ get_index_of_node(to) };
//
//            AdjacencyListType<W>& list = from->getAdjacentNodesIndices();
//
//            Edge<W> edge{to_index, std::nullopt};
//
//            auto [pos, succeeded] = list.insert(edge);
//
//            return succeeded;
//        }
//
//        bool addEdge(const T& from_node_value, const T& to_node_value, W weight)  {
//
//            if (m_isWeighted) {
//                throw std::logic_error("Graph should be weighted!");
//            }
//
//            const auto from{ findNode(from_node_value) };
//
//            const auto to{ findNode(to_node_value) };
//
//            if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
//                return false;
//            }
//
//            const size_t to_index{ get_index_of_node(to) };
//
//            AdjacencyListType<W>& list = from->getAdjacentNodesIndices();
//
//            Edge<W> edge{to_index, weight};
//
//            auto [pos, succeeded] = list.insert(edge);
//
//            return succeeded;
//        }
//
//        // Returns a reference to the node with given index.
//        // No bounds checking is done.
//        T& operator[](size_t index)
//        {
//            return m_nodes[index].value();
//        }
//
//        const T& operator[](size_t index) const
//        {
//            return m_nodes[index].value();
//        }
//
//        // Returns the number of nodes in the graph.
//        size_t countNodes() const noexcept
//        {
//            return m_nodes.size();
//        }
//
//        // Returns a set with the adjacent nodes of a given node.
//        // If the given node does not exist, an empty set is returned.
//        std::set<T> get_adjacent_nodes_values(const T& node_value) const
//        {
//            auto node{ findNode(node_value) };
//
//            if (node == std::end(m_nodes)) {
//                return std::set<T>{};
//            }
//
//            return get_adjacent_nodes_values(node->getAdjacentNodesIndices());
//        }
//
//    //private:
//    //    friend GraphNode<T>;
//
//    //    using nodes_container_type = std::vector<GraphNode<T>>;
//
//    //    nodes_container_type m_nodes;
//
//        
//
//        // Helper method to return an iterator to the given node, or the end iterator
//        // if the given node is not in the graph.
//        // typename nodes_container_type::iterator findNode(const T& node_value)
//        typename NodesContainerType<T, W>::iterator findNode(const T& node_value)
//        {
//            //return std::find_if(
//            //    std::begin(m_nodes), 
//            //    std::end(m_nodes),
//            //    [&node_value](const auto& node) {
//            //        return node.value() == node_value;
//            //    }
//            //);
//
//            // for testing separated in several statements
//
//            auto pos = std::find_if(
//                std::begin(m_nodes),
//                std::end(m_nodes),
//                [&node_value](const auto& node) {
//                    return node.value() == node_value;
//                }
//            );
//
//            return pos;
//        }
//
//        //typename nodes_container_type::const_iterator findNode(const T& node_value) const
//        typename NodesContainerType<T, W>::const_iterator findNode(const T& node_value) const
//        {
//            return const_cast<Graph<T>*>(this)->findNode(node_value);
//        }
//
//        // Given a set of adjacency node indices, returns the corresponding
//        // set of node values.
//        std::set<T> get_adjacent_nodes_values(const AdjacencyListType<W>& indices) const
//        {
//            std::set<T> values;
//
//            // TODO: Muss dieses auto&& da wirklich sein ??? StackOverflow
//            for (auto&& index : indices)
//            {
//                values.insert(m_nodes[index].value());
//            }
//
//            return values;
//        }
//
//        // Given an iterator to a node, returns the index of that node in the nodes container.
//        // size_t get_index_of_node(const typename nodes_container_type::const_iterator& node) const noexcept
//        size_t get_index_of_node(const typename NodesContainerType<T, W>::const_iterator& node) const noexcept
//        {
//            const auto index{ std::distance(std::cbegin(m_nodes), node) };
//
//            return static_cast<size_t>(index);
//        }
//
//        // added: PeLo - NEU
//
//        T geTNodeData(size_t index) {
//            return m_nodes[index].value();
//        }
//
//         bool isDirected() const { return true; }
//
//         size_t countEdges() const
//         {
//             size_t count = 0;
//             std::for_each(
//                 std::begin(m_nodes),
//                 std::end(m_nodes),
//                 [&](const auto& node) {
//
//                     const AdjacencyListType<W>& list = node.getAdjacentNodesIndices();
//
//                     count += list.size();
//                 }
//             );
//             // return (isDirected()) ? count : count / 2;
//             return count;
//         }
//
//         //typename GraphNode<T>::adjacency_list_type& getAdjacentNodesIndices(size_t index)
//         //{
//         //    return m_nodes[index].getAdjacentNodesIndices();
//         //}
//
//         //const typename GraphNode<T>::adjacency_list_type& getAdjacentNodesIndices(size_t index) const
//         //{
//         //    return m_nodes[index].getAdjacentNodesIndices();
//         //}
//
//         // TODO: Diese Methoden liefern ALLES zur�ck : Index und Gewicht (std::optional)
//         // TODO: Wird da eine zweite MEthode ben�tigt, die nur die Indices zur�ck liefert ?????
//
//         AdjacencyListType<W>& getAdjacentNodesIndices(size_t index)
//         {
//             return m_nodes[index].getAdjacentNodesIndices();
//         }
//
//         //AdjacencyListType<W>& getAdjacentNodesIndices(size_t index) const
//         //{
//         //    return m_nodes[index].getAdjacentNodesIndices();
//         //}
//
//
//        //'return': cannot convert from
//        //'std::set<std::pair<size_t,std::optional<TWeight>>,std::less<std::pair<size_t,std::optional<TWeight>>>,std::allocator<std::pair<size_t,std::optional<TWeight>>>>' to 
//        //'std::set<std::pair<size_t,std::optional<W>>,std::less<std::pair<size_t,std::optional<W>>>,std::allocator<std::pair<size_t,std::optional<W>>>> &'	RedesignEx	C : \Development\GitRepositoryCPlusPlus\Cpp_StandardTemplateLibrary\Programs\RedesignEx\Redesign01.cpp	407
//
//
//    };
//
//
//    // -------------------------------------------------------------------------------------
//
//    // Returns a given graph in DOT format.
//    template <typename T>
//    std::string toDot(const Graph<T>& graph, std::string_view graph_name)
//    {
//        std::stringstream ss;
//
//        ss << std::format("digraph {} {{", graph_name.data()) << std::endl;
//
//        for (size_t index{ 0 }; index < graph.countNodes(); ++index)
//        {
//            const auto& node_value{ graph[index] };
//
//            const auto adjacent_nodes{ graph.get_adjacent_nodes_values(node_value) };
//
//            if (adjacent_nodes.empty())
//            {
//                ss << node_value << std::endl;
//            }
//            else
//            {
//                for (auto&& node : adjacent_nodes)
//                {
//                    ss << std::format("{} -> {}", node_value, node) << std::endl;
//                }
//            }
//        }
//        ss << "}" << std::endl;
//
//        return ss.str();
//    }
//
//    // second version
//    template <typename T, typename W>
//    std::string toString(const Graph<T, W>& graph) {
//
//        std::string separator{ graph.isDirected() ? " -> " : " <=> " };
//
//        std::ostringstream oss;
//        oss << "Nodes: " << graph.countNodes() << ", Edges: " << graph.countEdges() << std::endl;
//
//        // Original:
//        // for (size_t source = 0; const std::vector<size_t>&list : graph.m_adjacencyList) {
//
//        for (size_t index = 0; index < graph.countNodes(); ++index) {
//
//            // if (m_nodeDescription[source].has_value())
//            if (true)
//            {
//                T description = graph[index]; // overloaded index operator
//
//                // using T = std::remove_cv<NodeDescription>::type;
//                using NodeType = std::remove_cv<T>::type;
//
//                if constexpr (!std::is_same<NodeType, std::string>::value) {
//                    std::string s{ std::to_string(description) };
//                    oss << "[" << /* std::setw(12) << std::left << */ s << "] ";
//                }
//                else {
//                    oss << "[" << /* std::setw(12) << std::left << */ description << "] ";
//                }
//            }
//            else {
//                std::string s{ (graph.countNodes() >= 10 && index < 10) ? "0" + std::to_string(index) : std::to_string(index) };
//                oss << "[" << s << "] ";
//            }
//
//            //typename GraphNode<T>::adjacency_list_type& getAdjacentNodesIndices(size_t index)
//            //{
//            //    return m_nodes[index].getAdjacentNodesIndices();
//            //}
//
//            //const typename GraphNode<T>::adjacency_list_type& getAdjacentNodesIndices(size_t index) const
//            //{
//            //    return m_nodes[index].getAdjacentNodesIndices();
//
//            //}
//
//            // HIER WEITER ...
//            //const typename GraphNode<T>::adjacency_list_type& list = graph.getAdjacentNodesIndices(index);
//
//            //for (size_t n = 0; size_t target : list) {
//            //    oss << index << separator << target;
//            //    if (n != list.size() - 1) {
//            //        oss << " | ";
//            //    }
//            //    ++n;
//            //}
//
//            oss << '\n';
//            // ++source;
//        }
//
//        return oss.str();
//    }
//}
//
//// =====================================================================================
//
//namespace Graph_Theory_DFS
//{
//    using namespace Graph_Theory_Redesign;
//
//    template <typename T>
//    class DFSSolver
//    {
//    private:
//        Graph<T>& m_graph;
//
//        std::vector<bool>                  m_visited;
//        std::deque<std::vector<size_t>>    m_paths;
//
//        std::vector<size_t>                m_components;
//        size_t                             m_count;
//
//    public:
//        DFSSolver(Graph<T>& graph) : m_graph{ graph }, m_count{} {}
//
//        void computeComponents() {
//
//            m_visited.resize(m_graph.countNodes());
//            std::fill(std::begin(m_visited), std::end(m_visited), false);
//
//            m_components.resize(m_graph.countNodes());
//            std::fill(std::begin(m_components), std::end(m_components), 0);
//
//            m_count = 0;
//
//            for (size_t node{}; node != m_graph.countNodes(); ++node) {
//                if (!m_visited.at(node)) {
//                    ++m_count;
//                    depthFirstSearch(node);
//                }
//            }
//        }
//
//        size_t getNumberOfComponents() const { return m_count; }
//
//        std::vector<size_t> getComponent(size_t mark) const {
//
//            std::vector<size_t> result;
//
//            for (size_t index{}; size_t vertex : m_components) {
//
//                if (vertex == mark) {
//                    result.push_back(index);
//                }
//
//                ++index;
//            }
//
//            return result;
//        }
//
//        size_t countFoundPaths() { return m_paths.size(); }
//
//        // function to perform DFS traversal in a directed graph to find
//        // the complete path between source and destination vertices
//        bool findPathAny(size_t source, size_t target, std::vector<size_t>& path) {
//
//            // setup 'm_visited' vector
//            m_visited.resize(m_graph.countNodes());
//            std::fill(std::begin(m_visited), std::end(m_visited), false);
//
//            return findPathAnyHelper(source, target, path);
//        }
//
//        void findPathAll(size_t source, size_t target) {
//
//            // setup 'm_visited' vector
//            m_visited.resize(m_graph.countNodes());
//            std::fill(std::begin(m_visited), std::end(m_visited), false);
//
//            // setup 'currentPath' vector
//            std::vector<size_t> currentPath;
//            currentPath.push_back(source);
//
//            findPathAllHelper(source, target, currentPath);
//        }
//
//        void printPath(const std::vector<size_t>& path) {
//
//            std::for_each(
//                std::begin(path),
//                std::prev(std::end(path)),
//                [](auto vertex) { std::cout << vertex << " -> "; }
//            );
//
//            auto last = path.back();
//            std::cout << last << std::endl;
//        }
//
//        void printPaths() {
//            for (const auto& path : m_paths) {
//                printPath(path);
//            }
//        }
//
//    private:
//        void depthFirstSearch(size_t node) {
//
//            m_visited.at(node) = true;          // mark current node as discovered
//            m_components.at(node) = m_count;    // set mark
//
//            // do for all adjacent vertices of the current vertex
//            std::vector<size_t> neighbours = m_graph.getNeighbouringNodes(node);
//            for (size_t next : neighbours) {
//
//                // next is not discovered
//                if (!m_visited.at(next)) {
//
//                    depthFirstSearch(next);
//                }
//            }
//        }
//
//        bool findPathAnyHelper(size_t source, size_t target, std::vector<size_t>& path) {
//
//            // mark current node as discovered
//            m_visited.at(source) = true;
//
//            // include current node in the path
//            path.push_back(source);
//
//            // if destination vertex is found
//            if (source == target) {
//                return true;
//            }
//
//            // do for all adjacent vertices of the dequeued vertex
//
//            // Original
//            // std::vector<size_t> neighbours = m_graph.getNeighbouringNodes(source);
//
//            AdjacencyListType neighbours = m_graph.getAdjacentNodesIndices(source);
//
//            for (auto [next, weight] : neighbours) {
//
//                // next is not discovered
//                if (!m_visited.at(next)) {
//
//                    // return true if destination is found
//                    if (findPathAnyHelper(next, target, path))
//                        return true;
//                }
//            }
//
//            // backtrack: remove current node from the path
//            path.pop_back();
//
//            // return false if destination vertex is not reachable from source
//            return false;
//
//        }
//
//        void findPathAllHelper(size_t source, size_t target, std::vector<size_t>& path) {
//
//            // mark current node as discovered
//            m_visited.at(source) = true;
//
//            // if destination vertex is found
//            if (source == target) {
//                m_paths.push_back(path); // store found solution
//                m_visited.at(source) = false;  // unmark current node as discovered
//            }
//            else {
//                // do for every edge
//                AdjacencyListType neighbours = m_graph.getAdjacentNodesIndices(source);
//
//
//                //    Severity	Code	Description	Project	File	Line	Suppression State
//                //    Error	C2440	'initializing':
//
//                //cannot convert from
//
//                //    'std::set<std::pair<size_t,std::optional<W>>,std::less<std::pair<size_t,std::optional<W>>>,std::allocator<std::pair<size_t,std::optional<W>>>>' to
//                //    'std::set<std::pair<size_t,std::optional<T>>,std::less<std::pair<size_t,std::optional<T>>>,std::allocator<std::pair<size_t,std::optional<T>>>>'
//
//                for (auto [index, weight] : neighbours) {
//
//                    // next is not discovered
//                    if (!m_visited.at(index)) {
//                        path.push_back(index);  // include current node in the path
//                        findPathAllHelper(index, target, path);
//                        path.pop_back();  // remove current node from the path (backtrack)
//                    }
//                }
//
//                // unmark current node as discovered
//                m_visited.at(source) = false;
//            }
//        }
//    };
//}
//
//// =====================================================================================
//// End-of-File
//// =====================================================================================
//
