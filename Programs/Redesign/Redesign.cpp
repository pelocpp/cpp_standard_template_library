// =====================================================================================
// Graph Theory Redesign
// =====================================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <algorithm>
#include <optional>
#include <queue>

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

// =====================================================================================

namespace Graph_Theory_Redesign
{
    // -------------------------------------------------------------

    using Edge = std::pair<size_t, size_t>;

    template<typename Weight>
    using WeightedEdge = std::tuple<size_t, size_t, Weight>;

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


    // TODO: ACHTUNG: habe da jetzt man nen Namenskonflikt mit Ex gelöst
    // Der Bezeichner getWeight kommt auch als Methode in den Klassen vor !?!?!?!
    // das ist zu klären
    template<typename Weight>
    auto getWeightEx(const WeightedEdge<Weight>& edge) {
        return std::get<2>(edge);
    }

    // -------------------------------------------------------------

    class IGraphRepresentation
    {
    public:
        virtual size_t countNodes() const = 0;  // Hnmmm, ist auch doppelt ?!?!
        virtual size_t countEdges() const = 0;  // Hnmmm, ist auch doppelt ?!?!

        //virtual void addEdge(std::pair<size_t, size_t>) = 0;
        //virtual void addEdges(const std::initializer_list<std::pair<size_t, size_t>>  list ) = 0;

        // Hmmmm, das ist zu klären, ob das hier in Ordnung ist !?!?!?!?!?!
        virtual std::vector<size_t> getNeighbouringNodes(size_t) = 0;

        //  virtual ~IGraphRepresentation() = 0;
    };

    // -------------------------------------------------------------

    class IUnweightedGraphRepresentation : public IGraphRepresentation
    {
    public:
        virtual void addEdge(size_t, size_t) = 0;
        virtual void addEdge(Edge) = 0;
        virtual std::vector<Edge> getAllEdges() = 0;
    };

    template <typename Weight>
    class IWeightedGraphRepresentation : public IGraphRepresentation
    {
    public:
        virtual void addEdge(size_t, size_t, Weight) = 0;
        virtual void addEdge(WeightedEdge<Weight>) = 0;
        virtual Weight getWeight(size_t n, size_t m) = 0;
        virtual std::vector<WeightedEdge<Weight>> getAllEdges() = 0;
    };

    // -------------------------------------------------------------

    class UnweightedDirectedGraphAdjListRepresentation : public IUnweightedGraphRepresentation
    {
    protected:
        std::vector<std::vector<size_t>> m_adjacencyList;

    public:
        UnweightedDirectedGraphAdjListRepresentation(size_t nodes) {
            m_adjacencyList.resize(nodes);
        }

        virtual size_t countNodes() const final { return m_adjacencyList.size(); }

        virtual size_t countEdges() const final { return 0; } // TO BE DONE

        virtual void addEdge(size_t n, size_t m) override {
            m_adjacencyList[n].push_back(m);
        }

        virtual void addEdge(Edge edge) override {
            addEdge(getSource(edge), getTarget(edge));
        }

        virtual std::vector<size_t> getNeighbouringNodes(size_t node) override {
            return m_adjacencyList[node];
        }

        virtual std::vector<Edge> getAllEdges() override {

            std::vector<Edge> edges;
            for (size_t row = 0; const auto & vertices : m_adjacencyList) {
                for (size_t column : vertices) {
                    edges.push_back({ row, column });
                }

                //if (!isEmpty(edge)) {      
                //    edges.push_back(edge);
                //}
            }

            return edges;
        }
    };

    class UnweightedUndirectedGraphAdjListRepresentation : public UnweightedDirectedGraphAdjListRepresentation
    {
    public:
        UnweightedUndirectedGraphAdjListRepresentation(size_t nodes) : UnweightedDirectedGraphAdjListRepresentation{ nodes } { }

        virtual void addEdge(size_t n, size_t m) override {
            m_adjacencyList[n].push_back(m);
            m_adjacencyList[m].push_back(n);
        }
    };

    // -------------------------------------------------------------

    template <typename Weight>
    class WeightedDirectedGraphAdjListRepresentation : public IWeightedGraphRepresentation<Weight>
    {
    protected:
        std::vector<std::vector<std::optional<Weight>>> m_adjacencyList;

    public:
        WeightedDirectedGraphAdjListRepresentation(size_t nodes)
            : m_adjacencyList{ std::vector<std::vector<std::optional<Weight>>>(nodes, std::vector<std::optional<Weight>>(nodes, std::nullopt)) }
        {}

        virtual size_t countNodes() const final { return m_adjacencyList.size(); }
        virtual size_t countEdges() const final { return 0; } // TO BE DONE

        virtual void addEdge(size_t n, size_t m, Weight weight) override {
            m_adjacencyList[n][m] = weight;
        }

        virtual void addEdge(WeightedEdge<Weight> edge) override {
            addEdge(getSource(edge), getTarget(edge), getWeightEx<Weight>(edge));
        }

        virtual Weight getWeight(size_t n, size_t m) override {
            return m_adjacencyList[n][m].value();
        }

        virtual std::vector<size_t>  getNeighbouringNodes(size_t node) override {

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

        virtual std::vector<WeightedEdge<Weight>> getAllEdges() override {

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
    };

    template <typename Weight>
    class WeightedUndirectedGraphAdjListRepresentation : public WeightedDirectedGraphAdjListRepresentation<Weight>
    {
    public:
        // Siehe hier
        // https://www.modernescpp.com/index.php/surprise-included-inheritance-and-member-functions-of-class-templates

        // Das Problem taucht gleich ZWEIMAL auf !!!!
        // ein erstes Mal bzgl. der Zugriffs auf m_adjacencyList
        // ein zweites Mal beim Aufruf von addEdge im Anwendungsbeispiel

        using WeightedDirectedGraphAdjListRepresentation<Weight>::addEdge;
        using WeightedDirectedGraphAdjListRepresentation<Weight>::m_adjacencyList;

        WeightedUndirectedGraphAdjListRepresentation(size_t nodes) : WeightedDirectedGraphAdjListRepresentation<Weight>{ nodes } { }

        virtual void addEdge(size_t n, size_t m, Weight weight) override {

            //WeightedDirectedGraphAdjListRepresentation<Weight>::addEdge(n, m, weight);
            //WeightedDirectedGraphAdjListRepresentation<Weight>::addEdge(m, n, weight);

            // TODO: Warum lässt sich das nicht übersetzen ?!?!?! ES GEHT DOCH !!!!!! Siehe 10 Zeilen weiter obem
            m_adjacencyList[n][m] = weight;
            m_adjacencyList[m][n] = weight;
        }
    };

    // -------------------------------------------------------------

    class IGraph
    {
    public:
        virtual size_t countNodes() const = 0;
        virtual size_t countEdges() const = 0;

        //  virtual void set(IGraphRepresentation& r) = 0;
        virtual std::vector<size_t>  getNeighbouringNodes(size_t) = 0;  // TODO: Hmmm, ist diese Methode an dieser Stelle richtig ?!?!?!? WIEDERHOLUNG
    };

    // soll eine abstrakte Basisklasse sein .................
    class UnweightedGraph : public IGraph
    {
    protected:
        IUnweightedGraphRepresentation& m_r;

    public:
        virtual size_t countNodes() const override { return m_r.countNodes(); }
        virtual size_t countEdges() const override { return 0; }

        virtual std::vector<size_t>  getNeighbouringNodes(size_t node) {
            return m_r.getNeighbouringNodes(node);
        }

        // Das ist auch eine Wiederholung !?!?!?!?!?!
        virtual std::vector<Edge> getAllEdges() {
            return m_r.getAllEdges();
        }

        UnweightedGraph(IUnweightedGraphRepresentation& r) : m_r{ r } {}
    };

    // soll eine abstrakte Basisklasse sein .................
    template <typename Weight>
    class WeightedGraph : public IGraph
    {
    protected:
        IWeightedGraphRepresentation<Weight>& m_r;

    public:
        // Das ist auch eine Wiederholung !?!?!?!?!?!
        virtual size_t countNodes() const override { return m_r.countNodes(); }
        virtual size_t countEdges() const override { return 0; }

        // Das ist auch eine Wiederholung !?!?!?!?!?!
        std::vector<size_t> getNeighbouringNodes(size_t node) {
            return m_r.getNeighbouringNodes(node);
        }

        // Das ist auch eine Wiederholung !?!?!?!?!?!
        virtual std::vector<WeightedEdge<Weight>> getAllEdges() {
            return m_r.getAllEdges();
        }

        // Das ist auch eine Wiederholung !?!?!?!?!?!
        Weight getWeight(size_t n, size_t m) { return m_r.getWeight(n, m); }

        WeightedGraph(IWeightedGraphRepresentation<Weight>& r) : m_r{ r } {}
    };

    // -------------------------------------------------------------

   /*
      template <typename TRepresentation>
      class DirectedGraph {
          TRepresentation m_graph;
          ....
   */

    class UnweightedDirectedGraph : public UnweightedGraph
    {
    public:
        UnweightedDirectedGraph(IUnweightedGraphRepresentation& r) : UnweightedGraph{ r } {}
    };

    class UnweightedUndirectedGraph : public UnweightedGraph
    {
    public:
        UnweightedUndirectedGraph(IUnweightedGraphRepresentation& r) : UnweightedGraph{ r } {}
    };

    // -------------------------------------------------------------

    template <typename TWEIGHT>
    class WeightedDirectedGraph : public WeightedGraph<TWEIGHT>
    {
    public:
        WeightedDirectedGraph(IWeightedGraphRepresentation<TWEIGHT>& r) : WeightedGraph<TWEIGHT>{ r } {}
    };

    template <typename TWEIGHT>
    class WeightedUndirectedGraph : public WeightedGraph<TWEIGHT>
    {
    public:
        WeightedUndirectedGraph(IWeightedGraphRepresentation<TWEIGHT>& r) : WeightedGraph<TWEIGHT>{ r } {}
    };

    // -------------------------------------------------------------

    class DFSSolver
    {
    private:
        UnweightedGraph& m_graph;    // ist für gerichtete oder ungerichtete Graphen ????
        std::vector<bool> m_visited;
        std::deque<std::vector<size_t>> m_paths;

    public:
        // DFSSolver(UnweightedDirectedGraph& r) : m_graph{ r } {}
        DFSSolver(UnweightedGraph& r) : m_graph{ r } {}

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

    class BFSSolver
    {
    private:
        UnweightedGraph& m_graph;   // TODO: zu klären: Ist dieser Algo für gerichtete oder ungerichtete Graphen ????

        std::deque<size_t> m_queue;
        std::vector<bool> m_visited;

    public:
        BFSSolver(UnweightedGraph& r) : m_graph{ r } {}

        std::vector<std::optional<size_t>> solve(size_t start) {

            // setup 'm_visited' vector
            m_visited.resize(m_graph.countNodes());
            std::fill(std::begin(m_visited), std::end(m_visited), false);
            m_visited.at(start) = true;

            // setup 'previous' vector
            std::vector<std::optional<size_t>> previous;
            previous.resize(m_graph.countNodes());
            std::fill(std::begin(previous), std::end(previous), std::nullopt);

            m_queue.push_back(start);
            while (!m_queue.empty()) {

                // dequeue a vertex from queue
                size_t node = m_queue.front();
                m_queue.pop_front();

                // get all adjacent vertices of the dequeued vertex
                std::vector<size_t> neighbours = m_graph.getNeighbouringNodes(node);
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

            // reconstruct path going backwards from 'target'
            std::vector<size_t> path;

            for (size_t pos = target; pos != -1; pos = prev.at(pos).has_value() ? prev.at(pos).value() : -1) {
                path.push_back(pos);
            }

            std::reverse(std::begin(path), std::end(path));

            // if 'source' and 'target' are connected, return the path
            if (path.at(0) == source) {
                return path;
            }
            else {
                return {};
            }
        }

        void printSolution(std::vector<size_t> path) {
            if (path.size() == 0) {
                std::cout << "No Solution found !" << std::endl;
                return;
            }

            // std__prev !!!!!!!!!!!!!!!!!!
            std::for_each(std::begin(path), std::end(path) - 1, [](size_t vertex) {
                std::cout << "[" << vertex << "] => ";
                }
            );

            // print last element without trailing comma :-)
            size_t vertex = path.at(path.size() - 1);
            std::cout << "[" << vertex << "].";
        }

    };

    // -------------------------------------------------------------

    // Dijkstra

    template<typename W>
    using Track = std::pair<size_t, W>;

    constexpr size_t MaxSize = static_cast<size_t>(-1);

    template <typename Weight>
    class DijkstraSolver {
    private:
        WeightedDirectedGraph<Weight>& m_graph;
        std::vector<size_t> m_distances;
        size_t m_start; // start vertex

    public:
        DijkstraSolver(WeightedDirectedGraph<Weight>& r) : m_graph{ r }, m_start{} {}

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
                Track<size_t> track = pq.top();
                size_t vertex = track.first;
                pq.pop();

                // get all adjacent vertices of the dequeued vertex
                std::vector<size_t> neighbours = m_graph.getNeighbouringNodes(vertex);

                // TODO - Pelo - entscheiden: Da geht / ginge auch getAllEdges !?!?! in der Weighted Variante !!!! - für die neighbours!!!!

                for (size_t target : neighbours) {

                    // size_t target = getTarget<EDGE>(edge);
                    //    IndexType weight = getWeight<EDGE, int>(edge);

                    // auto weight = getWeight<EDGE>(edge);
                    Weight weight = m_graph.getWeight(vertex, target);

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

    template <typename Weight>
    class KruskalSolver
    {
    private:
        WeightedUndirectedGraph<Weight>& m_graph;
        std::vector<size_t>               m_root;  // root nodes ('Union Find' algorithm)
        std::vector<WeightedEdge<Weight>> m_mst;        // minimum spanning tree (described with edges)

    public:
        KruskalSolver(WeightedUndirectedGraph<Weight>& r) : m_graph{ r } {}

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

                    Weight x1 = getWeightEx(edge1);
                    Weight x2 = getWeightEx(edge2);

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
                    << getWeightEx<Weight>(edge);
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

        UnweightedDirectedGraphAdjListRepresentation data{ 8 };

        data.addEdge(0, 3);
        data.addEdge(1, 0);
        data.addEdge(1, 2);
        data.addEdge(1, 4);
        data.addEdge(2, 7);
        data.addEdge(3, 4);
        data.addEdge(3, 5);
        data.addEdge(4, 3);
        data.addEdge(4, 6);
        data.addEdge(5, 6);
        data.addEdge(6, 7);

        // UnweightedDirectedGraph graph{ data };
        UnweightedGraph graph{ data };  // Geht auch !!!

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

        UnweightedUndirectedGraphAdjListRepresentation data{ 8 };

        data.addEdge(0, 3);
        data.addEdge(1, 0);
        data.addEdge(1, 2);
        data.addEdge(1, 4);
        data.addEdge(2, 7);
        data.addEdge(3, 4);
        data.addEdge(3, 5);
        data.addEdge(4, 3);
        data.addEdge(4, 6);
        data.addEdge(5, 6);
        data.addEdge(6, 7);

        //  UnweightedUndirectedGraph graph{ data };
        UnweightedGraph graph{ data };  // Geht auch !!!

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

        UnweightedDirectedGraphAdjListRepresentation data{ 8 };

        data.addEdge(0, 3);
        data.addEdge(1, 0);
        data.addEdge(1, 2);
        data.addEdge(1, 4);
        data.addEdge(2, 7);
        data.addEdge(3, 4);
        data.addEdge(3, 5);
        data.addEdge(4, 3);
        data.addEdge(4, 6);
        data.addEdge(5, 6);
        data.addEdge(6, 7);

        UnweightedDirectedGraph graph{ data };

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

        UnweightedDirectedGraphAdjListRepresentation data{ 8 };

        data.addEdge(0, 3);
        data.addEdge(1, 0);
        data.addEdge(1, 2);
        data.addEdge(1, 4);
        data.addEdge(2, 7);
        data.addEdge(3, 4);
        data.addEdge(3, 5);
        data.addEdge(4, 3);
        data.addEdge(4, 6);
        data.addEdge(5, 6);
        data.addEdge(6, 7);

        UnweightedDirectedGraph graph{ data };

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

        WeightedDirectedGraphAdjListRepresentation<size_t> data{ 6 };

        data.addEdge(0, 1, 10);
        data.addEdge(0, 2, 20);
        data.addEdge(1, 4, 10);
        data.addEdge(1, 3, 50);
        data.addEdge(2, 4, 33);
        data.addEdge(2, 3, 20);
        data.addEdge(3, 4, 20);
        data.addEdge(3, 5, 2);
        data.addEdge(4, 5, 1);

        WeightedDirectedGraph<size_t> graph{ data };

        // create solver
        DijkstraSolver<size_t> dijkstra{ graph };

        dijkstra.computeShortestPaths(0);
        // std::vector<size_t> distances = dijkstra.getDistances();
        dijkstra.printDistances();
    }

    void test_04_b()
    {
        // Beispiel "TU München Europakarte"

        WeightedDirectedGraphAdjListRepresentation<size_t> data{ 10 };

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

        data.addEdge(i, a, 464);
        data.addEdge(a, i, 464);
        data.addEdge(c, f, 1054);
        data.addEdge(f, c, 1054);
        data.addEdge(a, f, 343);
        data.addEdge(f, a, 343);
        data.addEdge(c, e, 1364);
        data.addEdge(e, c, 1364);
        data.addEdge(a, h, 1435);
        data.addEdge(h, a, 1435);
        data.addEdge(f, b, 879);
        data.addEdge(b, f, 879);
        data.addEdge(f, e, 1106);
        data.addEdge(e, f, 1106);
        data.addEdge(h, g, 837);
        data.addEdge(g, h, 837);
        data.addEdge(b, g, 954);
        data.addEdge(g, b, 954);
        data.addEdge(j, d, 1053);
        data.addEdge(d, j, 1053);
        data.addEdge(g, d, 433);
        data.addEdge(d, g, 433);
        data.addEdge(b, h, 811);
        data.addEdge(h, b, 811);
        data.addEdge(b, j, 524);
        data.addEdge(j, b, 524);
        data.addEdge(j, e, 766);
        data.addEdge(e, j, 766);

        WeightedDirectedGraph<size_t> graph{ data };
        DijkstraSolver<size_t> dijkstra{ graph };
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

        WeightedUndirectedGraphAdjListRepresentation<int> data{ NumNodes };

        data.addEdge(we1);
        data.addEdge(we2);
        data.addEdge(we3);
        data.addEdge(we4);
        data.addEdge(we5);
        data.addEdge(we6);
        data.addEdge(we7);
        data.addEdge(we8);

        WeightedUndirectedGraph<int> graph{ data };
        KruskalSolver<int> kruskal{ graph };
        kruskal.solve();
        kruskal.printMST();
    }

}

int main()
{
    using namespace Graph_Theory_Redesign;
    //test_01_A();
    //test_01_B();
    //test_02();
    //test_03();
    //test_04_a();
    //test_04_b();
    test_05();

    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================
