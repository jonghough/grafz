#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H
#include <functional>
#include "graph.h"
#include <vector>
#include "base_edge.h"
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;


namespace Grafz
{

/**
 * @brief is_connected
 * Determines whether the graph, g, is connected.
 * @param g graph
 * @return True if connected, false otherwise
 */
template<class T, class U>
bool is_connected(Graph<T,U> &g)
{
    int count = 0;
    auto xlambda = [&count](T& vertex1, T& vertex2)-> bool
    {
        count++;
        return false;
    };

    g.search_vertices_breadth_first(xlambda);
    return count == g.get_vertices().size();
}



template<class T, class U>
/**
 * @brief find_connected_vertices
 * Finds all the vertices in the graph which are adjacent to the given vertex.
 * (i.e. connected by an edge).
 *
 * @param g graph
 * @param vertex - given vertex
 * @return vector containing the adjacent vertices.
 */
vector<std::shared_ptr<T>> find_connected_vertices(Graph<T,U> &g, shared_ptr<T>& vertex)
{
    vector<std::shared_ptr<T>> connected_vertices {};
    auto adjacent_unvisited = g.find_adjacent_unvisited(vertex);
    for(auto v : adjacent_unvisited)
    {
        v->set_visited(true);
        connected_vertices.push_back(v);
    }

    for(auto v : adjacent_unvisited)
    {
        vector<std::shared_ptr<T>> cv = find_connected_vertices(g,v);
        connected_vertices.insert(connected_vertices.end(),cv.begin(), cv.end() );
    }
    return connected_vertices;
}





/**
 * @brief find_connected_components
 * Finds the connected components of the graph g. That is, partitions the
 * vertex-set of g into sets, were each set can be considered as a connected subgraph of g.
 * @param g graph
 * @return vector containing the partitioned vertex subsets.
 */
template<class T, class U>
vector<vector<std::shared_ptr<T>>> find_connected_components(Graph<T,U> &g)
{
    g.set_all_vertex_visited(false);
    vector< vector<std::shared_ptr<T> > > components;
    shared_ptr<T> vertex = g.get_first_unvisited_node();
    while(true)
    {
        vector<std::shared_ptr<T>> conns = Grafz::find_connected_vertices(g, vertex);
        vertex->set_visited(true);
        components.emplace_back(conns);
        vertex = g.get_first_unvisited_node();
        if(vertex == nullptr)
        {
            break;
        }

    }
    return components;
}


/**
 * @brief find_maximal_connected_subgraphs
 * Finds maximal conneected subgraphs of the graph g.
 * @param g Graph
 * @return vector of subgraphs of g, where each graph is a maximally
 * connected subgraph of g.
 */
template<class T, class U>
vector<shared_ptr<Graph<T,U>>> find_maximal_connected_subgraphs(Graph<T,U> &g)
{
    vector<vector<std::shared_ptr<T>>> components = find_connected_components(g);
    vector<shared_ptr<Graph<T,U>>> maximal_subgraphs {};
    for(vector<std::shared_ptr<T>> vec : components)
    {
        std::set<shared_ptr<U>> edge_set;
        for(auto edge : g.get_edges())
        {
            if(std::find(vec.begin(), vec.end(), edge->from()) != vec.end())
            {
                edge_set.emplace(edge);
            }
            else if(std::find(vec.begin(), vec.end(), edge->to()) != vec.end())
            {
                edge_set.emplace(edge);
            }
        }
        vector<shared_ptr<U>> edge_vec(edge_set.size());
        std::copy(edge_set.begin(), edge_set.end(), std::back_inserter(edge_vec));
        auto subg = std::make_shared<Graph<T,U>>(vec, edge_vec);
        maximal_subgraphs.emplace_back(subg);
    }
    return maximal_subgraphs;
}

}

#endif // CONNECTIVITY_H
