// =====================================================================================
// GraphAdjMatrix.h
// =====================================================================================

template <typename NODE, typename EDGE>
class GraphAdjMatrix : public IGraph<NODE, EDGE> {
private:
    // bool m_isDirected;
    Direction m_direction;
    int  m_numNodes;
    int  m_numEdges;
    std::vector<NODE> m_nodes;  // nodes vector
    std::vector<EDGE> m_adj;    // adjacency matrix

public:
    // c'tors
    // PeLo: More uniform syntax
    GraphAdjMatrix() = delete;
    GraphAdjMatrix(Direction direction) : /* m_isDirected{ isDirected } */  m_direction{ direction } {
        m_numNodes = -1;
        m_numEdges = 0;
    }

    // getter
    int countNodes() const override {
        return m_nodes.size();
    }

    int countEdges() const override {
        return m_numEdges;
    }

    bool isDirected() const override {
        return m_direction == Direction::directed;
    }

    bool isWeighted() const override {
        return std::tuple_size<EDGE>::value == 4;
    }

    // public interface
    void addNodes(const std::vector<NODE>& nodes) override {
        if (m_nodes.size() != 0) {
            throw std::bad_function_call();
        }
        else {
            for (const NODE& node : nodes) {
                addNode(node);
            }
            m_numNodes = m_nodes.size();

            // adjust size of adjacency matrix - add 'empty' node
            if constexpr (std::tuple_size<EDGE>::value == 3) {
                m_adj.resize(m_numNodes * m_numNodes, { -1, -1, {} });
            }
            if constexpr (std::tuple_size<EDGE>::value == 4) {
                m_adj.resize(m_numNodes * m_numNodes, { -1, -1, -1, {} });
            }
        }
    }

    void addNodes(const std::initializer_list<NODE> list) override {
        if (m_nodes.size() != 0) {
            throw std::bad_function_call();
        }
        else {
            for (const NODE& node : list) {
                addNode(node);
            }
            m_numNodes = m_nodes.size();

            // adjust size of adjacency matrix - add 'empty' node
            if constexpr (std::tuple_size<EDGE>::value == 3) {
                m_adj.resize(m_numNodes * m_numNodes, { -1, -1, {} });
            }
            if constexpr (std::tuple_size<EDGE>::value == 4) {
                m_adj.resize(m_numNodes * m_numNodes, { -1, -1, -1, {} });
            }
        }
    }

    NODE getNode(IndexType node) const override {
        return m_nodes[node];
    }

    std::vector<NODE> getAllNodes() const override {
        return m_nodes;
    }

    void addEdges(const std::vector<EDGE>& edges) override {
        for (const EDGE& edge : edges) {
            addEdge(edge);
        }
    }

    void addEdges(const std::initializer_list<EDGE> list)  override {
        for (const EDGE& edge : list) {
            addEdge(edge);
        }
    }

    std::vector<EDGE> getAllEdges() const override {
        std::vector<EDGE> edges;
        for (const EDGE& edge : m_adj) {
            if (!isEmpty(edge)) {
                edges.push_back(edge);
            }
        }
        return edges;
    }

    EDGE searchEdge(IndexType source, IndexType target) const override {
        auto begin = std::begin(m_adj) + m_numNodes * source;
        auto end = std::begin(m_adj) + m_numNodes * (source + 1);

        auto iter = std::find_if(
            begin,
            end,
            [=](const EDGE& entry) {
                IndexType s = getSource(entry);
                IndexType t = getTarget(entry);
                return source == s and target == t;
            }
        );

        if (iter == end) {
            return EDGE{};
        }
        else {
            return *iter;
        }
    }

    std::vector<IndexType> getNeighbouringNodes(IndexType node) const override {
        auto begin = std::begin(m_adj) + m_numNodes * node;
        auto end = std::begin(m_adj) + m_numNodes * (node + 1);

        std::vector<IndexType> neighbours;
        std::for_each(begin, end, [&](const EDGE& edge) {
            if (!isEmpty(edge)) {
                int target = getTarget(edge);
                neighbours.push_back(target);
            }
        });

        return neighbours;
    }

    std::vector<EDGE> getNeighbouringEdges(IndexType node) const override {
        auto begin = std::begin(m_adj) + m_numNodes * node;
        auto end = std::begin(m_adj) + m_numNodes * (node + 1);

        std::vector<EDGE> neighbours;
        std::for_each(begin, end, [&](const EDGE& edge) {
            if (!isEmpty(edge)) {
                neighbours.push_back(edge);
            }
        });

        return neighbours;
    }

    std::string toString() const override {
        std::ostringstream oss;

        // evaluate 'weight' attribute
        std::string is_weighted;
        if constexpr (std::tuple_size<EDGE>::value == 3) {
            is_weighted = "unweighted";
        }
        if constexpr (std::tuple_size<EDGE>::value == 4) {
            is_weighted = "weighted";
        }

        oss << "Graph: " << ((m_direction == Direction::directed) ? "directed" : "undirected") << ", " << is_weighted << "\n";

        if (!isDirected()) {

            std::string separator = " <=> ";

            for (int row = 0; row < m_numNodes; ++row)
            {
                oss << "Node [" << row << "]: ";

                bool isFirst = true;

                for (int col = 0; col < m_numNodes; ++col)
                {
                    int index = toIndex(row, col);
                    EDGE edge = m_adj[index];

                    if (! isEmpty(edge)) {
                        assert(getSource(edge) == row);
                        assert(getTarget(edge) == col);

                        oss << row << separator << col;

                        if (isWeighted()) {
                            if constexpr (std::tuple_size<EDGE>::value == 4) {
                                auto weight = getWeightEx(edge);
                                oss << " {" << weight << "} ";
                            }
                        }
                        
                        if (!isFirst) {
                            oss << " | ";
                        }

                        isFirst = false;
                    }
                }
                oss << '\n';
            }
        }
        else {
            std::string separator = " -> ";

            for (int row = 0; row < m_numNodes; ++row)
            {
                oss << "Node [" << row << "]: ";

                bool isFirst = true;

                for (int col = 0; col < m_numNodes; ++col)
                {
                    int index = toIndex(row, col);
                    const EDGE edge = m_adj[index];

                    if (!isEmpty(edge)) {

                        assert(getSource(edge) == row);
                        assert(getTarget(edge) == col);

                        oss << row << separator << col;

                        if (isWeighted()) {
                            if constexpr (std::tuple_size<EDGE>::value == 4) {
                                auto weight = getWeightEx(edge);
                                oss << " {" << weight << "} ";
                            }
                        }

                        if (!isFirst) {
                            oss << " | ";
                        }

                        isFirst = false;
                    }
                }
                oss << '\n';
            }
        }

        return oss.str();
    }

    public:
        //// additional member template functions
        //template<typename NODE_DETAILS, typename EDGE_DETAILS>
        //std::string toStringNodes() const {
        //    std::ostringstream oss;
        //    std::for_each(std::begin(m_nodes), std::end(m_nodes), [&](const NODE& node) {
        //        int id = getId(node);
        //        NODE_DETAILS details = getDetails<NODE, NODE_DETAILS>(node);
        //        oss << "[" << id << "] " << details << '\n';
        //        });

        //    return oss.str();
        //}

        // additional member template functions
        std::string toStringNodes() const {
            std::ostringstream oss;
            oss << "Nodes:" << '\n';
            std::for_each(std::begin(m_nodes), std::end(m_nodes), [&](const NODE& node) {
                int id = getId(node);
                auto details = getDetailsEx(node);
                oss << "[" << id << "]  " << details << '\n';
                }
            );
            return oss.str();
        }

        template<typename EDGE_DETAILS>
        std::string toStringEdges() const {
            std::ostringstream oss;
            oss << "Edges:" << '\n';
            for (const EDGE& edge : m_adj) {
                if (!isEmpty(edge)) {
                    oss << '[' << edgeToString(edge) << ']';
                    if constexpr (std::tuple_size<EDGE>::value == 3) {
                        // it's a unweighted edge
                        auto details = getDetailsUnweightedEdgeEx(edge);
                        oss << "  " << details << '\n';
                    }
                    else if constexpr (std::tuple_size<EDGE>::value == 4) {
                        // it's a weighted edge
                        auto details = getDetailsWeightedEdgeEx(edge);
                        auto weight = getWeightEx(edge);
                        oss << " [" << weight << "] " << details << '\n';
                    }
                }
            }
            return oss.str();
        }

private:
    void addNode(const NODE& node) {
        m_nodes.push_back(node);
    }

    inline int toIndex(IndexType source, IndexType target) const {
        return source * m_numNodes + target;
    }

    void addEdge(const EDGE& edge) {
        IndexType source = getSource<EDGE>(edge);
        IndexType target = getTarget<EDGE>(edge);

        if (! isDirected()) {
            // add two entries
            int index = toIndex(source, target);
            m_adj[index] = edge;

            EDGE copy = edge;
            swapSourceTarget(copy);
            index = toIndex(target, source);
            m_adj[index] = copy;

            ++m_numEdges;
        }
        else {
            int index = toIndex(source, target);
            m_adj[index] = edge;
            ++m_numEdges;
        }
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
