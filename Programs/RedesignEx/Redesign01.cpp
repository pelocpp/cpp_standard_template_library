// =====================================================================================
// Graph Theory Redesign // Summer 2023
// =====================================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <deque>
#include <utility>
#include <algorithm>
#include <optional>
#include <queue>
#include <type_traits>
#include <string_view>
#include <format>

// =====================================================================================

namespace Graph_Theory_Redesign
{
    // hmmm, muss das mit der Vorbelegung sein ...
    template <typename NodeDescription>
    class IGraphRepresentation
    {
    public:
        virtual bool isDirected() const = 0;
        virtual bool isWeighted() const = 0;

        virtual size_t countNodes() const = 0;
        virtual size_t countEdges() const = 0;

        virtual void setNodeDescription(size_t index, const NodeDescription& description) = 0;
        virtual void setNodeDescriptions(const std::initializer_list<NodeDescription> list) = 0;
        virtual std::optional<NodeDescription> getNodeDescription(size_t index) = 0;

        virtual std::string toString() const = 0;
    };

    // -------------------------------------------------------------------------------------

    template<typename T>
    class GraphNode
    {
    public:
        // TODO: Hmmm, das sollte irgendwie generell global oder überhaupt nicht deklariert werden
        // type alias for the container type used to store the adjacency list
        using adjacency_list_type = std::set<size_t>;

    private:
        T m_data;
        std::set<size_t> m_adjacentNodeIndices;

    public:
        // constructs a graph_node for the given value
        GraphNode(const T& data)
            : m_data{ data } { }

        GraphNode(T&& data)
            : m_data{ std::move(data) } { }

        // returns a reference to the stored value
        T& value() noexcept { return m_data; }

        const T& value() const noexcept { return m_data; }

   // private:
   // 
   // TODO: Das sollte möglicherweise nur die const Version ausreichen
   // 
        // returns a reference to the adjacency list
        adjacency_list_type& get_adjacent_nodes_indices()
        {
            return m_adjacentNodeIndices;
        }

        const adjacency_list_type& get_adjacent_nodes_indices() const
        {
            return m_adjacentNodeIndices;
        }
    };


    // -------------------------------------------------------------------------------------


    template<typename T>
    class Graph
    {
    private:
        friend GraphNode<T>;  // hmm, wo wird da in GraphNode reingelangt ....

        using nodes_container_type = std::vector<GraphNode<T>>;

        nodes_container_type m_nodes;

    public:
        // For an insert to be successful, the value shall not be in the graph yet. 
        // Returns true if a new node with given value has been added to
        // the graph, and false if there was already a node with the given value.
        
        bool addNode(const T& node_value) {
            T copy{ node_value };
            
            // return addNode(std::move(copy));

            return true;
        }

        bool addNode(T&& node_value) {
            auto iter{ findNode(node_value) };

            if (iter != std::end(m_nodes)) {
                // Value is already in the graph, return false.
                return false;
            }

            m_nodes.emplace_back(std::move(node_value));

            // Value successfully added to the graph, return true.
            return true;
        }

        // Returns true if the edge was successfully created, false otherwise.
        bool insertEdge(const T& from_node_value, const T& to_node_value)
        {
            const auto from{ findNode(from_node_value) };

            const auto to{ findNode(to_node_value) };

            if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
                return false;
            }

            const size_t to_index{ get_index_of_node(to) };

            // return from->get_adjacent_nodes_indices().insert(to_index).second;

            std::set<size_t>& list = from->get_adjacent_nodes_indices();

            auto [pos, succeeded] = list.insert(to_index);

            return succeeded;
        }

        // Returns a reference to the node with given index.
        // No bounds checking is done.
        T& operator[](size_t index)
        {
            return m_nodes[index].value();
        }

        const T& operator[](size_t index) const
        {
            return m_nodes[index].value();
        }

        // Returns the number of nodes in the graph.
        size_t size() const noexcept
        {
            return m_nodes.size();
        }

        // Returns a set with the adjacent nodes of a given node.
        // If the given node does not exist, an empty set is returned.
        std::set<T> get_adjacent_nodes_values(const T& node_value) const
        {
            auto iter{ findNode(node_value) };

            if (iter == std::end(m_nodes)) {
                return std::set<T>{};
            }

            return get_adjacent_nodes_values(iter->get_adjacent_nodes_indices());
        }

    //private:
    //    friend GraphNode<T>;

    //    using nodes_container_type = std::vector<GraphNode<T>>;

    //    nodes_container_type m_nodes;

        // Helper method to return an iterator to the given node, or the end iterator
        // if the given node is not in the graph.
        typename nodes_container_type::iterator findNode(const T& node_value)
        {
            //return std::find_if(
            //    std::begin(m_nodes), 
            //    std::end(m_nodes),
            //    [&node_value](const auto& node) {
            //        return node.value() == node_value;
            //    }
            //);

            // for testing separated in several statements

            auto pos = std::find_if(
                std::begin(m_nodes),
                std::end(m_nodes),
                [&node_value](const auto& node) {
                    return node.value() == node_value;
                }
            );

            return pos;
        }

        typename nodes_container_type::const_iterator findNode(const T& node_value) const
        {
            return const_cast<Graph<T>*>(this)->findNode(node_value);
        }

        // Given a set of adjacency node indices, returns the corresponding
        // set of node values.
        std::set<T> get_adjacent_nodes_values(
            const typename GraphNode<T>::adjacency_list_type& indices) const
        {
            std::set<T> values;

            for (auto&& index : indices)
            {
                values.insert(m_nodes[index].value());
            }

            return values;
        }

        // Given an iterator to a node, returns the index of that node in the nodes container.
        size_t get_index_of_node(const typename nodes_container_type::const_iterator& node) const noexcept
        {
            const auto index{ std::distance(std::cbegin(m_nodes), node) };

            return static_cast<size_t>(index);
        }
    };


    // -------------------------------------------------------------------------------------

// Returns a given graph in DOT format.
    template <typename T>
    std::string toDot(const Graph<T>& graph, std::string_view graph_name)
    {
        std::stringstream ss;

        ss << std::format("digraph {} {{", graph_name.data()) << std::endl;

        for (size_t index{ 0 }; index < graph.size(); ++index)
        {
            const auto& node_value{ graph[index] };

            const auto adjacent_nodes{ graph.get_adjacent_nodes_values(node_value) };

            if (adjacent_nodes.empty())
            {
                ss << node_value << std::endl;
            }
            else
            {
                for (auto&& node : adjacent_nodes)
                {
                    ss << std::format("{} -> {}", node_value, node) << std::endl;
                }
            }
        }
        ss << "}" << std::endl;

        return ss.str();
    }
}

// =====================================================================================


namespace Graph_Theory_Graphs
{
    using namespace Graph_Theory_Redesign;

    // testing only graphs
    // a) Undirected, Unweighted, No Node Descriptions
    // b) Undirected, Unweighted, Node Descriptions
    // c) Directed,   Unweighted, No Node Descriptions
    // d) Directed,   Unweighted, Node Descriptions
    // 
    // Same with Weighted Graphs - To be Done


    void test_00()
    {
        Graph<int> graph;

        // Insert some nodes and edges.

        graph.addNode(11);
        graph.addNode(22);
        graph.addNode(33);
        graph.addNode(44);
        graph.addNode(55);

        graph.insertEdge(11, 33);
        graph.insertEdge(22, 33);
        graph.insertEdge(22, 44);
        graph.insertEdge(22, 55);
        graph.insertEdge(33, 44);
        graph.insertEdge(44, 55);

        std::string dot = toDot<int>(graph, "Beispiel");

        std::cout << dot << std::endl;
    }

    //void test_a()
    //{
    //    std::cout << "Undirected, Unweighted, No Node Descriptions" << std::endl;

    //    Graph graph{ 4 };

    //    graph.addEdge(0, 1);
    //    graph.addEdge(1, 2);
    //    graph.addEdge(2, 3);
    //    graph.addEdge(3, 0);

    //    std::cout << graph << std::endl;
    //}

    void test_b()
    {
        std::cout << "Undirected, Unweighted, Node Descriptions" << std::endl;

        // TODO: Klären, ob ein Konstruktor mit der Knotenanzahl Sinn ergibt
      //  Graph<std::string> graph{ 4 };
        Graph<std::string> graph;

        graph.addNode(std::string {"A"});
        graph.addNode(std::string {"B"});
        graph.addNode(std::string {"C"});
        graph.addNode(std::string {"D"});

        //graph.setNodeDescriptions({
        //    std::string{"A"},
        //    std::string{"B"},
        //    std::string{"C"},
        //    std::string{"C"}
        //    }
        //);

        //graph.insertEdge(0, 1);
        //graph.insertEdge(1, 2);
        //graph.insertEdge(2, 3);
        //graph.insertEdge(3, 0);

        graph.insertEdge(std::string {"A"}, std::string {"B"});
        graph.insertEdge(std::string {"B"}, std::string {"C"});
        graph.insertEdge(std::string {"C"}, std::string {"C"});
        graph.insertEdge(std::string {"C"}, std::string {"A"});

        std::string dot = toDot<std::string>(graph, "Beispiel");

        std::cout << dot << std::endl;
    }

    //void test_c()
    //{
    //    std::cout << "Directed, Unweighted, No Node Descriptions" << std::endl;

    //    UnweightedDirectedGraphAdjListRepresentation<int> graph{ 4 };

    //    graph.addEdge(0, 1);
    //    graph.addEdge(1, 2);
    //    graph.addEdge(2, 3);
    //    graph.addEdge(3, 0);

    //    std::cout << graph << std::endl;
    //}

    //void test_d()
    //{
    //    std::cout << "Directed, Unweighted, Node Descriptions" << std::endl;

    //    UnweightedDirectedGraphAdjListRepresentation<std::string> graph{ 4 };

    //    graph.setNodeDescriptions({
    //        std::string{"A"}, std::string{"B"}, std::string{"C"}, std::string{"C"}
    //        });

    //    graph.addEdge(0, 1);
    //    graph.addEdge(1, 2);
    //    graph.addEdge(2, 3);
    //    graph.addEdge(3, 0);

    //    std::cout << graph << std::endl;
    //}

    void test_graphs()
    {
        test_00();
    }
}


// =====================================================================================


//
//namespace Graph_Theory_DFS
//{
//    using namespace Graph_Theory_Redesign;
//
//
//    template <typename NodeDescription>
//    class DFSSolver
//    {
//    private:
//        Graph<NodeDescription>& m_graph;
//        std::vector<bool>                                 m_visited;
//        std::deque<std::vector<size_t>>                   m_paths;
//
//        std::vector<size_t>                               m_components;
//        size_t                                            m_count;
//
//    public:
//        DFSSolver(Graph<NodeDescription>& graph)
//            : m_graph{ graph }, m_count{} {}
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
//            std::vector<size_t> neighbours = m_graph.getNeighbouringNodes(source);
//
//            for (size_t next : neighbours) {
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
//                std::vector<size_t> neighbours = m_graph.getNeighbouringNodes(source);
//
//                for (size_t next : neighbours) {
//
//                    // next is not discovered
//                    if (!m_visited.at(next)) {
//                        path.push_back(next);  // include current node in the path
//                        findPathAllHelper(next, target, path);
//                        path.pop_back();  // remove current node from the path (backtrack)
//                    }
//                }
//
//                // unmark current node as discovered
//                m_visited.at(source) = false;
//            }
//        }
//    };
//
//    // DFS - all paths - UNDIRECTED Graph - NOT WEIGHTED
//    void test_dfs_01()
//    {
//        std::cout << "Redesign Graph Theory - DFS" << std::endl;
//
//        Graph<int> graph{ 8 };
//
//        graph.addEdge(0, 3);
//        graph.addEdge(1, 0);
//        graph.addEdge(1, 2);
//        graph.addEdge(1, 4);
//        graph.addEdge(2, 7);
//        graph.addEdge(3, 4);
//        graph.addEdge(3, 5);
//        graph.addEdge(4, 3);
//        graph.addEdge(4, 6);
//        graph.addEdge(5, 6);
//        graph.addEdge(6, 7);
//
//        DFSSolver dfs{ graph };
//
//        constexpr size_t Source{ 1 };
//        constexpr size_t Target{ 6 };
//
//        dfs.findPathAll(Source, Target);
//
//        if (size_t count; (count = dfs.countFoundPaths()) != 0)
//        {
//            std::cout << "Found " << count << " solutions:" << std::endl;
//            dfs.printPaths();
//        }
//        else {
//            std::cout << "No path exists between vertices " << Source << " and " << Target;
//        }
//    }
//}

// =====================================================================================
// End-of-File
// =====================================================================================

