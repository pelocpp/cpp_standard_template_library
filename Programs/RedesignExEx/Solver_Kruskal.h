// =====================================================================================
// Graph Theory Redesign // Summer 2023 // Solver_Kruskal.h
// =====================================================================================

#pragma once

#include "Graph.h"

using namespace Graph_Theory;

namespace Graph_Theory_Kruskal
{
    // template <typename Weight, typename NodeDescription = int>
    template <typename T, typename W>
    class KruskalSolver
    {
    private:
        const Graph<T, W>& m_graph;
        std::vector<size_t> m_root;       // root nodes ('Union Find' algorithm)
        std::vector<Edge<W>> m_mst;  // minimum spanning tree (described with edges)

    public:
        KruskalSolver(const Graph<T, W>& graph) : m_graph{ graph } {}

        void initRootNodes() {
            // initialize root nodes
            m_root.resize(m_graph.countNodes());

            std::generate(
                std::begin(m_root),
                std::end(m_root), 
                [n = 0]() mutable -> size_t {
                    return n++;
                }
            );
        }

        void solve() {

            initRootNodes();

            // retrieve and sort all edges
            std::vector<Edge<W>> edges = m_graph.getAllEdges();

            std::sort(
                std::begin(edges),
                std::end(edges),
                [](const Edge<W>& edge1, const Edge<W>& edge2) -> bool {

                    W x1 = getEdgeWeight(edge1);
                    W x2 = getEdgeWeight(edge2);

                    return x1 < x2;

                    // return getWeight<EDGE, int>(edge1) < getWeight<EDGE, int>(edge2);
                }
            );

            for (const Edge<W>& edge : edges) {

                size_t source = getEdgeSource(edge);
                size_t target = getEdgeTarget(edge);

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
            for (const Edge<W>& edge : m_mst) {
                std::cout
                    << getEdgeSource(edge) << " - "
                    << getEdgeTarget(edge) << " : "
                    << getEdgeWeight<W>(edge);
                std::cout << std::endl;
            }
        }
    };

}

// =====================================================================================
// End-of-File
// =====================================================================================
