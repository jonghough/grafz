#ifndef BICONNECTEDCOMPONENTGENERATOR
#define BICONNECTEDCOMPONENTGENERATOR
#include <memory>
#include "graph.h"
#include <stack>
#include <map>
#include <vector>
#include <set>
#include "nodedata.h"
#include <cmath>
#include <algorithm>
#include <iostream>
namespace Grafz
{
template<class T, class U>
/**
 * Splits a graph into biconnected components, where a
 * biconnected component of a graph is a connected subgraph of the graph such
 * that removing any edge from the subgraph still leaves a connected subgraph.
 * This class partitions the original grph into maximal such subgraphs.
 *
 * An example usage is finding all basic cycles of a graph. Partitioning
 * the graph into biconnected components allows easier calculations as there are
 * no cycles between any two components, and each vertex is contained in at least
 * one cycle in its component.
 */
class biconnected_component_generator final
{
private:
    Graph<T, U> &m_graph;

    std::stack<std::shared_ptr<U>> m_edge_stack;
    std::set<std::set<std::shared_ptr<U>>> m_connected_sets;
    std::map<std::shared_ptr<T>, node_data<T>> m_data_map;
    int m_counter;

    /**
     * @brief visit_node
     * visit the given node, pushing it onto the stack.
     * @param node a node in the graph
     */
    void visit_node(std::shared_ptr<T> node) {
        m_data_map.find(node)->second.visited = true;
        m_counter++;
        m_data_map.find(node)->second.depth = m_counter;
        m_data_map.find(node)->second.low = m_counter;

        for (auto next_edge : m_graph.find_incident_edges(node)) {
            auto next_node = next_edge->from() == node ? next_edge->to() : next_edge->from();
            if (!m_data_map.find(next_node)->second.visited) {
                m_edge_stack.push(next_edge);
                m_data_map.find(next_node)->second.parent = node;
                visit_node(next_node);
                if (m_data_map.find(next_node)->second.low >= m_data_map.find(node)->second.depth) {
                    m_connected_sets.insert(get_biconnected_nodes(next_edge));
                }
                m_data_map.find(node)->second.low = std::min(m_data_map.find(next_node)->second.low, m_data_map.find(node)->second.low);
            } else if (m_data_map.find(node)->second.parent != next_node && m_data_map.find(node)->second.depth > m_data_map.find(next_node)->second.depth) {
                m_edge_stack.push(next_edge);
                m_data_map.find(node)->second.low = std::min(m_data_map.find(next_node)->second.depth, m_data_map.find(node)->second.low);
            }
        }
    }

    std::set<std::shared_ptr<U>> get_biconnected_nodes(std::shared_ptr<U> edge) {

        std::set<std::shared_ptr<U>> edge_set;
        while (true) {
            if (m_edge_stack.size() == 0) break;

            auto e = m_edge_stack.top();
            m_edge_stack.pop();
            edge_set.insert(e);
            if (edge.get() == e.get()) break;

        }
        return edge_set;
    }

public:
    /**
     * @brief biconnected_component_generator
     * Creates an instance of the biconnected_component_generator class. The instance can be used
     * to partition the graph object into biconnected components.
     * @param graph - graph to partition into biconnected components.
     */
    biconnected_component_generator(Graph<T, U> &graph) : m_graph(graph), m_counter(0) {
      
    }

    ~biconnected_component_generator(){}

    /**
     * @brief find_biconnected_components
     * Finds biconnected components of this instance's graph. The resulting biconnected
     * components can then be found with the get_connected_sets() function.
     */
    void find_biconnected_components() {

        for (auto vertex : m_graph.get_vertices()) {

            node_data<T> nd;
            m_data_map.insert(std::pair<std::shared_ptr<T>, node_data<T>>(vertex, nd));
        }

        for (auto vertex : m_graph.get_vertices()) {
            if (!m_data_map.find(vertex)->second.visited) {
                visit_node(vertex);
            }
        }
    }

    /**
     * @brief get_connected_sets
     * Returns a set containing sets of (shared pointers to) edges, where each set represents a biconnected component
     * of the graph. The function find_biconnected_components() must be calle dfirst to generate the biconnected
     * component sets.
     * @return biconnected components, represented by sets of edges.
     */
    std::set<std::set<std::shared_ptr<U>>> get_connected_sets() {
        return m_connected_sets;
    }

};
}
#endif // BICONNECTEDCOMPONENTGENERATOR

