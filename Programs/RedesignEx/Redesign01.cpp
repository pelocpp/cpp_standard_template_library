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

    template<typename T>
    class GraphNode
    {
    private:
        // type alias for the container type used to store the adjacency list.
        using adjacency_list_type = std::set<size_t>;

    private:
        T m_data;
        std::set<size_t> m_adjacentNodeIndices;

    public:
        // constructs a graph_node for the given value
        GraphNode(const T& t);
        GraphNode(T&& t);

        // returns a reference to the stored value
        T& value() noexcept;
        const T& value() const noexcept;

    private:
        // returns a reference to the adjacency list
        adjacency_list_type& get_adjacent_nodes_indices();
        const adjacency_list_type& get_adjacent_nodes_indices() const;
    };

    template<typename T>
    class Graph
    {
    public:
        // For an insert to be successful, the value shall not be in the graph yet. 
        // Returns true if a new node with given value has been added to
        // the graph, and false if there was already a node with the given value.
        bool insert(const T& node_value);
        bool insert(T&& node_value);

        // Returns true if the edge was successfully created, false otherwise.
        bool insert_edge(const T& from_node_value, const T& to_node_value);

        // Returns a reference to the node with given index.
        // No bounds checking is done.
        T& operator[](size_t index);
        const T& operator[](size_t index) const;

        // Returns the number of nodes in the graph.
        size_t size() const noexcept;

        // Returns a set with the adjacent nodes of a given node.
        // If the given node does not exist, an empty set is returned.
        std::set<T> get_adjacent_nodes_values(const T& node_value) const;

    private:
        friend GraphNode<T>;

        using nodes_container_type = std::vector<GraphNode<T>>;

        nodes_container_type m_nodes;

        // Helper method to return an iterator to the given node, or the end iterator
        // if the given node is not in the graph.
        typename nodes_container_type::iterator findNode(const T& node_value);
        typename nodes_container_type::const_iterator findNode(const T& node_value) const;

        // Given a set of adjacency node indices, returns the corresponding
        // set of node values.
        std::set<T> get_adjacent_nodes_values(
            const typename GraphNode<T>::adjacency_list_type& indices) const;

        // Given an iterator to a node, returns the index of that node in the nodes container.
        size_t get_index_of_node(const typename nodes_container_type::const_iterator& node) const noexcept;
    };
}

// =====================================================================================

namespace Graph_Theory_DFS
{
    using namespace Graph_Theory_Redesign;


    template <typename NodeDescription>
    class DFSSolver
    {
    private:
        Graph<NodeDescription>& m_graph;
        std::vector<bool>                                 m_visited;
        std::deque<std::vector<size_t>>                   m_paths;

        std::vector<size_t>                               m_components;
        size_t                                            m_count;

    public:
        DFSSolver(Graph<NodeDescription>& graph)
            : m_graph{ graph }, m_count{} {}

        void computeComponents() {

            m_visited.resize(m_graph.countNodes());
            std::fill(std::begin(m_visited), std::end(m_visited), false);

            m_components.resize(m_graph.countNodes());
            std::fill(std::begin(m_components), std::end(m_components), 0);

            m_count = 0;

            for (size_t node{}; node != m_graph.countNodes(); ++node) {
                if (!m_visited.at(node)) {
                    ++m_count;
                    depthFirstSearch(node);
                }
            }
        }

        size_t getNumberOfComponents() const { return m_count; }

        std::vector<size_t> getComponent(size_t mark) const {

            std::vector<size_t> result;

            for (size_t index{}; size_t vertex : m_components) {

                if (vertex == mark) {
                    result.push_back(index);
                }

                ++index;
            }

            return result;
        }

        size_t countFoundPaths() { return m_paths.size(); }

        // function to perform DFS traversal in a directed graph to find
        // the complete path between source and destination vertices
        bool findPathAny(size_t source, size_t target, std::vector<size_t>& path) {

            // setup 'm_visited' vector
            m_visited.resize(m_graph.countNodes());
            std::fill(std::begin(m_visited), std::end(m_visited), false);

            return findPathAnyHelper(source, target, path);
        }

        void findPathAll(size_t source, size_t target) {

            // setup 'm_visited' vector
            m_visited.resize(m_graph.countNodes());
            std::fill(std::begin(m_visited), std::end(m_visited), false);

            // setup 'currentPath' vector
            std::vector<size_t> currentPath;
            currentPath.push_back(source);

            findPathAllHelper(source, target, currentPath);
        }

        void printPath(const std::vector<size_t>& path) {

            std::for_each(
                std::begin(path),
                std::prev(std::end(path)),
                [](auto vertex) { std::cout << vertex << " -> "; }
            );

            auto last = path.back();
            std::cout << last << std::endl;
        }

        void printPaths() {
            for (const auto& path : m_paths) {
                printPath(path);
            }
        }

    private:
        void depthFirstSearch(size_t node) {

            m_visited.at(node) = true;          // mark current node as discovered
            m_components.at(node) = m_count;    // set mark

            // do for all adjacent vertices of the current vertex
            std::vector<size_t> neighbours = m_graph.getNeighbouringNodes(node);
            for (size_t next : neighbours) {

                // next is not discovered
                if (!m_visited.at(next)) {

                    depthFirstSearch(next);
                }
            }
        }

        bool findPathAnyHelper(size_t source, size_t target, std::vector<size_t>& path) {

            // mark current node as discovered
            m_visited.at(source) = true;

            // include current node in the path
            path.push_back(source);

            // if destination vertex is found
            if (source == target) {
                return true;
            }

            // do for all adjacent vertices of the dequeued vertex
            std::vector<size_t> neighbours = m_graph.getNeighbouringNodes(source);

            for (size_t next : neighbours) {

                // next is not discovered
                if (!m_visited.at(next)) {

                    // return true if destination is found
                    if (findPathAnyHelper(next, target, path))
                        return true;
                }
            }

            // backtrack: remove current node from the path
            path.pop_back();

            // return false if destination vertex is not reachable from source
            return false;

        }

        void findPathAllHelper(size_t source, size_t target, std::vector<size_t>& path) {

            // mark current node as discovered
            m_visited.at(source) = true;

            // if destination vertex is found
            if (source == target) {
                m_paths.push_back(path); // store found solution
                m_visited.at(source) = false;  // unmark current node as discovered
            }
            else {
                // do for every edge
                std::vector<size_t> neighbours = m_graph.getNeighbouringNodes(source);

                for (size_t next : neighbours) {

                    // next is not discovered
                    if (!m_visited.at(next)) {
                        path.push_back(next);  // include current node in the path
                        findPathAllHelper(next, target, path);
                        path.pop_back();  // remove current node from the path (backtrack)
                    }
                }

                // unmark current node as discovered
                m_visited.at(source) = false;
            }
        }
    };

    // DFS - all paths - UNDIRECTED Graph - NOT WEIGHTED
    void test_dfs_01()
    {
        std::cout << "Redesign Graph Theory - DFS" << std::endl;

        Graph<int> graph{ 8 };

        graph.addEdge(0, 3);
        graph.addEdge(1, 0);
        graph.addEdge(1, 2);
        graph.addEdge(1, 4);
        graph.addEdge(2, 7);
        graph.addEdge(3, 4);
        graph.addEdge(3, 5);
        graph.addEdge(4, 3);
        graph.addEdge(4, 6);
        graph.addEdge(5, 6);
        graph.addEdge(6, 7);

        DFSSolver dfs{ graph };

        constexpr size_t Source{ 1 };
        constexpr size_t Target{ 6 };

        dfs.findPathAll(Source, Target);

        if (size_t count; (count = dfs.countFoundPaths()) != 0)
        {
            std::cout << "Found " << count << " solutions:" << std::endl;
            dfs.printPaths();
        }
        else {
            std::cout << "No path exists between vertices " << Source << " and " << Target;
        }
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
