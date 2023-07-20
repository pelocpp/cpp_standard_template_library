// =====================================================================================
// Graph Theory Redesign // Summer 2023
// =====================================================================================

#pragma once

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
#include <optional>
#include <stdexcept>
#include <cstddef>

// =====================================================================================

namespace Graph_Theory_Redesign
{
    // hmmm, muss das mit der Vorbelegung sein ...
    //template <typename NodeDescription>
    //class IGraphRepresentation
    //{
    //public:
    //    virtual bool isDirected() const = 0;
    //    virtual bool isWeighted() const = 0;

    //    virtual size_t countNodes() const = 0;
    //    virtual size_t countEdges() const = 0;

    //    virtual void seTNodeData(size_t index, const NodeDescription& description) = 0;
    //    virtual void seTNodeDatas(const std::initializer_list<NodeDescription> list) = 0;
    //    virtual std::optional<NodeDescription> geTNodeData(size_t index) = 0;

    //    virtual std::string toString() const = 0;
    //};

    // -------------------------------------------------------------------------------------


    // TODO:
    // Hmmm, eigentlich müsste das man in der Klasse GraphNode verstecken ...
    // Obwohl es ein Rückgabeparameter ist
    // Aber:
    // Mit den Iterator-Datentypen wird es in C++ genau so gemacht !!!

    // Fazit : Sollte in die Klasse GraphNode verlagert werden

    using EmptyType = std::nullptr_t;  //   hmm, void geht nicht ...

    template<typename Weight>
    using Edge = std::pair<size_t, std::optional<Weight>>;

    // needed as key compare function for std::set
    template<typename Weight = EmptyType>
    auto cmp = [](Edge<Weight> edge1, Edge<Weight> edge2) {
        
        auto [key1, weight1] = edge1;
        auto [key2, weight2] = edge2;

        return key1 < key2;
    };

    template<typename Weight = EmptyType>
    using AdjacencyListType = std::set<Edge<Weight>, decltype(cmp<Weight>)>;

    // -------------------------------------------------------------------------------------

    template<typename T, typename W = EmptyType>
    class GraphNode
    {
    public:
        // added: PeLo -  wird derzeit noch nicht benötigt
        using GraphNodeValueType = T;
        using GraphNodeWeightType = W;

    private:
        T m_data;
        AdjacencyListType<W> m_adjacentNodes;

    public:
        // constructing a graph_node for a given value
        GraphNode(const T& data) : m_data{ data } { }

        GraphNode(T&& data) : m_data{ std::move(data) } { }

        // returns a reference to the stored value
        T& value() noexcept { return m_data; }
        const T& value() const noexcept { return m_data; }

        // private:
        // 
        // TODO: Das sollte möglicherweise nur die const Version ausreichen
        // 
             
        // returns a reference to the adjacency list


        const AdjacencyListType<W>& getAdjacentNodes() const
        {
            return m_adjacentNodes;
        }

        AdjacencyListType<W>& getAdjacentNodes()
        {
            return m_adjacentNodes;
        }

        // needed for constructing stl set container with 'GraphNode' objects
        bool operator< (const GraphNode& other) {

            return m_data < other.m_data;
        }
    };

    // -------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------
    // -------------------------------------------------------------------------------------

    enum class Direction { Directed, Undirected };
    enum class Weight { Weighted, Unweighted };

    template<typename T, typename W>
    using NodesContainerType = std::vector<GraphNode<T, W>>;

    // -------------------------------------------------------------------------------------

    template<typename T, typename W = EmptyType>
    class Graph
    {
        // added: PeLo -  wird derzeit noch nicht benötigt
        using GraphNodeValueType = T;
        using GraphNodeWeightType = W;

    private:
        NodesContainerType<T, W> m_nodes;
        Direction m_isDirected;
        Weight m_isWeighted;

    public:
        Graph() : Graph{ Direction::Directed, Weight::Unweighted } {}

        Graph(Direction isDirected, Weight isWeighted = Weight::Unweighted) {
            m_isDirected = isDirected;
            m_isWeighted = isWeighted;
        }

    private:
        bool addNode(const T& data) {

            auto iter{ findNode(data) };

            if (iter != std::end(m_nodes)) {
                // value is already in the graph, return false
                return false;
            }

            T copy{ data };
            m_nodes.emplace_back(std::move(copy));
            return true;
        }

        void sort() {

            std::sort(
                std::begin(m_nodes),
                std::end(m_nodes)
            );
        }

    public:
        void addNodes(const std::initializer_list<T> list) {

            std::for_each(
                list.begin(),
                list.end(),
                [&](const auto& data) {
                    addNode(data);
                }
            );

            sort();
        }


        // TODO: Allgemein: Es müssen / sollten 2 Varianten an Methoden vorhanden sein:
        // addEdge mit Indices
        // addEdge mit Werten von Knoten
        // Oder auch nicht ...


        // Returns true if the edge was successfully created, false otherwise.
        bool addEdge(const T& fromNode, const T& toNode)
        {
            if (m_isWeighted == Weight::Weighted) {
                throw std::logic_error("Graph should be unweighted!");
            }

            const auto from{ findNode(fromNode) };

            const auto to{ findNode(toNode) };

            if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
                return false;
            }

            const size_t toIndex{ getIndexOfNode(to) };

            AdjacencyListType<W>& fromList = from->getAdjacentNodes();

            Edge<W> edge{toIndex, std::nullopt};

            auto [pos, succeeded] = fromList.insert(edge);

            if (succeeded) {

                if (m_isDirected == Direction::Undirected) {

                    GraphNode<T, W>& target = m_nodes[toIndex];

                    AdjacencyListType<W>& toList = target.getAdjacentNodes();

                    const size_t fromIndex{ getIndexOfNode(from) };

                    Edge<W> edge{fromIndex, std::nullopt};

                    auto [pos, succeeded] = toList.insert(edge);

                    return succeeded;
                }
                else {
                    return true;
                }
            }
            else {
                return false;
            }
        }

        bool addEdge(const T& fromNode, const T& toNode, const W& weight) {

            if (m_isWeighted == Weight::Unweighted) {
                throw std::logic_error("Graph should be weighted!");
            }

            const auto from{ findNode(fromNode) };

            const auto to{ findNode(toNode) };

            if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
                return false;
            }

            const size_t toIndex{ getIndexOfNode(to) };

            AdjacencyListType<W>& list = from->getAdjacentNodes();

            Edge<W> edge{toIndex, weight};

            auto [pos, succeeded] = list.insert(edge);

            return succeeded;
        }

        // Returns a reference to the node with given index.
        // No bounds checking is done.


        // ACHTUNG: Da sollte eigentlich nur die CONST Version gehen.
        // Es wird eine Referenz eines NODES zurückgeliefert !!!!!!!!!!!!!!!!!!!

        GraphNode<T, W>& operator[](size_t index)
        {
            return m_nodes[index];
        }

        const GraphNode<T, W>& operator[](size_t index) const
        {
            return m_nodes[index];
        }

        // Returns the number of nodes in the graph.
        size_t countNodes() const noexcept
        {
            return m_nodes.size();
        }

        AdjacencyListType<W>& getAdjacentNodes(   const  T& node_value) // const
        {
            static AdjacencyListType<W> empty {};

            auto node{ findNode(node_value) };

            if (node == std::end(m_nodes)) {

                return empty;
            }

            return node->getAdjacentNodes();
        }

        const AdjacencyListType<W>& getAdjacentNodes(const T& node_value) const
        {
            return const_cast<Graph<T, W>*>(this)->getAdjacentNodes(node_value);
        }




        //private:
        //    friend GraphNode<T>;

        //    using nodes_container_type = std::vector<GraphNode<T>>;

        //    nodes_container_type m_nodes;



            // Helper method to return an iterator to the given node, or the end iterator
            // if the given node is not in the graph.
            // typename nodes_container_type::iterator findNode(const T& node_value)
        typename NodesContainerType<T, W>::iterator findNode(const T& node_value)
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

        //typename nodes_container_type::const_iterator findNode(const T& node_value) const
        typename NodesContainerType<T, W>::const_iterator findNode(const T& node_value) const
        {
            return const_cast<Graph<T,W>*>(this)->findNode(node_value);
        }

        // Given a set of adjacency node indices, returns the corresponding
        // set of node values.



        // Given an iterator to a node, returns the index of that node in the nodes container.
        // size_t getIndexOfNode(const typename nodes_container_type::const_iterator& node) const noexcept
        size_t getIndexOfNode(const typename NodesContainerType<T, W>::const_iterator& node) const noexcept
        {
            const auto index{ std::distance(std::cbegin(m_nodes), node) };

            return static_cast<size_t>(index);
        }

        // added: PeLo - NEU

        // eher nicht benötigt - ich arbeite nicht Index Orientiert ...................
        //T getNodeData(size_t index) {
        //    return m_nodes[index].value();
        //}

        Direction isDirected() const { return m_isDirected; }

        Weight isWeighted() const { return m_isWeighted; }

        size_t countEdges() const
        {
            size_t count = 0;
            std::for_each(
                std::begin(m_nodes),
                std::end(m_nodes),
                [&](const auto& node) {

                    const AdjacencyListType<W>& list = node.getAdjacentNodes();

                    count += list.size();
                }
            );
            // return (isDirected()) ? count : count / 2;
            return count;
        }

        //typename GraphNode<T>::adjacency_list_type& getAdjacentNodesIndices(size_t index)
        //{
        //    return m_nodes[index].getAdjacentNodesIndices();
        //}

        //const typename GraphNode<T>::adjacency_list_type& getAdjacentNodesIndices(size_t index) const
        //{
        //    return m_nodes[index].getAdjacentNodesIndices();
        //}

        // TODO: Diese Methoden liefern ALLES zurück : Index und Gewicht (std::optional)
        // TODO: Wird da eine zweite MEthode benötigt, die nur die Indices zurück liefert ?????

        //AdjacencyListType<W>& getAdjacentNodesIndices(size_t index)
        //{
        //    return m_nodes[index].getAdjacentNodesIndices();
        //}

        //AdjacencyListType<W>& getAdjacentNodesIndices(size_t index) const
        //{
        //    return m_nodes[index].getAdjacentNodesIndices();
        //}

    };

    // -------------------------------------------------------------------------------------

    // Returns a given graph in DOT format.

    // TODO: Der graph Parameter ist im Original als const markiert ....

    //template <typename T, typename W = EmptyType>
    //std::string toDot(Graph<T, W>& graph, std::string_view graph_name)
    //{
    //    std::stringstream ss;

    //    ss << std::format("Graph {} {{", graph_name.data()) << std::endl;

    //    for (size_t index{ }; index < graph.countNodes(); ++index)
    //    {
    //        GraphNode<T, W>& node{ graph[index] };  // da steht im Original ein const vorne ....

    //        T& value = node.value();

    //        // KORREKT
    //        //  const auto adjacent_nodes{ graph.get_adjacent_nodes_values(node_value) };

    //        // mit oder ohne Referenz !!!
    //        const AdjacencyListType<W>& adjacent_nodes{ node.getAdjacentNodes() };

    //        if (adjacent_nodes.empty())
    //        {
    //            ss << value << std::endl;  // TODO: Wiederholung
    //        }
    //        else
    //        {
    //            ss << value << ": ";   // TODO: Wiederholung

    //            for (size_t columns{}; auto & [target, weight] : adjacent_nodes)
    //            {
    //                ss << index << " -> " << target;

    //                if (weight.has_value()) {

    //                    ss << "  { " << weight.value() << " }";
    //                }

    //                if (columns != adjacent_nodes.size() - 1) {
    //                    ss << " | ";
    //                }

    //                ++columns;

    //                // ss << std::format("{} -> {}", node_value, node) << std::endl;   // TODO: Vielleicht auf format umsteigen ...
    //            }

    //            ss << std::endl;
    //        }
    //    }
    //    ss << "}" << std::endl;

    //    return ss.str();
    //}


    template <typename T, typename W>
    std::string toString(const Graph<T, W>& graph) {

        std::string separator{ graph.isDirected() == Direction::Directed ? " -> " : " <=> " };

        std::ostringstream oss;
        oss << "Graph: " << std::endl;
        oss << "  Nodes: " << graph.countNodes() << ", Edges: " << graph.countEdges() << std::endl;
        oss << "  " << (graph.isDirected() == Direction::Directed ? "Directed" : "Undirected");
        oss << "  " << (graph.isWeighted() == Weight::Weighted ? "Weighted" : "Unweighted") << std::endl << std::endl;

        // Original:
        // for (size_t source = 0; const std::vector<size_t>&list : graph.m_adjacencyList) {

        for (size_t index{ 0 }; index < graph.countNodes(); ++index)
        {
            // auto& node{ graph[index] };  // da steht im Original ein const vorne ....
            const GraphNode<T, W>& node{ graph[index] };  // da steht im Original ein const vorne ....

            const T& fromValue = node.value();

            using NodeType = std::remove_cv<T>::type;

            if constexpr (!std::is_same<NodeType, std::string>::value) {
                std::string s{ std::to_string(fromValue) };
                oss << "[" << /* std::setw(12) << std::left << */ s << "] ";
            }
            else {
                oss << "[" << /* std::setw(12) << std::left << */ fromValue << "] ";
            }

            const AdjacencyListType<W> list = graph.getAdjacentNodes(fromValue);

            // const&
            // OFFEN: Wie und wo wird das weight ausgegeben
            for (size_t n = 0; const auto& [next, weight] : list) {

                const T& toValue = graph[next].value();

                oss << fromValue << separator << toValue;

                if (n != list.size() - 1) {
                    oss << " | ";
                }
                ++n;
            }

            // WEITER: hier müssen die Knoten ... und nicht die Indices ausgegeben werden


            oss << std::endl;
            
            for (size_t columns{}; auto& [target, weight] : list)
            {
                oss << index << " -> " << target;

                if (weight.has_value()) {

                    oss << "  { " << weight.value() << " }";
                }

                if (columns != list.size() - 1) {
                    oss << " | ";
                }

                ++columns;

                // ss << std::format("{} -> {}", node_value, node) << std::endl;   // TODO: Vielleicht auf format umsteigen ...
            }

            oss << std::endl;
        }

        return oss.str();
    }
}

// =====================================================================================

// =====================================================================================
// End-of-File
// =====================================================================================

