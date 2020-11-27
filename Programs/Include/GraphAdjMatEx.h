// =====================================================================================
// GraphAdjMatrixEx.h
// =====================================================================================

template <typename EDGE>
class GraphAdjMatrixEx final : public IGraphEx<EDGE> {

private:
    int  m_numNodes;
    int  m_numEdges;
    bool m_isDirected;
    bool m_isWeighted;
    std::vector<EDGE> m_adj; // adjacency matrix

public:
    // c'tors
    // PeLo: More uniform syntax
    GraphAdjMatrixEx() = delete;

    // PeLo ????  da muss die Anzahl der Knoten übergeben werden .. oder nicht ???

    GraphAdjMatrixEx(bool directed = NotDirected, bool weighted = NotWeighted) : m_numNodes{ -1 }, m_numEdges{ -1 } {
        m_isDirected = directed;
        m_isWeighted = weighted;
        //m_numNodes = -1;  // PeLo ???
        //m_numEdges = -1; 
    }

    // getter
    virtual int countNodes() const override {
        return m_numNodes;
    }

    virtual int countEdges() const override {
        return m_numEdges;
    }

    virtual bool isDirected() const override {
        return m_isDirected;
    }

    virtual bool isWeighted() const override {
        return m_isWeighted;
    }

    // setter
    virtual void setNodesCount(int numNodes) override {
        m_numNodes = numNodes;

        // initialize adjacency matrix
        EDGE empty = make_empty_edge();
        m_adj.resize(m_numNodes * m_numNodes, empty);
    }

    // public interface
    virtual void addEdges(const std::vector<EDGE>& edges) override {
        for (const EDGE& edge : edges) {
            addEdge(edge);
        }
    }

    // PeLo: nochmal testen, wie die beiden zum Aufruf gelangen ?!?!?!?!
    virtual void addEdges(const std::initializer_list<EDGE> list)  override {
        for (const EDGE& edge : list) {
            addEdge(edge);
        }
    }

    virtual std::vector<EDGE> getAllEdges() const override {
        std::vector<EDGE> edges;
        for (const EDGE& edge : m_adj) {
            if (!isEmpty(edge)) {        // PeLo:  Hmmm,wie können da empty Edges reinkommen  ???
                edges.push_back(edge);
            }
        }
        return edges;
    }

    virtual EDGE searchEdge(IndexType source, IndexType target) const override {
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

    virtual std::vector<IndexType> getNeighbouringNodes(IndexType node) const override {
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

    virtual std::vector<EDGE> getNeighbouringEdges(IndexType node) const override {
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

    virtual std::string toString() const override {
        std::ostringstream oss;

        oss << "Graph: " << (m_isDirected ? "directed" : "undirected") << " / ";
        oss << (m_isWeighted ? "weighted" : "not weighted") << "\n";

        if (!isDirected()) {

            std::string separator = " <=> ";

            for (int row = 0; row < m_numNodes; ++row)
            {
                oss << "Node [" << row << "]: ";

            //    bool isFirst = true;

                for (int col = 0; col < m_numNodes; ++col)
                {
                    int index = toIndex(row, col);
                    EDGE edge = m_adj[index];

                    if (! isEmpty(edge)) {
                        assert(getSource(edge) == row);
                        assert(getTarget(edge) == col);

                        oss << row << separator << col;

                        if (isWeighted()) {
                            if constexpr (std::tuple_size<EDGE>::value >= 3) {   // PeLo das kann weg !!!!!!!!!! NEIN - das ist hier ein Problem
                                                                                // ich muss irgendwie Weighted Edge und Unweighted Edge
                                                                                // zur COMPILE TIME unterscheiden können !!!!
                                auto weight = getWeightEx(edge);
                                oss << " {" << weight << "} ";
                            }
                        }

                        oss << "  ||  ";
                        
                        //if (!isFirst) {
                        //    oss << " | ";
                        //}

              //          isFirst = false;
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
        //std::string toStringNodes() const {
        //    std::ostringstream oss;
        //    oss << "Nodes:" << '\n';
        //    std::for_each(std::begin(m_nodes), std::end(m_nodes), [&](const NODE& node) {
        //        int id = getId(node);
        //        auto details = getDetailsEx(node);
        //        oss << "[" << id << "]  " << details << '\n';
        //        }
        //    );
        //    return oss.str();
        //}

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
    EDGE make_empty_edge() {  
        EDGE empty{};
        setSourceNode(empty, -1);
        setTargetNode(empty, -1);
        return empty;
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
