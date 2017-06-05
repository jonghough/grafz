#ifndef GRAPHSEARCH_H
#define GRAPHSEARCH_H
#include <functional>
#include <memory>
#include <map>
#include <vector>
#include <set>
#include <limits>
#include <iostream>
#include <stdexcept>

#include "graph.h"
#include "base_edge.h"
#include "weighted_edge.h"
#include "vertex_data.h"
#include "directed_edge.h"
#include "directed_weighted_edge.h"
#include "edge_direction.h"

namespace Grafz
{
template<class T, class U>
map<shared_ptr<T>, float> get_adjacent_vertices_with_weights(Graph<T, U> &graph, shared_ptr<T> &vertex)
{
    map<shared_ptr<T>, float> node_map;
    for (auto edge : graph.get_edges()) {
        if (edge -> from().get() == vertex.get()) {
            node_map.insert(pair<shared_ptr<T>, float>(edge->to(), edge->get_weight()));
        } else if (edge -> to().get() == vertex.get()) {
            node_map.insert(pair<shared_ptr<T>, float>(edge->from(), edge->get_weight()));
        }
    }
    return node_map;
}

/**
 * Implementation of Dijkstra's algorithm for finding the minimum path between two vertices on
 * a weighted graph, where all weights are assumed non-negative single floating points.
 *
 *
 */
template<class T, class U>
vector<shared_ptr<T>> find_min_path_with_dijkstra(Graph<T, U> &graph, shared_ptr<T> &source, shared_ptr<T> &sink)
{
    static_assert(is_base_of<weighted_edge<T>, U>::value, "U must be derived from weighted_edge.");

    map<shared_ptr<T>, vertex_data<T>> previous_map;
    vector<shared_ptr<T>> min_path;

    for (auto vert : graph.get_vertices()) {
        if (vert.get() == source.get()) {
            previous_map.insert(pair < shared_ptr<T>,
                                vertex_data<T >> (vert, vertex_data<T>(0.0f)));
        } else {
            previous_map.insert(pair < shared_ptr<T>,
                                vertex_data<T >> (vert, vertex_data<T>(numeric_limits<float>::max())));
        }
        previous_map.find(vert)->second.set_visited(false);
    }
    bool ok = true;
    while (ok) {
        shared_ptr<T> current_vert = nullptr;
        float dist = numeric_limits<float>::max();
        for (auto vert : graph.get_vertices()) {
            if (!previous_map.find(vert)->second.is_visited()) {
                if (current_vert == nullptr) {
                    current_vert = vert;
                    dist = previous_map.find(current_vert)->second.get_distance();
                } else {
                    if (previous_map.find(vert)->second.get_distance() < dist) {
                        current_vert = vert;
                        dist = previous_map.find(current_vert)->second.get_distance();
                    }
                }
            }
        }
        if (current_vert == nullptr) {
            ok = false;
            break;
        }

        if (current_vert.get() == sink.get()) {
            ok = false;
        }

        previous_map.find(current_vert)->second.set_visited(true);

        map<shared_ptr<T>, float> adjacent_with_weights = get_adjacent_vertices_with_weights(graph, current_vert);


        typedef typename map<shared_ptr<T>, float>::iterator MapIter;
        MapIter map_iterator;
        for (map_iterator = adjacent_with_weights.begin(); map_iterator != adjacent_with_weights.end(); map_iterator++) {
            if (previous_map.find(map_iterator->first)->second.is_visited()) {
                continue;
            } else {
                float possible = previous_map.find(current_vert)->second.get_distance() + map_iterator->second;
                if (possible < previous_map.find(map_iterator->first)->second.get_distance()) {
                    vertex_data<T> v_data(possible);
                    v_data.set_distance(possible);
                    v_data.set_previous(current_vert);
                    previous_map.at(map_iterator->first) = v_data;
                }
            }
        }
    }

    shared_ptr<T> vrtx = previous_map.find(sink)->second.get_previous();
    min_path.push_back(sink);

    while (true) {
        min_path.push_back(vrtx);
        vrtx = previous_map.find(vrtx)->second.get_previous();

        if (vrtx.get() == source.get()) {
            min_path.push_back(vrtx);
            break;
        }
    }

    return min_path;
}

/**
 * Implements a A* minimum path search between two points, source and sink, on a
 * weighted graph, where weights are assumed to be non-negative. The A* heuristic
 * function is given by the heuristic parameter.
 *
 */
template<class T, class U>
vector<shared_ptr<T>> find_min_path_with_astar(Graph<T, U> &graph, shared_ptr<T> &source, shared_ptr<T> &sink,
                   function<float(shared_ptr<T>, shared_ptr<T>)> heuristic)
{
    static_assert(is_base_of<weighted_edge<T>, U>::value, "U must be derived from weighted_edge.");

    map<shared_ptr<T>, vertex_data<T>> previous_map;
    vector<shared_ptr<T>> min_path;

    set<shared_ptr<T>> open_set;
    set<shared_ptr<T>> closed_set;
    map<shared_ptr<T>, float> g_score_map;
    map<shared_ptr<T>, float> f_score_map;

    open_set.insert(source);

    for (auto t : graph.get_vertices()) {
        g_score_map.insert(pair<shared_ptr<T>, float>(t, numeric_limits<float>::max()));
        f_score_map.insert(pair<shared_ptr<T>, float>(t, 0.0f));
        previous_map.insert(pair < shared_ptr<T>,
                            vertex_data<T >> (t, vertex_data<T>(0.0f)));
    }

    g_score_map.at(source) = 0.0f;
    f_score_map.at(source) = 0.0f + heuristic(source, sink);

    while (open_set.size() > 0) {
        shared_ptr<T> current_vert = nullptr;
        for (auto item : open_set) {
            if (current_vert == nullptr) {
                current_vert = item;
            } else {
                if (f_score_map.find(current_vert)->second > f_score_map.find(item)->second) {
                    current_vert = item;
                }
            }
        }

        if (current_vert == sink) {
            min_path.push_back(current_vert);
        }

        open_set.erase(current_vert);
        closed_set.insert(current_vert);

        auto inc_edges = graph.find_incident_edges(current_vert);

        for (auto edge : inc_edges) {
            auto from_v = edge->from();
            auto to_v = edge->to();
            auto tmp = g_score_map.find(current_vert)->second + edge->get_weight();
            vector<shared_ptr<T>> edge_vs = {from_v, to_v};
            for (auto vert : edge_vs) {
                if (vert.get() == current_vert.get()) {
                    continue;
                } else if (closed_set.find(vert) == closed_set.end()) {

                    if (open_set.find(vert) == open_set.end()) {
                        vertex_data<T> v_data(tmp);
                        v_data.set_distance(tmp);
                        v_data.set_previous(current_vert);
                        previous_map.at(vert) = v_data;
                        g_score_map.at(vert) = tmp;
                        f_score_map.at(vert) = tmp + heuristic(vert, sink);
                        open_set.insert(vert);
                    } else {

                        auto dist_vert = g_score_map.find(vert)->second;
                        if (tmp < dist_vert) {
                            vertex_data<T> v_data(tmp);
                            v_data.set_distance(tmp);
                            v_data.set_previous(current_vert);
                            previous_map.at(vert) = v_data;
                            g_score_map.at(vert) = tmp;
                            f_score_map.at(vert) = tmp + heuristic(vert, sink);
                        }
                    }
                }
            }
        }
    }

    shared_ptr<T> vrtx = previous_map.find(sink)->second.get_previous();

    while (true) {
        min_path.push_back(vrtx);
        vrtx = previous_map.find(vrtx)->second.get_previous();

        if (vrtx.get() == source.get()) {
            min_path.push_back(vrtx);
            break;
        }
    }

    return min_path;
}



/**
 *  Finds the minimum path between source and sink vertices using Bellman-Ford
 *  algorithm.
 * 
 * 
 */
template<class T, class U>
vector<shared_ptr<T>> find_min_path_with_bellman_ford(Graph<T, U> &graph, shared_ptr<T> &source, shared_ptr<T> &sink)
{
    vector<shared_ptr<T>> path;
    auto nodes = graph.get_vertices();
    map<shared_ptr<T>, vertex_data<T>> node_map;
    float MAX = numeric_limits<float>::max();
    for (auto vert : graph.get_vertices()) {
        if (vert.get() == source.get()) {
            node_map.insert(pair < shared_ptr<T>,
                            vertex_data<T >> (vert, vertex_data<T>(0.0f)));
        } else {
            node_map.insert(pair < shared_ptr<T>,
                            vertex_data<T >> (vert, vertex_data<T>(MAX)));
        }
    }

    for (auto v : node_map) {
        for (auto e : graph.get_edges()) {
            if (e->get_direction() == Edge_Direction::FORWARD) {
                float tmp = node_map.find(e->from())->second.get_distance() + e->get_weight();
                if (tmp < node_map.find(e->to())->second.get_distance()) {
                    node_map.find(e->to())->second.set_distance(tmp);
                    node_map.find(e->to())->second.set_previous(e->from());
                }
            } else if (e->get_direction() == Edge_Direction::BACKWARD) {
                float tmp = node_map.find(e->to())->second.get_distance() + e->get_weight();
                if (tmp < node_map.find(e->from())->second.get_distance()) {
                    node_map.find(e->from())->second.set_distance(tmp);
                    node_map.find(e->from())->second.set_previous(e->to());
                }
            }
        }

    }


    for (auto edge : graph.get_edges()) {

        float tmp = node_map.find(edge->from())->second.get_distance() + edge->get_weight();
        if (tmp < node_map.find(edge->to())->second.get_distance()) {
           throw std::exception();
        }
    }

    shared_ptr<T> vrtx = node_map.find(sink)->second.get_previous();
    path.push_back(sink);
    while (true) {
        path.push_back(vrtx);
        vrtx = node_map.find(vrtx)->second.get_previous();

        if (vrtx.get() == source.get()) {
            path.push_back(vrtx);
            break;
        }
    }
    return path;
}

}
#endif // GRAPHSEARCH_H
