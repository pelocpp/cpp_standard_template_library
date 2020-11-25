// =====================================================================================
// IGraph.h
// =====================================================================================

template <typename NODE, typename EDGE>
class IGraph
{
public:
    virtual int countNodes() const = 0;
    virtual int countEdges() const = 0;

    virtual bool isDirected() const = 0;
    virtual bool isWeighted() const = 0;

    virtual void addNodes(const std::vector<NODE>&) = 0;
    virtual void addNodes(const std::initializer_list<NODE> list) = 0;
    virtual NODE getNode(IndexType node) const = 0;
    virtual std::vector<NODE> getAllNodes() const = 0;   // PeLo : Das sollte auch mit einem Iterator gehen !!!!

    virtual void addEdges(const std::vector<EDGE>&) = 0;
    virtual void addEdges(const std::initializer_list<EDGE> list) = 0;
    // virtual NODE getNode(IndexType node) const = 0;
    virtual std::vector<EDGE> getAllEdges() const = 0;

    // PeL: umbenennen: From -> To
    virtual EDGE searchEdge(IndexType source, IndexType target) const = 0;

    virtual std::vector<IndexType> getNeighbouringNodes(IndexType node) const = 0;
    virtual std::vector<EDGE> getNeighbouringEdges(IndexType node) const = 0;

    virtual std::string toString() const = 0;
};

// =====================================================================================
// End-of-File
// =====================================================================================
