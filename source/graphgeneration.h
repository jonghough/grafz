#ifndef GRAPHGENERATION
#define GRAPHGENERATION
#include <memory>
#include <stdint.h>
#include <vector>
#include <set>
#include <map>
#include "graph.h"
#include "base_edge.h"
#include "base_vertex.h"
#include "weighted_edge.h"
#include <algorithm>
#include <iterator>

namespace Grafz
{

/**
 * Generates a complete graph from the given vector of vertices.
 */
template<class T> std::shared_ptr<Graph<T, base_edge<T>>> generate_complete_graph(std::vector<std::shared_ptr<T>> vertices)
{
    std::vector<shared_ptr<base_edge<T>>> edgevec;
    for (int i = 0; i < vertices.size() - 1; i++) {
        for (int j = i + 1; j < vertices.size(); j++) {
            auto e = std::make_shared<base_edge<T>>(vertices.at(i), vertices.at(j));
            edgevec.push_back(e);
        }
    }
    auto graph =  std::make_shared<Graph<T, base_edge<T>>> (vertices,edgevec);
    return graph;
}

/**
 * @brief generate_vertices
 * @param num
 * @return
 */
std::vector<std::shared_ptr<base_vertex>> generate_vertices(uint32_t num)
{
    std::vector<std::shared_ptr<base_vertex>> vec;
    if (num == 0) return vec;
    else {
        for (int i = 0; i < num; i++) {
            auto v = std::make_shared<base_vertex>("vertex_"+std::to_string(i));
            vec.push_back(v);
        }
        return vec;
    }
}


/**
 * @brief generate_cyclic_graph
 * @param vertices
 *          a vector of vertices.
 * @return A cyclic graph of the given vertices, where vertices adjacent in the vector are made to
 *          be adjacent in the graph.
 */
template<class T>
std::shared_ptr<Graph<T,base_edge<T>>> generate_cyclic_graph(std::vector<std::shared_ptr<T>> vertices){
    //auto vertices = generate_vertices(vertex_count);
    std::vector<shared_ptr<base_edge<T>>> edgevec;
    for(uint32_t i = 0; i < vertices.size() - 1; i++){
        auto e = std::make_shared<base_edge<T>>(vertices.at(i), vertices.at(i + 1));
        edgevec.push_back(e);
    }
    auto ex = std::make_shared<base_edge<T>>(vertices.at(vertices.size() - 1), vertices.at(0));
    edgevec.push_back(ex);
    auto graph =  std::make_shared<Graph<T, base_edge<T>>> (vertices, edgevec);
    return graph;
}


/**
 * Generates a new graph isomorphic to the given graph with weighted edges of random weights.
 * Effectively, it clones the given graph as a weighted graph.
 */
template<class T, class U>
std::shared_ptr<Graph<T,weighted_edge<T>>> generate_random_weights(std::shared_ptr<Graph<T,U>> graph, std::function<shared_ptr<T>(T&)> clone_vertex){

    std::vector<std::shared_ptr<weighted_edge<T>>> edgevec;
    std::map<uint64_t, std::shared_ptr<T>> vertices;
    for(auto vertex : graph->get_vertices()){
        shared_ptr<T> t = clone_vertex(*(vertex.get()));
        vertices.insert(std::pair<uint64_t, std::shared_ptr<T>>((uint64_t)(vertex.get()), t));
    }
    for(auto edge : graph->get_edges()){
        auto from = vertices.find((uint64_t)(edge->from().get()))->second;
        auto to = vertices.find((uint64_t)(edge->to().get()))->second;
        auto shpte = std::make_shared<weighted_edge<T>>(from, to, 10.0f);
        edgevec.push_back(shpte);
    }
    std::vector<std::shared_ptr<T>> v;
    for( typename std::map<uint64_t, std::shared_ptr<T>>::iterator it = vertices.begin(); it != vertices.end(); ++it ) {
        v.push_back( it->second );
    }
    auto newGraph = std::make_shared<Graph<T, weighted_edge<T>>>(Graph<T, weighted_edge<T>>(v, edgevec));
    return newGraph;
}
}
#endif // GRAPHGENERATION

