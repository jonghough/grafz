#ifndef GRAPH_H
#define GRAPH_H
#include <queue>
#include <vector>
#include <stack>
#include <functional>
#include "base_vertex.h"
#include "base_edge.h"
#include <memory>

 namespace Grafz {
   
template<class T, class U>
class Graph
{
public:

    /**
     * @brief Graph
     * @param vertexSet
     * @param edgeSet
     */
    Graph(std::vector<std::shared_ptr<T>>& vertexSet, std::vector<std::shared_ptr<U>>& edgeSet) : m_vertex_set(vertexSet), m_edge_set(edgeSet) {
        //static_assert(std::is_base_of<base_vertex, T>::value, "T must be derived from base_vertex.");
        //static_assert(std::is_base_of<base_edge<T>, U>::value, "U must be derived from base_edge<T>, where T derives from base_vertex.");
    }

    /**
     * @brief get_vertices
     * @return
     */
    std::vector<std::shared_ptr<T>> &get_vertices() {
        return m_vertex_set;
    }

    /**
     * @brief get_edges
     * @return
     */
    std::vector<std::shared_ptr<U>> &get_edges() {
        return m_edge_set;
    }


    void set_all_vertex_visited(bool visited) {
        for (auto it = m_vertex_set.begin(); it != m_vertex_set.end(); ++it) {
            std::shared_ptr<T> t = *it;
            t->set_visited(visited);
        }
    }
    /**
     * Function argument's parameters  are previous visited vertex
     * and current visited vertex. This function returns true to
     * short-circuit the search, false to keep searching.
     * @brief search_vertices_breadth_first
     */
    void search_vertices_breadth_first(std::function<bool(T &, T &)> on_next_vert) {

        std::queue<std::shared_ptr<T>> vert_queue;
        bool selected = false;
        for (auto it = m_vertex_set.begin(); it != m_vertex_set.end(); ++it) {
            if (!selected) {
                vert_queue.push(*it);
                selected = true;
            }
            std::shared_ptr<T> t = *it;
            t->set_visited(false);
        }

        while (!vert_queue.empty()) {
            std::shared_ptr<T> v = vert_queue.front();
            vert_queue.pop();
            std::vector<std::shared_ptr<T>> adjacent = find_adjacent_vertices(v);
            for (auto adj : adjacent) {
                auto adj_ptr = adj;
                if (!adj_ptr->is_visited()) {
                    bool stop = on_next_vert(*v, *adj_ptr);
                    adj_ptr -> set_visited(true);
                    vert_queue.push(adj);
                    if (stop)
                        break;
                }
            }
        }

    }

    /**
     * @brief search_vertices_depth_first
     */
    void search_vertices_depth_first(std::function<bool(T &, T &)> on_next_vert) {
        std::stack<std::shared_ptr<T>> vert_stack;
        bool selected = false;
        for (auto it = m_vertex_set.begin(); it != m_vertex_set.end(); ++it) {
            if (!selected) {
                vert_stack.push(*it);
                selected = true;
            }
            std::shared_ptr<T> t = *it;
            t->set_visited(false);
        }

        while (!vert_stack.empty()) {
            std::shared_ptr<T> v = vert_stack.top();
            vert_stack.pop();
            std::vector<std::shared_ptr<T>> adjacent = find_adjacent_vertices(v);
            for (auto adj : adjacent) {
                auto adj_ptr = adj;
                if (!adj_ptr->is_visited()) {
                    bool stop = on_next_vert(*v, *adj_ptr);
                    adj_ptr -> set_visited(true);
                    vert_stack.push(adj);
                    if (stop)
                        break;
                }
            }
        }
    }

    /**
     * @brief search_edges_breadth_first
     */
    void search_edges_breadth_first(std::function<bool(U &, U &)> on_next_edge) {
        std::queue<std::shared_ptr<U>> edge_queue;
        bool selected = false;
        for (auto it = m_edge_set.begin(); it != m_edge_set.end(); ++it) {
            if (!selected) {
                edge_queue.push(*it);
                selected = true;
            }
            std::shared_ptr<U> u = *it;
            u->set_visited(false);
        }

        while (!edge_queue.empty()) {
            std::shared_ptr<U> edge = edge_queue.front();
            edge_queue.pop();
            std::vector<std::shared_ptr<U>> incident = find_incident_edges(edge);
            for (auto inc : incident) {
                auto inc_ptr = inc;
                if (!inc_ptr->is_visited()) {
                    bool stop = on_next_edge(*edge, *inc_ptr);
                    inc_ptr -> set_visited(true);
                    edge_queue.push(inc);
                    if (stop)
                        break;
                }
            }
        }
    }

    /**
     * @brief search_edges_depth_first
     * Searches through the graph's edge set usign a DFS, starting
     * at an arbitrary edge. If the graph is not connected, not all
     * edges will be reached.
     * The function parameter takes the previous edge and the current
     * edge as parameters, and is caled on each iteration of the DFS.
     * If the callback returns true the DFS is short-circuited and
     * stops.
     */
    void search_edges_depth_first(std::function<bool(U &, U &)>) {}

    /**
     * @brief get_first_unvisited_node
     * @return
     */
    std::shared_ptr<T> get_first_unvisited_node() {
        for (auto v : m_vertex_set) {
            if (!v->is_visited())
                return v;
        }
        return nullptr;
    }

    /**
     * @brief find_adjacent_vertices
     * Finds all the vertices on the graph that are adjacent
     * to the given vertex, where adjacent
     * means that the two vertices share a common edge.
     * This function allocates a new vector of the adjacent
     * vertices, and returns the vector.
     * @param vertex
     * @return
     */
    std::vector<std::shared_ptr<T>> find_adjacent_vertices(std::shared_ptr<T> vertex) {
        std::vector<std::shared_ptr<T>> adjacent;// = new vector<std::shared_ptr<T>>();;
        for (auto e : m_edge_set) {
            auto e_ptr = e;
            std::shared_ptr<T> f = e_ptr->from();
            std::shared_ptr<T> t = e_ptr->to();
            if (f.get() == vertex.get()) {
                adjacent.push_back(t);
            } else if (t.get() == vertex.get()) {
                adjacent.push_back(f);
            }

        }
        return adjacent;
    }

    /**
     * @brief find_adjacent_unvisited
     * Finds all the vertices on the graph that are adjacent and
     * unvisited to the given vertex, where adjacent
     * means that the two vertices share a common edge.
     * This function allocates a new vector of the adjacent, unvisited
     * vertices, and returns the vector.
     * @param vertex
     * @return
     */
    std::vector<std::shared_ptr<T>> find_adjacent_unvisited(std::shared_ptr<T> vertex) {
        std::vector<std::shared_ptr<T>> adjacent;// = new vector<std::shared_ptr<T>>();;
        for (auto e : m_edge_set) {
            auto e_ptr = e;
            std::shared_ptr<T> f = e_ptr->from();
            std::shared_ptr<T> t = e_ptr->to();
            if (f.get() == vertex.get() && !t->is_visited()) {
                adjacent.push_back(t);
            } else if (t.get() == vertex.get() && !f->is_visited()) {
                adjacent.push_back(f);
            }

        }
        return adjacent;
    }

    /**
     * @brief find_incident_edges
     * Find's all edges on the graph which are incident with the given
     * edge, where incident means that the two edges share a common
     * vertex.
     * This function allocates a new vector of the incident edges and
     * reutrns the vector.
     * @param edge
     * @return
     */
    std::vector<std::shared_ptr<U>> find_incident_edges(std::shared_ptr<U> edge) {

        std::shared_ptr<T> f_ptr = edge -> from();
        std::shared_ptr<T> t_ptr = edge -> to();
        std::vector<std::shared_ptr<U>> edge_vec;// = new vector<std::shared_ptr<U>>();
        for (auto e : m_edge_set) {
            //dont include self
            if (edge.get() == e.get())
                continue;
            if (e->from().get() == f_ptr.get() || e->to().get() == f_ptr.get()
            || e->from().get() == t_ptr.get() || e->to().get() == t_ptr.get()) {
                edge_vec.push_back(e);
            }
        }
        return edge_vec;
    }


    std::vector<std::shared_ptr<U>> find_incident_edges(std::shared_ptr<T> vertex) {
        std::vector<std::shared_ptr<U>> edge_vec;// = new vector<std::shared_ptr<U>>();
        for (auto e : m_edge_set) {
            if (e->from().get() == vertex.get() || e->to().get() == vertex.get()) {
                edge_vec.push_back(e);
            }
        }
        return edge_vec;
    }


protected:

    /**
     * @brief m_vertex_set
     */
    std::vector<std::shared_ptr<T>> m_vertex_set;

    /**
     * @brief m_edge_set
     */
    std::vector<std::shared_ptr<U>> m_edge_set;
};
 }
#endif // GRAPH_H
