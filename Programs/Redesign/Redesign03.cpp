// =====================================================================================
// Graph Theory Redesign
// =====================================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <utility>
#include <algorithm>
#include <optional>
#include <queue>
#include <type_traits>

// TODO: final, override ... Vor allem final einsetzen, wenn man eine Methode nicht mehr überschreiben sollte

// TODO: Hier ist beschrieben, wie man in einer Klasse ZWEI ITeratoren unterbekommt:
// https://blog.cppse.nl/cpp-multiple-iterators-with-traits

// TODO:
// Man sollte die Klassen auch mit C++ Iteratoren ausstatten
// Dazu benötigt man das Thema "c++ implementing iterator as nested class"  ( Google Search ) !!!

// // TODO:
// ACHTUNG: Habe jetzt überall size_t verwendet - da geht aber -1 nicht !!!!!!!!!!!!!!!!!!!!

// TODO:
// Es sind derzeit keinerlei Fehlerberprüfungen drin: doppelte Kanten ... wieso wird da eigenlich nicht mehr eine std::set verwendet ????

// TWO PHASE LOOKUP !!!!
// https://www.modernescpp.com/index.php/surprise-included-inheritance-and-member-functions-of-class-templates
// HIER GEHT ES UM DAS using inmitten des Quellcode !!!!

// TODO: 
//// Die beiden Methoden 
//virtual void setNodeDescription(size_t index, const NodeDescription& description) = 0;
//virtual void setNodeDescriptions(const std::initializer_list<NodeDescription> list) = 0;
// sind derzeit doppelt implementiert ... das sollte man doch vermeiden
// 

// TODO:
// oss << "[" << std::setw(12) << std::left << description << "] ";
// Hier könnte man die maximale Feldbreite tatsächlich berechnen -- sieht dann doch besser aus ....
// ODer gleich mit std::format von C++ 20 arbeiten !!!!

// =====================================================================================

namespace Graph_Theory_Redesign
{
    // -------------------------------------------------------------

    using Edge = std::pair<size_t, size_t>;

    template<typename Weight>
    using WeightedEdge = std::tuple<size_t, size_t, Weight>;

    // TODO: Der wird nur bei Dijkstra verwendet ...
    template<typename Weight>
    using Track = std::pair<size_t, Weight>;

    template<typename Edge>
    size_t getSource(const Edge& edge) {
        return std::get<0>(edge);
    }

    template<typename Edge>
    size_t getTarget(const Edge& edge) {
        return std::get<1>(edge);
    }

    //size_t getSource(auto&& edge) {
    //    return std::get<0>(edge);
    //}

    //size_t getTarget(auto&& edge) {
    //    return std::get<1>(edge);
    //}

    template<typename Weight>
    auto getEdgeWeight(const WeightedEdge<Weight>& edge) {
        return std::get<2>(edge);
    }

    // -------------------------------------------------------------

    template <typename NodeDescription = int>
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

    // -------------------------------------------------------------

    template <typename NodeDescription = int>
    class IUnweightedGraphRepresentation : public IGraphRepresentation<NodeDescription>
    {
    public:
        virtual void addEdge(size_t, size_t) = 0;
        virtual void addEdge(const Edge&) = 0;
        virtual void addEdges(const std::initializer_list<Edge> list) = 0;
        virtual std::vector<Edge> getAllEdges() const = 0;
        virtual std::vector<size_t> getNeighbouringNodes(size_t) const = 0;
    };

    template <typename Weight, typename NodeDescription = int>
    class IWeightedGraphRepresentation : public IGraphRepresentation<NodeDescription>
    {
    public:
        virtual void addEdge(size_t, size_t, Weight) = 0;
        virtual void addEdge(const WeightedEdge<Weight>&) = 0;
        virtual void addEdges(const std::initializer_list<WeightedEdge<Weight>> list) = 0;
        virtual Weight getWeight(size_t n, size_t m) = 0;
        virtual std::vector<WeightedEdge<Weight>> getAllEdges() const = 0;
        virtual std::vector<WeightedEdge<Weight>> getNeighbouringEdges(size_t) const = 0;
        virtual std::vector<size_t> getNeighbouringNodes(size_t) const = 0;
    };

    // -------------------------------------------------------------

    template <typename NodeDescription = int>
    class UnweightedDirectedGraphAdjListRepresentation : public IUnweightedGraphRepresentation<NodeDescription>
    {
    protected:
        std::vector<std::vector<size_t>> m_adjacencyList;
        std::vector<std::optional<NodeDescription>> m_nodeDescription;

    public:
        UnweightedDirectedGraphAdjListRepresentation(size_t nodes) {
            m_adjacencyList.resize(nodes);
            m_nodeDescription.resize(nodes);
        }

        virtual bool isDirected() const override { return true; }
        virtual bool isWeighted() const override { return false; }

        virtual size_t countNodes() const final { return m_adjacencyList.size(); }
        virtual size_t countEdges() const final { return 0; } // TO BE DONE

        virtual void addEdge(size_t n, size_t m) override {
            m_adjacencyList[n].push_back(m);
        }

        virtual void addEdge(const Edge& edge) final {
            addEdge(getSource(edge), getTarget(edge));
        }

        virtual void addEdges(const std::initializer_list<Edge> list) final {
            for (const Edge& edge : list) {
                addEdge(edge);
            }
        }

        virtual void setNodeDescription(size_t index, const NodeDescription& description) {
            m_nodeDescription[index] = description;
        }

        virtual void setNodeDescriptions(const std::initializer_list<NodeDescription> list) {
            m_nodeDescription.insert(std::begin(m_nodeDescription), std::begin(list), std::end(list));
        }

        virtual std::optional<NodeDescription> getNodeDescription(size_t index) {
            return m_nodeDescription[index];
        }

        virtual std::vector<size_t> getNeighbouringNodes(size_t node) const override {
            return m_adjacencyList[node];
        }

        virtual std::vector<Edge> getAllEdges() const override {

            std::vector<Edge> edges;
            for (size_t row = 0; const auto & vertices : m_adjacencyList) {
                for (size_t column : vertices) {
                    edges.push_back({ row, column });
                }
            }
            return edges;
        }

        virtual std::string toString() const override {

            std::string separator{ isDirected() ? " -> " : " <=> " };

            std::ostringstream oss;
            for (size_t source = 0; const std::vector<size_t>& list : m_adjacencyList) {

                if (m_nodeDescription[source].has_value()) {
                    NodeDescription description = m_nodeDescription[source].value();

                    using T = std::remove_cv<NodeDescription>::type;
                    if constexpr (! std::is_same<T, std::string>::value) {
                        std::string s{ std::to_string(description) };
                        oss << "[" << /* std::setw(12) << */ std::left << s << "] ";
                    }
                    else {
                        oss << "[" << /* std::setw(12) << */ std::left << description << "] ";
                    }
                }
                else {
                    oss << "[" << source << "] ";
                }

                for (size_t index = 0; size_t target : list) {
                    oss << source << separator << target;
                    if (index != list.size() - 1) {
                        oss << " | ";
                    }
                    ++index;
                }

                oss << '\n';
                ++source;
            }

            return oss.str();
        }
    };

    template <typename NodeDescription = int>
    std::ostream& operator<< (std::ostream& os, UnweightedDirectedGraphAdjListRepresentation<NodeDescription> graph) {
        os << "Graph: Directed, Unweighted:" << std::endl;
        os << graph.toString();
        return os;
    }

    template <typename NodeDescription = int>
    class UnweightedUndirectedGraphAdjListRepresentation : public UnweightedDirectedGraphAdjListRepresentation<NodeDescription>
    {
    public:
        UnweightedUndirectedGraphAdjListRepresentation(size_t nodes) : UnweightedDirectedGraphAdjListRepresentation<NodeDescription>{ nodes } { }

        virtual bool isDirected() const final { return false; }
        virtual bool isWeighted() const final { return false; }

        virtual void addEdge(size_t n, size_t m) override {
            this->m_adjacencyList[n].push_back(m);
            this->m_adjacencyList[m].push_back(n);
        }
    };

    template <typename NodeDescription = int>
    std::ostream& operator<< (std::ostream& os, UnweightedUndirectedGraphAdjListRepresentation<NodeDescription> graph) {
        os << "Graph: Undirected, Unweighted:" << std::endl;
        os << graph.toString();
        return os;
    }

    // -------------------------------------------------------------

    template <typename Weight, typename NodeDescription = int>
    class WeightedDirectedGraphAdjListRepresentation : public IWeightedGraphRepresentation<Weight, NodeDescription>
    {
    protected:
        std::vector<std::vector<std::optional<Weight>>> m_adjacencyList;
        std::vector<std::optional<NodeDescription>> m_nodeDescription;

    public:
        WeightedDirectedGraphAdjListRepresentation(size_t nodes)
            : m_adjacencyList{ std::vector<std::vector<std::optional<Weight>>>(nodes, std::vector<std::optional<Weight>>(nodes, std::nullopt)) }
        {
           // m_adjacencyList.resize(nodes);  // TODO HIer habe ich den Faden verloren: Geht das in der Liste oder im Rumpf vom c'tor
            m_nodeDescription.resize(nodes);
        }

        virtual bool isDirected() const override { return true; }
        virtual bool isWeighted() const override { return true; }

        virtual size_t countNodes() const final { return m_adjacencyList.size(); }
        virtual size_t countEdges() const final { return 0; } // TO BE DONE

        virtual void addEdge(size_t n, size_t m, Weight weight) override
        {
            m_adjacencyList[n][m] = weight;
        }

        virtual void addEdge(const WeightedEdge<Weight>& edge) final {
            addEdge(getSource(edge), getTarget(edge), getEdgeWeight<Weight>(edge));
        }

        virtual void addEdges(const std::initializer_list<WeightedEdge<Weight>> list) final {
            for (const WeightedEdge<Weight>& edge : list) {
                addEdge(edge);
            }
        }

        virtual Weight getWeight(size_t n, size_t m) final {
            return m_adjacencyList[n][m].value();
        }

        virtual void setNodeDescription(size_t index, const NodeDescription& description) {
            m_nodeDescription[index] = description;
        }

        virtual void setNodeDescriptions(const std::initializer_list<NodeDescription> list) {
            m_nodeDescription.insert(std::begin(m_nodeDescription), std::begin(list), std::end(list));
        }

        virtual std::optional<NodeDescription> getNodeDescription(size_t index) {
            return m_nodeDescription[index];
        }

        virtual std::vector<size_t> getNeighbouringNodes(size_t node) const final {

            std::vector<size_t> neighbours;

            std::for_each(
                std::begin(m_adjacencyList[node]),
                std::end(m_adjacencyList[node]),
                [&, index = 0](const auto& entry) mutable {
                    if (entry.has_value()) {
                        neighbours.push_back(index);
                    }
                    ++index;
                }
            );

            return neighbours;
        }

        virtual std::vector<WeightedEdge<Weight>> getAllEdges() const final {
            std::vector<WeightedEdge<Weight>> edges;
            for (size_t row = 0; const auto & vertices : m_adjacencyList) {
                for (size_t column = 0; auto entry : vertices) {
                    if (entry.has_value()) {
                        edges.push_back({ row, column, entry.value() });
                    }
                    ++column;
                }
                ++row;
            }
            return edges;
        }

        virtual std::vector<WeightedEdge<Weight>> getNeighbouringEdges(size_t node) const final {

            std::vector<WeightedEdge<Weight>> edges;
            std::vector<std::optional<Weight>> row = m_adjacencyList[node];

            for (int column = 0; const auto& entry : row) {
                if (entry.has_value()) {
                    edges.push_back({ node, column, entry.value() });
                }
                ++column;
            }
            return edges;
        }

        virtual std::string toString() const override {
            std::ostringstream oss;
            oss << "To be Done!";
            return oss.str();
        }
    };

    template <typename Weight, typename NodeDescription = int>
    class WeightedUndirectedGraphAdjListRepresentation : public WeightedDirectedGraphAdjListRepresentation<Weight, NodeDescription>
    {
    public:
        // Siehe hier
        // https://www.modernescpp.com/index.php/surprise-included-inheritance-and-member-functions-of-class-templates

        // Das Problem taucht gleich ZWEIMAL auf !!!!
        // ein erstes Mal bzgl. der Zugriffs auf m_adjacencyList
        // ein zweites Mal beim Aufruf von addEdge im Anwendungsbeispiel

        using WeightedDirectedGraphAdjListRepresentation<Weight, NodeDescription>::addEdge;
        using WeightedDirectedGraphAdjListRepresentation<Weight, NodeDescription>::m_adjacencyList;

        WeightedUndirectedGraphAdjListRepresentation(size_t nodes) : WeightedDirectedGraphAdjListRepresentation<Weight, NodeDescription>{ nodes } { }

        virtual bool isDirected() const final { return false; }
        virtual bool isWeighted() const final { return true; }

        virtual void addEdge(size_t n, size_t m, Weight weight) override {

            //WeightedDirectedGraphAdjListRepresentation<Weight>::addEdge(n, m, weight);
            //WeightedDirectedGraphAdjListRepresentation<Weight>::addEdge(m, n, weight);

            // TODO: Warum lässt sich das nicht übersetzen ?!?!?! ES GEHT DOCH !!!!!! Siehe 10 Zeilen weiter obem
            m_adjacencyList[n][m] = weight;
            m_adjacencyList[m][n] = weight;
        }

        virtual std::string toString() const override {
            std::ostringstream oss;
            oss << "To be Done!";
            return oss.str();
        }
    };

    // -------------------------------------------------------------

    template <typename NodeDescription = int>
    class DFSSolver
    {
    private:
        IUnweightedGraphRepresentation<NodeDescription>& m_graph;    // ist für gerichtete oder ungerichtete Graphen ????
        std::vector<bool> m_visited;
        std::deque<std::vector<size_t>> m_paths;

    public:
        DFSSolver(IUnweightedGraphRepresentation<NodeDescription>& graph) : m_graph{ graph } {}

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

            // hier mit std::prev arbeiten !!!!
            std::for_each(std::begin(path), std::end(path) - 1, [](size_t vertex) {
                std::cout << vertex << " -> ";
                }
            );

            size_t last = *(std::end(path) - 1);
            std::cout << last << std::endl;
        }

        void printPaths() {
            for (const auto& path : m_paths) {
                printPath(path);
            }
        }

    private:
        bool findPathAnyHelper(size_t source, size_t target, std::vector<size_t>& path) {

            // mark current node as discovered
            m_visited.at(source) = true;

            // include current node in the path
            path.push_back(source);

            // if destination vertex is found
            if (source == target) {
                return true;
            }

            // do for all adjacent vertices of the dequeued vertex (source -> next)
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
                // do for every edge (source -> next)
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

    // -------------------------------------------------------------

    // BFS

    template <typename NodeDescription = int>
    class BFSSolver
    {
    private:
        IUnweightedGraphRepresentation<NodeDescription>& m_graph;   // TODO: zu klären: Ist dieser Algo für gerichtete oder ungerichtete Graphen ????
        std::deque<size_t> m_queue;
        std::vector<bool> m_visited;

    public:
        BFSSolver(IUnweightedGraphRepresentation<NodeDescription>& graph) : m_graph{ graph } {}

        std::vector<std::optional<size_t>> solve(size_t start) {

            // setup 'm_visited' vector
            m_visited.resize(m_graph.countNodes());
            std::fill(std::begin(m_visited), std::end(m_visited), false);
            m_visited.at(start) = true;

            // setup 'previous' vector
            std::vector<std::optional<size_t>> previous (m_graph.countNodes());
            std::fill(std::begin(previous), std::end(previous), std::nullopt);

            m_queue.push_back(start);
            while (!m_queue.empty()) {

                // dequeue a vertex from queue
                size_t node{ m_queue.front() };
                m_queue.pop_front();

                // get all adjacent vertices of the dequeued vertex
                std::vector<size_t> neighbours{ m_graph.getNeighbouringNodes(node) };
                for (size_t next : neighbours) {
                    if (!m_visited.at(next)) {
                        m_queue.push_back(next);
                        m_visited.at(next) = true;
                        previous.at(next) = node;
                    }
                }
            }

            return previous;
        }

        std::vector<size_t> reconstructPath(size_t source, size_t target, std::vector<std::optional<size_t>> prev) {

            std::vector<size_t> path;
            bool done{ false };
            size_t pos{ target };

            // reconstruct path going backwards from 'target'
            while (!done) {
                path.push_back(pos);
                if (prev.at(pos).has_value()) {
                    pos = prev.at(pos).value();
                }
                else {
                    done = true;
                }
            }

            // need to reverse the constructed path
            std::reverse(std::begin(path), std::end(path));

            // if 'source' and 'target' are connected, return the path
            return (path.at(0) == source) ? path : std::vector<size_t>{};
        }

        void printSolution(std::vector<size_t> path) {
            if (path.size() == 0) {
                std::cout << "No Solution found !" << std::endl;
            }
            else {
                std::for_each(
                    std::begin(path),
                    std::prev(std::end(path)), 
                    [&](size_t vertex) {
                        //  std::cout << "[" << vertex << "] => ";

                        std::optional<NodeDescription> description{ m_graph.getNodeDescription(vertex) };

                        if (description.has_value()) {

                            using T = std::remove_cv<NodeDescription>::type;

                            if constexpr (!std::is_same<T, std::string>::value) {
                                std::string s{ std::to_string(description.value()) };
                                std::cout << "[" << s << "] => ";
                            }
                            else {
                                std::cout << "[" << description.value() << "] => ";
                            }


                           // std::cout << "[" << vertex << "] => ";
                        }
                        else {
                            std::cout << "[" << vertex << "] => ";
                        }
                    }
                );

                // print last element without trailing comma :-)
                size_t vertex = path.back();
                // TODO: Hmmm, da muss man jetzt dieselbe std::optional Umwandlung machen wir kurz zuvor... das ist lästing
                // Da könnte man eine Methode konzipieren, die ein std::pair zurückliefert ... und structured binding verwendet....
                std::cout << "[" << vertex << "].";
            }
        }

        //using T = std::remove_cv<NodeDescription>::type;

        ////     oss << std::setw(10) << std::left;

        //if constexpr (!std::is_same<T, std::string>::value) {
        //    std::string s{ std::to_string(description) };
        //    oss << "[" << std::setw(12) << std::left << s << "] ";
        //}
        //else {
        //    oss << "[" << std::setw(12) << std::left << description << "] ";
        //}

    };

    // -------------------------------------------------------------

    // Dijkstra

    constexpr size_t MaxSize = static_cast<size_t>(-1);

    template <typename Weight, typename NodeDescription = int>
    class DijkstraSolver {
    private:
        IWeightedGraphRepresentation<Weight, NodeDescription>&  m_graph;
        std::vector<size_t>                    m_distances;
        size_t                                 m_start; // start vertex

    public:
        DijkstraSolver(IWeightedGraphRepresentation<Weight, NodeDescription>& graph) : m_graph{ graph }, m_start{} {}

        bool computeShortestPaths(size_t startVertex) {

            m_start = startVertex;
            m_distances.resize(m_graph.countNodes());

            // initialize all possible distances as infinite (-1)
            std::generate(std::begin(m_distances), std::end(m_distances), [] {
                return MaxSize;
                }
            );

            // need a lambda to compare Track elements
            auto compareTracks = [](const Track<size_t>& lhs, const Track<size_t>& rhs) {
                const auto& [idLeft, weightLeft] = lhs;
                const auto& [idRight, weightRight] = rhs;
                return weightLeft > weightRight;
            };

            // need a priority queue
            // note: the third template parameter should be the *type* of the comparison function;
            // the function itself is then passed as a parameter in the constructor of priority_queue!
            std::priority_queue <
                Track<Weight>,
                std::vector<Track<Weight> >,
                decltype(compareTracks) >
                pq(compareTracks);

            // add source to priority queue, distance is 0
            Track<Weight> startTrack{ m_start , 0 };

            pq.push(startTrack);

            m_distances[m_start] = 0;

            // while priority queue isn't empty...
            while (!pq.empty()) {

                // get minimum distance vertex from priority queue - we call it 'vertex'
                Track<Weight> track = pq.top();
                size_t vertex = track.first;
                pq.pop();

                // get all adjacent edges of the dequeued vertex
                std::vector<WeightedEdge<Weight>> edges = m_graph.getNeighbouringEdges(vertex);

                for (const WeightedEdge<Weight>& edge : edges) {

                    size_t target = getTarget(edge);
                    Weight weight = getEdgeWeight(edge);

                    // if the distance to 'target' is shorter by going through 'vertex' ...
                    if (m_distances[target] == MaxSize || m_distances[target] > m_distances[vertex] + weight) {

                        // update the distance of 'target'
                        m_distances[target] = m_distances[vertex] + weight;

                        // insert 'target' into the priority queue
                        Track<Weight> track{ target , m_distances[target] };
                        pq.push(track);
                    }
                }
            }

            return true;
        }

        std::vector<size_t> getDistances() {
            return m_distances;
        }

        void printDistances() {

            std::cout << "\nPrinting the shortest paths for node " << m_start << ".\n";

            for (size_t i = 0; i != m_graph.countNodes(); ++i) {
                // NODE_DETAILS targetLocation = getDetails<NODE_DETAILS>(node);
                std::cout
                    << "Distance from " << m_start
                    << " to " << i << " is: "
                    << m_distances[i] << std::endl;

            }
        }
    };

    // -------------------------------------------------------------

    template <typename Weight, typename NodeDescription = int>
    class KruskalSolver
    {
    private:
        IWeightedGraphRepresentation<Weight, NodeDescription>&  m_graph;
        std::vector<size_t>                    m_root;      // root nodes ('Union Find' algorithm)
        std::vector<WeightedEdge<Weight>>      m_mst;       // minimum spanning tree (described with edges)

    public:
        KruskalSolver(IWeightedGraphRepresentation<Weight, NodeDescription>& graph) : m_graph{ graph } {}

        void initRootNodes() {
            // initialize root nodes
            m_root.resize(m_graph.countNodes());
            std::generate(std::begin(m_root), std::end(m_root), [n = 0]() mutable->size_t {
                return n++;
            });
        }

        void solve() {

            initRootNodes();

            // retrieve and sort all edges
            std::vector<WeightedEdge<Weight>> edges = m_graph.getAllEdges();

            std::sort(
                std::begin(edges),
                std::end(edges),
                [](const WeightedEdge<Weight>& edge1, const WeightedEdge<Weight>& edge2) -> bool {

                    Weight x1 = getEdgeWeight(edge1);
                    Weight x2 = getEdgeWeight(edge2);

                    return x1 < x2;

                    // return getWeight<EDGE, int>(edge1) < getWeight<EDGE, int>(edge2);
                }
            );

            for (const WeightedEdge<Weight>& edge : edges) {

                size_t source = getSource(edge);
                size_t target = getTarget(edge);

                size_t sourceRepresentative = findSet(source);
                size_t targetRepresentative = findSet(target);

                if (sourceRepresentative != targetRepresentative) {
                    m_mst.push_back(edge); // add to minimum spanning tree
                    unionSet(sourceRepresentative, targetRepresentative);
                }
            }
        }

        size_t findSet(size_t index) {
            // if i is the parent of itself, we've found representative of the set
            if (index == m_root[index]) {
                return index;
            }
            else {
                // if i is not the parent of itself, then i is not
                // the representative of this set, so we recursively
                // call 'findSet' on its parent
                return findSet(m_root[index]);
            }
        }

        void unionSet(size_t u, size_t v) {
            m_root[u] = m_root[v];
        }

        void printMST() {
            std::cout << "Edge :" << " Weight" << std::endl;
            for (const WeightedEdge<Weight>& edge : m_mst) {
                std::cout
                    << getSource(edge) << " - "
                    << getTarget(edge) << " : "
                    << getEdgeWeight<Weight>(edge);
                std::cout << std::endl;
            }
        }
    };

    // -------------------------------------------------------------

    // DFS
    void test_01_A()
    {
        std::cout << "Redesign Graph Theory - DFS" << std::endl;

        // DIRECTED Graph -  NOT WEIGHTED

        UnweightedDirectedGraphAdjListRepresentation<int> graph{ 8 };

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
        graph.addEdge(7, 6);

        std::cout << graph.toString() << std::endl;;

        DFSSolver dfs{ graph };

        constexpr size_t Source = 1;
        constexpr size_t Target = 6;

        if (std::vector<size_t> resultPath; dfs.findPathAny(Source, Target, resultPath))
        {
            std::cout << "Path exists from vertex " << Source << " to vertex " << Target << std::endl;
            std::cout << "The complete path is: ";
            dfs.printPath(resultPath);
        }
        else {
            std::cout << "No path exists between vertices " << Source << " and " << Target;
        }
    }

    void test_01_B()
    {
        std::cout << "Redesign Graph Theory - DFS" << std::endl;

        // UNDIRECTED Graph -  NOT WEIGHTED

        UnweightedUndirectedGraphAdjListRepresentation<int> graph{ 8 };

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

        constexpr size_t Source = 1;
        constexpr size_t Target = 6;

        if (std::vector<size_t> resultPath; dfs.findPathAny(Source, Target, resultPath))
        {
            std::cout << "Path exists from vertex " << Source << " to vertex " << Target << std::endl;
            std::cout << "The complete path is: ";
            dfs.printPath(resultPath);
        }
        else {
            std::cout << "No path exists between vertices " << Source << " and " << Target;
        }
    }

    // DFS - all paths - UNDIRECTED Graph - NOT WEIGHTED
    void test_02()
    {
        std::cout << "Redesign Graph Theory - DFS" << std::endl;

        UnweightedDirectedGraphAdjListRepresentation<int> graph{ 8 };

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

        constexpr size_t Source = 1;
        constexpr size_t Target = 6;

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

    // -------------------------------------------------------------

    // BFS - all paths - UNDIRECTED Graph - NOT WEIGHTED
    void test_03()
    {
        std::cout << "Redesign Graph Theory - BFS" << std::endl;

        UnweightedDirectedGraphAdjListRepresentation<int> graph{ 8 };

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

        BFSSolver bfs{ graph };

        std::vector<std::optional<size_t>> paths = bfs.solve(0);
        std::vector<size_t> solution = bfs.reconstructPath(0, 4, paths);
        bfs.printSolution(solution);
    }

    // -------------------------------------------------------------

    // Dijkstra - all paths - UNDIRECTED Graph - WEIGHTED
    void test_04_a()
    {
        // Beispiel "LMU_Muenchen"

        WeightedDirectedGraphAdjListRepresentation<int, size_t> graph{ 6 };

        graph.addEdge(0, 1, 10);
        graph.addEdge(0, 2, 20);
        graph.addEdge(1, 4, 10);
        graph.addEdge(1, 3, 50);
        graph.addEdge(2, 4, 33);
        graph.addEdge(2, 3, 20);
        graph.addEdge(3, 4, 20);
        graph.addEdge(3, 5, 2);
        graph.addEdge(4, 5, 1);

        // create solver
        DijkstraSolver<int, size_t> dijkstra{ graph };

        dijkstra.computeShortestPaths(0);
        // std::vector<size_t> distances = dijkstra.getDistances();
        dijkstra.printDistances();
    }

    void test_04_b()
    {
        // Beispiel "TU München Europakarte"

        WeightedDirectedGraphAdjListRepresentation<int, size_t> graph{ 10 };

        // Beispiel TUM München Europakarte
        constexpr int a = 0;
        constexpr int b = 1;
        constexpr int c = 2;
        constexpr int d = 3;
        constexpr int e = 4;
        constexpr int f = 5;
        constexpr int g = 6;
        constexpr int h = 7;
        constexpr int i = 8;
        constexpr int j = 9;

        graph.addEdge(i, a, 464);
        graph.addEdge(a, i, 464);
        graph.addEdge(c, f, 1054);
        graph.addEdge(f, c, 1054);
        graph.addEdge(a, f, 343);
        graph.addEdge(f, a, 343);
        graph.addEdge(c, e, 1364);
        graph.addEdge(e, c, 1364);
        graph.addEdge(a, h, 1435);
        graph.addEdge(h, a, 1435);
        graph.addEdge(f, b, 879);
        graph.addEdge(b, f, 879);
        graph.addEdge(f, e, 1106);
        graph.addEdge(e, f, 1106);
        graph.addEdge(h, g, 837);
        graph.addEdge(g, h, 837);
        graph.addEdge(b, g, 954);
        graph.addEdge(g, b, 954);
        graph.addEdge(j, d, 1053);
        graph.addEdge(d, j, 1053);
        graph.addEdge(g, d, 433);
        graph.addEdge(d, g, 433);
        graph.addEdge(b, h, 811);
        graph.addEdge(h, b, 811);
        graph.addEdge(b, j, 524);
        graph.addEdge(j, b, 524);
        graph.addEdge(j, e, 766);
        graph.addEdge(e, j, 766);

        DijkstraSolver<int, size_t> dijkstra{ graph };
        dijkstra.computeShortestPaths(2);
        dijkstra.printDistances();
    }

    // -------------------------------------------------------------

    // Kruskal

    void test_05()
    {
        // https://www.programiz.com/dsa/kruskal-algorithm

        constexpr int NumNodes = 6;

        WeightedEdge<int> we1{ 0, 1, 4 };
        WeightedEdge<int> we2{ 0, 2, 4 };
        WeightedEdge<int> we3{ 1, 2, 2 };
        WeightedEdge<int> we4{ 2, 3, 3 };
        WeightedEdge<int> we5{ 2, 5, 2 };
        WeightedEdge<int> we6{ 2, 4, 4 };
        WeightedEdge<int> we7{ 3, 4, 3 };
        WeightedEdge<int> we8{ 5, 4, 3 };

        WeightedUndirectedGraphAdjListRepresentation<int, int> graph{ NumNodes };

        graph.addEdge(we1);
        graph.addEdge(we2);
        graph.addEdge(we3);
        graph.addEdge(we4);
        graph.addEdge(we5);
        graph.addEdge(we6);
        graph.addEdge(we7);
        graph.addEdge(we8);

        KruskalSolver<int, int> kruskal{ graph };
        kruskal.solve();
        kruskal.printMST();
    }

    // =====================================================================================

    // Flugverbindungen Nordamerika
    // test_10
    // Flug von New Yort nach Urbana
    // Flug von Houston nach Calgary
    // Am wenigsten Umsteigen
    // In diesem Beispiel ist der Graph UNGERICHTET, man kann also immer in beide
    // Richtungen fliegen

    // BFS - all paths - UNDIRECTED Graph - NOT WEIGHTED
    void test_10()
    {
        std::cout << "Flugverbindungen Nordamerika - BFS" << std::endl;
        std::cout << "Flug von New Yort nach Urbana - Am wenigsten Umsteigen" << std::endl;

        UnweightedUndirectedGraphAdjListRepresentation<std::string> graph{ 8 };

        // 0 New York
        // 1 Toronto
        // 2 Chicago
        // 3 Urbana
        // 4 Houston
        // 5 Denver
        // 6 Calgary
        // 7 Los Angeles

        graph.setNodeDescription(0, "New York");
        graph.setNodeDescription(1, "Toronto");
        graph.setNodeDescription(2, "Chicago");
        graph.setNodeDescription(3, "Urbana");
        graph.setNodeDescription(4, "Houston");
        graph.setNodeDescription(5, "Denver");
        graph.setNodeDescription(6, "Calgary");
        graph.setNodeDescription(7, "Los Angeles");

        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(0, 5);
        graph.addEdge(1, 2);
        graph.addEdge(1, 6);
        graph.addEdge(1, 7);
        graph.addEdge(2, 5);
        graph.addEdge(4, 7);
        graph.addEdge(5, 3);
        graph.addEdge(5, 4);
        graph.addEdge(5, 7);

        BFSSolver<std::string> bfs{ graph };

        std::vector<std::optional<size_t>> paths = bfs.solve(7);
        std::vector<size_t> solution = bfs.reconstructPath(7, 0, paths);
        bfs.printSolution(solution);
    }

    // =====================================================================================

    // Flugverbindungen Nordamerika
    // test_11
    // Flug von New Yort nach Urbana
    // Flug von Houston nach Calgary
    // Am wenigsten Umsteigen

    // BFS - all paths - DIRECTED Graph - NOT WEIGHTED
    void test_11()
    {
        size_t source{ 0 };
        size_t target{ 7 };

        std::cout << "Flugverbindungen Nordamerika - BFS" << std::endl;
        std::cout << "Flug von New Yort nach Urbana - Am wenigsten Umsteigen" << std::endl;

        UnweightedDirectedGraphAdjListRepresentation<std::string> graph{ 8 };

        // 0 New York
        // 1 Toronto
        // 2 Chicago
        // 3 Urbana
        // 4 Houston
        // 5 Denver
        // 6 Calgary
        // 7 Los Angeles

        graph.setNodeDescriptions({
            "New York","Toronto","Chicago","Urbana",
            "Houston","Denver","Calgary","Los Angeles" 
        });

        graph.addEdge(0, 1);
        graph.addEdge(0, 2);
        graph.addEdge(0, 5);
        graph.addEdge(1, 2);
        graph.addEdge(1, 6);
        graph.addEdge(1, 7);
        graph.addEdge(2, 5);
        graph.addEdge(4, 7);
        graph.addEdge(5, 3);
        graph.addEdge(5, 4);
        graph.addEdge(5, 7);

        std::cout << graph << std::endl;

        BFSSolver<std::string> bfs{ graph };
        std::vector<std::optional<size_t>> paths = bfs.solve(source);
        std::vector<size_t> solution = bfs.reconstructPath(source, target, paths);
        bfs.printSolution(solution);
    }

    // =====================================================================================

    // Buch von Hans Werner Lang
    // test_12
    // Ungerichteter Graph mit insgesamt 23 Knoten
    // Kürzeste Verbindung
    // Die Knoten sollen als Knotenbeschriftung int haben.

    // BFS - all paths - UNDIRECTED Graph - NOT WEIGHTED
    void test_12()
    {
        std::cout << "Buch von Hans Werner Lang - BFS" << std::endl;
        std::cout << "Ungerichteter Graph mit insgesamt 23 Knoten - Kürzeste Verbindung" << std::endl;

        UnweightedUndirectedGraphAdjListRepresentation<int> graph{ 23 };

        std::cout << graph << std::endl;

        //graph.setNodeDescriptions({
        //1, 2, 3, 4, 5, 6, 7, 8, 9, 10
        //});


        graph.addEdge(0, 5);
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 4);
        graph.addEdge(4, 5);
        graph.addEdge(5, 6);
        graph.addEdge(1, 7);
        graph.addEdge(5, 8);
        graph.addEdge(6, 10);
        graph.addEdge(8, 9);
        graph.addEdge(9, 10);
        graph.addEdge(7, 11);
        graph.addEdge(8, 15);
        graph.addEdge(11, 12);
        graph.addEdge(12, 13);
        graph.addEdge(13, 14);
        graph.addEdge(14, 15);
        graph.addEdge(11, 16);
        graph.addEdge(12, 17);
        graph.addEdge(13, 18);
        graph.addEdge(15, 19);
        graph.addEdge(16, 17);
        graph.addEdge(17, 18);
        graph.addEdge(19, 20);
        graph.addEdge(20, 21);
        graph.addEdge(18, 22);

        BFSSolver<int> bfs{ graph };

        size_t source{ 7 };
        size_t target{ 15 };

        std::vector<std::optional<size_t>> paths = bfs.solve(source);
        std::vector<size_t> solution = bfs.reconstructPath(source, target, paths);
        bfs.printSolution(solution);
    }

    // =====================================================================================

    // testing only graphs
    // a) Undirected, Unweighted, No Node Descriptions
    // b) Undirected, Unweighted, Node Descriptions
    // c) Directed,   Unweighted, No Node Descriptions
    // d) Directed,   Unweighted, Node Descriptions
    // 
    // Same with Weighted Graphs - To be Done

    void test_90_a()
    {
        std::cout << "Undirected, Unweighted, No Node Descriptions" << std::endl;

        UnweightedUndirectedGraphAdjListRepresentation graph{ 4 };

        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 0);

        std::cout << graph << std::endl;
    }

    void test_90_b()
    {
        std::cout << "Undirected, Unweighted, Node Descriptions" << std::endl;

        UnweightedUndirectedGraphAdjListRepresentation<std::string> graph{ 4 };

        graph.setNodeDescriptions({
            std::string{"A"}, std::string{"B"}, std::string{"C"}, std::string{"C"}
        });

        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 0);

        std::cout << graph << std::endl;
    }

    void test_90_c()
    {
        std::cout << "Directed, Unweighted, No Node Descriptions" << std::endl;

        UnweightedDirectedGraphAdjListRepresentation<int> graph{ 4 };

        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 0);

        std::cout << graph << std::endl;
    }

    void test_90_d()
    {
        std::cout << "Directed, Unweighted, Node Descriptions" << std::endl;

        UnweightedDirectedGraphAdjListRepresentation<std::string> graph{ 4 };

        graph.setNodeDescriptions({
            std::string{"A"}, std::string{"B"}, std::string{"C"}, std::string{"C"}
        });

        graph.addEdge(0, 1);
        graph.addEdge(1, 2);
        graph.addEdge(2, 3);
        graph.addEdge(3, 0);

        std::cout << graph << std::endl;
    }


    // =====================================================================================


}

// =====================================================================================


int main()
{
    using namespace Graph_Theory_Redesign;
    //test_01_A();
    //test_01_B();
    //test_02();
    //test_03();
    //test_04_a();
    //test_04_b();
    //test_05();

    // test_10();
    // test_11();
    //test_12();

    test_90_a();
    test_90_b();
    test_90_c();
    test_90_d();

    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================
