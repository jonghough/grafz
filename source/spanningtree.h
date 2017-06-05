#ifndef SPANNING_TREE_H
#define SPANNING_TREE_H

#include <set>
#include <map>
#include <memory>
#include <algorithm>
#include <iostream>


#include "connectivity.h"
#include "graph.h"
#include "edge_data.h"
#include "disjointset.h"

namespace Grafz
{


/**
 * Implementation of Kruskal's algorithm to find a minimal spanning tree
 * for a given weighted graph.
 *
 */
template<class T, class U>
vector<shared_ptr<U>> find_minimum_spanning_tree(Graph<T,U>& graph)
{
    vector<shared_ptr<U>> edges_copy( graph.get_edges());// = new vector<shared_ptr<U>>( graph.get_edges());
    std::sort(edges_copy.begin(), edges_copy.end(), [](shared_ptr<U> i,shared_ptr<U> j)
    {
        return i.get()->get_weight()<j.get()->get_weight();
    }   );
    disjoint_set<T,U> disjoint_set;// = new Grafz::disjoint_set<T,U>();
    vector<shared_ptr<U>> spanning_tree_edges;

    while(edges_copy.size() > 0)
    {
        shared_ptr<U> first = edges_copy.at(0);
        if(disjoint_set.can_add_edge(first))
        {
            spanning_tree_edges.push_back(first);
        }

        edges_copy.erase(edges_copy.begin());
    }

    return spanning_tree_edges;
}

}
#endif
