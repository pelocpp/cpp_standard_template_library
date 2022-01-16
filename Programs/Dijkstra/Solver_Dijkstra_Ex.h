//// =====================================================================================
//// Solver_Dijkstra
//// =====================================================================================
//
//namespace Solver_Dijkstra_Ex {
//
//    template<typename W>
//    using Track = std::pair<IndexType, W>;
//
//    template <typename EDGE>
//    class DijkstraSolverEx {
//    private:
//        const IGraphEx<EDGE>* m_graph;
//        std::vector<IndexType> m_distances;
//        IndexType m_start; // start vertex
//
//    public:
//        // c'tor
//        DijkstraSolverEx() : m_start(), m_graph(nullptr) {}
//
//        // public interface
//        void setGraph(const IGraphEx<EDGE>*);
//        bool computeShortestPaths(IndexType startVertex);
//        std::vector<IndexType> getDistances();
//
//        // note: template function on a template class :-)
//        // template<typename NODE_DETAILS>
//        // void printDistances();
//    };
//
//    template <typename EDGE>
//    void DijkstraSolverEx<EDGE>::setGraph(const IGraphEx<EDGE>* graph) {
//        m_graph = graph;
//    }
//
//    template <typename EDGE>
//    bool DijkstraSolverEx<EDGE>::computeShortestPaths(IndexType startVertex) {
//
//        m_start = startVertex;
//        m_distances.resize(m_graph->countNodes());
//
//        // initialize all possible distances as infinite (-1)
//        std::generate(std::begin(m_distances), std::end(m_distances), [] {
//            return -1;
//            });
//
//        // need a lambda to compare Track elements
//        auto compareTracks = [](const Track<int>& lhs, const Track<int>& rhs)  {
//            const auto& [idLeft, weightLeft] = lhs;
//            const auto& [idRight, weightRight] = rhs;
//            return weightLeft > weightRight;
//        };
//
//        // need a priority queue
//        // note: the third template parameter should be the *type* of the comparison function;
//        // the function itself is then passed as a parameter in the constructor of priority_queue!
//        std::priority_queue <
//            Track<int>, std::vector<Track<int>>, decltype(compareTracks) > pq(compareTracks);
//
//        // add source to priority queue, distance is 0
//        Track<int> startTrack{ m_start , 0 };
//        pq.push(startTrack);
//
//        m_distances[m_start] = 0;
//
//        // while priority queue isn't empty...
//        while (!pq.empty()) {
//
//            // get minimum distance vertex from priority queue - we call it 'vertex'
//            using TWEIGHT = int;
//            Track<TWEIGHT> track = pq.top();
//            int vertex = track.first;
//            pq.pop();
//
//            // get all adjacent vertices of the dequeued vertex
//            std::vector<EDGE> neighbours = m_graph->getNeighbouringEdges(vertex);
//            for (const EDGE& edge : neighbours) {
//
//                IndexType target = getTarget<EDGE>(edge);
//            //    IndexType weight = getWeight<EDGE, int>(edge);
//                auto weight = getWeight<EDGE>(edge);
//
//                // if the distance to 'target' is shorter by going through 'vertex' ...
//                if (m_distances[target] == -1 || m_distances[target] > m_distances[vertex] + weight) {
//
//                    // update the distance of 'target'
//                    m_distances[target] = m_distances[vertex] + weight;
//
//                    // insert 'target' into the priority queue
//                    Track<int> track{ target , m_distances[target]};
//                    pq.push(track);
//                }
//            }
//        }
//
//        return true;
//    }
//
//    template <typename EDGE>
//    std::vector<IndexType> DijkstraSolverEx<EDGE>::getDistances() {
//        return m_distances;
//    }
//
//    //template<typename EDGE>
//    //template<typename NODE_DETAILS>
//    //void DijkstraSolverEx<EDGE>::printDistances() {
//
//    //    std::cout << "\nPrinting the shortest paths for node " << m_start << ".\n";
//
//        //std::vector<NODE> nodes = m_graph->getAllNodes();
//        //NODE startNode = nodes[m_start];
//        //NODE_DETAILS startLocation = getDetails<NODE_DETAILS>(startNode);
//
//        //int i = 0;
//        //for (NODE node : nodes) {
//        //    NODE_DETAILS targetLocation = getDetails<NODE_DETAILS>(node);
//        //    std::cout
//        //        << "Distance from " << startLocation
//        //        << " to " << targetLocation << " is: "
//        //        << m_distances[i] << std::endl;
//        //    i++;
//        //}
//   // }
//}
//
//// =====================================================================================
//// End-of-File
//// =====================================================================================
