#ifndef CYCLES_H
#define CYCLES_H
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <iostream>
#include "graph.h"
#include "biconnected_component_generator.h"
#include "edge_data.h"

namespace Grafz
{


/**
 * @brief merge_cycles
 * Merges cycles into unique basic cycles by cancelling out any cycles that
 * are cyclic permutations of other cycles.
 * @param cycles the set of cycle-sets
 * @return unique basic cycles.
 */
template<class T>
vector<vector<shared_ptr<T>>> merge_cycles(vector<vector<shared_ptr<T>>> cycles)
{
    map<long, vector<shared_ptr<T>>> cycle_map;

    for(auto cyc : cycles)
    {
        long signature = 0;
        for(int counter = 0; counter < cyc.size(); counter++)
        {
            int prev = 0;
            int next = 0;
            if(counter == 0)
                prev = cyc.size() - 1;
            else prev = counter - 1;
            if(counter == cyc.size() - 1)
                next = 0;
            else next = counter + 1;
            auto counter_ptr = (long)cyc.at(counter).get();
            auto prev_ptr = (long)cyc.at(prev).get();
            auto next_ptr = (long)cyc.at(next).get();
            auto a = counter_ptr * counter_ptr * prev_ptr * next_ptr;
            signature += (long)(a + (a>>1) | (a<<3)) ;
        }
        if(cycle_map.count(signature) == 0)
        {
            cycle_map.insert(pair<long, vector<shared_ptr<T>>>(signature, cyc));
        }
        else
        {
            cycle_map.at(signature) = cyc;
        }
    }

    vector<vector<shared_ptr<T>>> all_cycles;
    for(auto cyc : cycle_map)
    {
        all_cycles.push_back(cyc.second);
    }

    return all_cycles;
}

/**
 * @brief add_to_path
 * Adds the curren_ver vertex to the current path and searches for any cycle in the cyc_stack, stack of already
 * visited vertices.
 * @param graph
 * @param edge_visit_data
 * @param previous_vert
 * @param current_vert
 * @param cyc_stack
 * @return
 */
template<class T, class U>
vector<vector<shared_ptr<T>>> add_to_path(Graph<T,U>& graph, map<shared_ptr<U>,edge_data<T,U>>& edge_visit_data,
        shared_ptr<T> previous_vert, shared_ptr<T> current_vert, vector<shared_ptr<T>> * cyc_stack)
{

    vector<vector<shared_ptr<T>>> cycle_list;

    for(size_t i = 0; i < cyc_stack->size() - 1; i++)
    {
        auto vert = cyc_stack->at(i);
        if(vert.get() == current_vert.get())
        {
            vector<shared_ptr<T>> cycle;
            for(size_t j = i; j < cyc_stack->size(); j++)
            {
                cycle.push_back(cyc_stack->at(j));
            }
            cycle_list.push_back(cycle);
            return cycle_list;
        }
    }

    auto incident_edges = graph.find_incident_edges(current_vert);
    cyc_stack->push_back(current_vert);
    for(auto edgedata : incident_edges)
    {
        if(!edge_visit_data.find(edgedata)->second.is_visited())
        {
            edge_visit_data.find(edgedata)->second.set_visited(true);
            if(edgedata.get()->from().get() != previous_vert.get() && edgedata.get()->from().get() != current_vert.get())
            {
                auto next_path = add_to_path(graph, edge_visit_data, current_vert, edgedata.get()->from(),cyc_stack);
                cycle_list.insert(cycle_list.end(), next_path.begin(), next_path.end());
            }
            if(edgedata.get()->to().get() != previous_vert.get() && edgedata.get()->to().get() != current_vert.get())
            {
                auto next_path = add_to_path(graph, edge_visit_data, current_vert, edgedata.get()->to(),cyc_stack);
                cycle_list.insert(cycle_list.end(), next_path.begin(), next_path.end());
            }
        }
        edge_visit_data.find(edgedata)->second.set_visited(false);
    }

    cyc_stack->pop_back();
    return cycle_list;
}

template<class T, class U>
vector<vector<shared_ptr<T>>> find_all_cycles(Graph<T,U> &graph)
{
    biconnected_component_generator<T,U> bcg(graph);
    bcg.find_biconnected_components();
    auto bcs = bcg.get_connected_sets();

    vector<vector<shared_ptr<T>>> cycle_vec;
    map<shared_ptr<U>, edge_data<T,U>> all_edge_data;
    bool select = false;
    shared_ptr<T> vertex = graph.get_vertices().at(0);



    for(auto edge : graph.get_edges())
    {
        all_edge_data.insert(pair<shared_ptr<U>, edge_data<T,U>>(edge, edge_data<T,U>(edge)));
    }

    auto adjacent = graph.find_adjacent_vertices(vertex);
    for(auto vert : adjacent)
    {
        if(vert.get() == vertex.get())
            continue;
        vector<shared_ptr<T>> * cyc_stack = new vector<shared_ptr<T>>();
        cyc_stack->push_back(vertex);
        auto cycles_sub = add_to_path(graph, all_edge_data, vertex, vert, cyc_stack);
        cycle_vec.insert(cycle_vec.end(), cycles_sub.begin(), cycles_sub.end());
        delete(cyc_stack);
    }
    return merge_cycles(cycle_vec);
}


}

#endif
