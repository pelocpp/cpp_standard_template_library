#pragma once

// PeLo dieses pragma once vielleicht öfters einfügen ...

// =====================================================================================
// Solver_Kruskal
// =====================================================================================

namespace Solver_Kruskal_Ex {

    template <typename EDGE>
    class KruskalSolverEx {
        const IGraphEx<EDGE>* m_graph;
        std::vector<IndexType> m_root;  // root nodes ('Union Find' algorithm)
        std::vector<EDGE> m_mst;        // minimum spanning tree (described with edges)

    public:
        // c'tor
        KruskalSolverEx() : m_graph(nullptr) {}

        // public interface
        void setGraph(const IGraphEx<EDGE>*);
        void initRootNodes();
        void solve();
        int findSet(IndexType);
        void unionSet(IndexType, IndexType);
        void printMST();
    };

    template <typename EDGE>
    void KruskalSolverEx<EDGE>::setGraph(const IGraphEx<EDGE>* graph) {
        m_graph = graph;
    }

    template <typename EDGE>
    void KruskalSolverEx<EDGE>::solve() {
        initRootNodes();

        // retrieve and sort all edges
        std::vector<EDGE> edges = m_graph->getAllEdges();

        std::sort(
            std::begin(edges),
            std::end(edges),
            [](const EDGE& edge1, const EDGE& edge2) -> bool {
                return getWeight<EDGE, int>(edge1) < getWeight<EDGE, int>(edge2);
            }
        );

        for (const EDGE& edge : edges) {

            IndexType source = getSource(edge);
            IndexType target = getTarget(edge);

            IndexType sourceRepresentative = findSet(source);
            IndexType targetRepresentative = findSet(target);

            if (sourceRepresentative != targetRepresentative) {
                m_mst.push_back(edge); // add to minimum spanning tree
                unionSet(sourceRepresentative, targetRepresentative);
            }
        }
    }

    template <typename EDGE>
    int KruskalSolverEx<EDGE>::findSet(IndexType index) {
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

    template <typename EDGE>
    void KruskalSolverEx<EDGE>::unionSet(IndexType u, IndexType v) {
        m_root[u] = m_root[v];
    }

    template <typename EDGE>
    void KruskalSolverEx<EDGE>::initRootNodes() {
        // initialize root nodes
        m_root.resize(m_graph->countNodes());
        std::generate(std::begin(m_root), std::end(m_root), [n = 0]() mutable->IndexType {
            return n++;
        });
    }

    template <typename EDGE>
    void KruskalSolverEx<EDGE>::printMST() {
        std::cout << "Edge :" << " Weight" << std::endl;
        for (EDGE edge : m_mst) {
            std::cout
                << getSource(edge) << " - "
                << getTarget(edge) << " : "
                << getWeight<EDGE, int>(edge);
            std::cout << std::endl;
        }
    }
}

// =====================================================================================
// End-of-File
// =====================================================================================
