// =====================================================================================
// GraphAdjList.h
// =====================================================================================

template <typename NODE, typename EDGE>
class GraphAdjList : public IGraph<NODE, EDGE> {
private:
    bool m_isDirected;
    std::vector<NODE> m_nodes;
    std::vector<std::vector<EDGE>> m_adjacencyList;

public:
    // c'tors
    GraphAdjList() = delete;
    GraphAdjList(bool isDirected) : m_isDirected(isDirected) {}

    // getter
    int countNodes() const override {
        return m_nodes.size();
    }

    int countEdges() const override {
        int count = 0;
        std::for_each(std::begin(m_adjacencyList), std::end(m_adjacencyList), [&count](std::vector<EDGE> row) {
            count += row.size();
            }
        );
        return count;
    }

    bool isDirected() const override {
        return m_isDirected;
    }

    bool isWeighted() const override {
        return std::tuple_size<EDGE>::value == 4;
    }

    // public interface
    void addNodes(const std::vector<NODE>& nodes) override {
        if (m_nodes.size() != 0 or m_adjacencyList.size() != 0) {
            throw std::bad_function_call();
        }
        else {
            m_adjacencyList.resize(nodes.size());
            for (const NODE& node : nodes) {
                addNode(node);
            }
        }
    }

    void addNodes(const std::initializer_list<NODE> list) override {
        if (m_nodes.size() != 0 or m_adjacencyList.size() != 0) {
            throw std::bad_function_call();
        }
        else {
            m_adjacencyList.resize(list.size());
            for (const NODE& node : list) {
                addNode(node);
            }
        }
    }

    std::vector<NODE> getAllNodes() const override {
        return m_nodes;
    }

    void addEdges(const std::vector<EDGE>& edges) override {
        for (const EDGE& edge : edges) {
            addEdge(edge);
        }
    }

    void addEdges(const std::initializer_list<EDGE> list) override {
        for (const EDGE& edge : list) {
            addEdge(edge);
        }
    }

    std::vector<EDGE> getAllEdges() const override {
        std::vector<EDGE> edges;
        for (std::vector<EDGE> row : m_adjacencyList) {
           std::copy(row.begin(), row.end(), std::back_inserter(edges));
        }
        return edges;
    }

    EDGE searchEdge(IndexType source, IndexType target) const override {

        auto iter = std::find_if(
            std::begin(m_adjacencyList[source]),
            std::end(m_adjacencyList[source]),
            [=](const EDGE& entry) {
                IndexType s = getSource(entry);
                IndexType t = getTarget(entry);
                return source == s and target == t;
            }
        );

        if (iter == std::end(m_adjacencyList[source])) {
            return EDGE{};
        }
        else {
            return *iter;
        }
    }

    std::string toString() const override {
        std::ostringstream oss;

        bool isFirstEdge = true;
        int row = 0;
        std::string separator = isWeighted() ? " -> " : " <=> ";

        std::for_each(std::begin(m_adjacencyList), std::end(m_adjacencyList), [&](const std::vector<EDGE>& list) {
            oss << "[" << row << "] ";
            if (list.size() > 0) {
                unsigned count = 0;
                std::for_each(std::begin(list), std::end(list), [&](const EDGE& edge) mutable {

                    IndexType source = getSource(edge);
                    IndexType target = getTarget(edge);
                    oss << source << separator << target;

                    if (isWeighted()) {
                        if constexpr (std::tuple_size<EDGE>::value == 4) {
                            int weight = getWeight<EDGE, int>(edge);
                            oss << " [" << weight << "]";
                        }
                    }

                    if (count < list.size() - 1) {
                        oss << " | ";
                    }

                    ++count;
                    }
                );
            }
            oss << '\n';
            ++row;
            }
        );

        return oss.str();
    }

    std::vector<IndexType> getNeighbouringNodes(IndexType node) const override {

        std::vector<IndexType> neighbours;
        for (const EDGE& edge : m_adjacencyList[node]) {

            IndexType target = getTarget(edge);
            neighbours.push_back(target);
        }

        return neighbours;
    }

    std::vector<EDGE> getNeighbouringEdges(IndexType node) const override {
        // need a copy (using copy c'tor)
        std::vector<EDGE> edges = m_adjacencyList[node];
        return edges;
    }

public:
    // additional member template functions
    template<typename NODE_DETAILS, typename EDGE_DETAILS>
    std::string toStringNodes() const {
        std::ostringstream oss;
        std::for_each(std::begin(m_nodes), std::end(m_nodes), [&](const NODE& node) {
            int id = getId(node);
            NODE_DETAILS details = getDetails<NODE, NODE_DETAILS>(node);
            oss << "[" << id << "] " << details << '\n';
            });

        return oss.str();
    }

    template<typename NODE_DETAILS, typename EDGE_DETAILS>
    std::string toStringEdges() const {
        std::ostringstream oss;
        std::for_each(std::begin(m_adjacencyList), std::end(m_adjacencyList), [&](const std::vector<EDGE>& list) {
            std::for_each(std::begin(list), std::end(list), [&](const EDGE& edge) {
                EDGE_DETAILS details{};
                if constexpr (std::tuple_size<EDGE>::value == 3) {
                    // it's a unweighted edge
                    details = getDetailsUnweightedEdge<EDGE, EDGE_DETAILS>(edge);
                }
                if constexpr (std::tuple_size<EDGE>::value == 4) {
                    // it's a weighted edge
                    details = getDetailsWeightedEdge<EDGE, EDGE_DETAILS>(edge);
                }

                oss << edgeToString(edge) << " " << details << '\n';
            });
        });
        return oss.str();
    }

    template<typename NODE_DETAILS, typename EDGE_DETAILS>
    bool readTSPFile(std::string filename) {

        std::string fullname = std::filesystem::current_path().u8string() + "\\TSP\\" + filename;
        std::ifstream infile;
        infile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            infile.open(fullname);
        }
        catch (std::ifstream::failure e) {
            std::cerr << "File " << filename << " not found!";
            return false;
        }
        std::cout << "Processing file " << filename << ":" << std::endl;

        int dimension = 0;
        parseTSPHeader<NODE_DETAILS, EDGE_DETAILS>(infile, dimension);
        parseTSPData<NODE_DETAILS, EDGE_DETAILS>(infile, dimension);
        return true;
    }

private:
    // private helper methods
    template<typename NODE_DETAILS, typename EDGE_DETAILS>
    void parseTSPHeader(std::ifstream& infile, int& dimension) {

        enum class Keywords {
            Name,
            Type,
            Comment,
            Dimension,
            EdgeWeightType,
            EdgeWeightFormat,
            DisplayDataType,
            EdgeWeightSection
        };

        std::map<std::string, Keywords> keywords{
            { "NAME", Keywords::Name },
            { "TYPE", Keywords::Type },
            { "COMMENT", Keywords::Comment },
            { "DIMENSION", Keywords::Dimension },
            { "EDGE_WEIGHT_TYPE", Keywords::EdgeWeightType},
            { "EDGE_WEIGHT_FORMAT", Keywords::EdgeWeightFormat },
            { "DISPLAY_DATA_TYPE", Keywords::DisplayDataType },
            { "EDGE_WEIGHT_SECTION", Keywords::EdgeWeightSection }
        };

        bool sectionEdgeWeightFound = false;

        try {

            while (!sectionEdgeWeightFound) {
                std::string line;
                std::getline(infile, line);

                // read keyword and skip colon ':'
                std::istringstream iss = std::istringstream{ line };
                std::string token;
                std::string colon;
                std::string data;

                iss >> token;
                iss >> colon;

                // if it's a comment, get the rest of the line
                if (token == "COMMENT") {
                    getline(iss, data);
                }
                else {
                    iss >> data;
                }

                Keywords keyword = keywords[token];

                switch (keyword) {
                case Keywords::Name:
                    std::cout << "Name: " << data << std::endl;
                    break;
                case Keywords::Type:
                    std::cout << "Type: " << data << std::endl;
                    break;
                case Keywords::Comment:
                    std::cout << "Comment: " << data << std::endl;
                    break;
                case Keywords::Dimension:
                    std::cout << "Dimension: " << data << std::endl;
                    dimension = std::stoi(data);
                    break;
                case Keywords::EdgeWeightType:
                    std::cout << "EdgeWeightType: " << data << std::endl;
                    break;
                case Keywords::EdgeWeightFormat:
                    std::cout << "EdgeWeightFormat: " << data << std::endl;
                    break;
                case Keywords::DisplayDataType:
                    std::cout << "DisplayDataType: " << data << std::endl;
                    break;
                case Keywords::EdgeWeightSection:
                    std::cout << "EdgeWeightSection: " << data << std::endl;
                    sectionEdgeWeightFound = true;  // terminate parsing of TSP header section
                    break;
                default:
                    std::cerr << "Internal Error parsing tokens! " << std::endl;
                }
            }
        }
        catch (std::ifstream::failure e) {
            std::cerr << "Error reading file!";
            infile.close();
            return;
        }
    }

    // private helper methods
    template<typename NODE_DETAILS, typename EDGE_DETAILS>
    void parseTSPData(std::ifstream& infile, int dimension) {

        // create rsp. resize node vector and adjacency vector to appropriate size
        m_nodes.resize(dimension);

        // fill vector with node objects
        std::generate(std::begin(m_nodes), std::end(m_nodes), [index = 0]() mutable {
            NODE node{ static_cast<IndexType>(index), {} };
            index++;
            return node;
        });

        m_adjacencyList.resize(dimension);

        try {

            int row = 1;
            int col = 0;

            while (true) {
                std::string line;
                std::getline(infile, line);

                if (line == "DISPLAY_DATA_SECTION") {
                    // end of display data section reached
                    break;
                }
                //  std::cout << line << std::endl;

                std::istringstream iss = std::istringstream{ line };
                while (true) {
                    std::string value;

                    iss >> value;
                    if (value.empty()) {
                        break;
                    }

                    // convert string to integer (weight)
                    int weight = std::stoi(value);

                    // add edge to graph
                    col++;

                    if (row != col) {
                        // std::cout << "Value " << weight << " [" << row << "," << col << "]" << std::endl;
                        EDGE edge1 = createWeightedEdge<int, EDGE_DETAILS>(row - 1, col - 1, weight);
                        EDGE edge2 = createWeightedEdge<int, EDGE_DETAILS>(col - 1, row - 1, weight);
                        addEdge(edge1);
                        addEdge(edge2);
                    }

                    // switch to next diagonal row, if necessary
                    if (col == row) {
                        row++;
                        col = 0;
                    }
                }
            }

            infile.close();
        }
        catch (std::ifstream::failure e) {
            std::cerr << "Error reading file!";
            infile.close();
            return;
        }
    }

    void addNode(const NODE& node) {
        m_nodes.push_back(node);
    }

    void addEdge(const EDGE& edge) {
        IndexType nodeNum = getSource<EDGE>(edge);
        m_adjacencyList[nodeNum].push_back(edge);
    }
};

// =====================================================================================
// End-of-File
// =====================================================================================
