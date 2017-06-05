#include <set>
#include <vector>
#include <memory>
#include <graph.h>


namespace Grafz
{

template<class T, class U>
std::vector<std::set<std::shared_ptr<T>>> find_maximal_cliques(Graph<T, U> &graph){

    std::set<std::shared_ptr<T>> R;
    std::set<std::shared_ptr<T>> X;
    std::set<std::shared_ptr<T>> P;

    auto cliques = find_cliques(graph, R,X,P);
    return cliques;

}

/**
 * @brief find_cliques
 * @param graph
 * @param R
 * @param X
 * @param P
 * @return
 */
template<class T, class U>
std::vector<std::set<std::shared_ptr<T>>> find_cliques(Graph<T, U> &graph, std::set<std::shared_ptr<T>> R, std::set<std::shared_ptr<T>> X, std::set<std::shared_ptr<T>> P)
{
    std::vector<std::set<std::shared_ptr<T>>> vertexSets;
    if (P.empty() || X.empty()) {
        vertexSets.push_back(R);
        return vertexSets;
    } else {
        std::set<std::shared_ptr<T>> vSet;
        for (T t : P) {
            if (vSet.contains(t))
	      continue;
	    
            std::set<T> R_(R);
            std::set<T> X_(X);
            std::set<T> P_(P);
            for (T d : vSet)
                P_.erase(d);

            for (iterator = P_.begin(); iterator != P_.end();iterator++ ) {
                if (!P.contains( * iterator)) {
                    P_.erase(iterator);
                }
            }
            R_.insert(t);
            for (T d : vSet)
                X_.insert(d);
            auto adj = graph.find_adjacent_vertices(t);
            std::set<std::shared_ptr<T>> adjset(adj.begin(), adj.end());
            for (iterator = X_.begin(); iterator != X_.end();iterator++ ) {
                if (!adjset.contains( * iterator)) {
                    X_.erase(iterator);
                }
            }

            vertexSets.push_back(find_cliques(graph, R_, X_, P_));
            vSet.insert(n);

        }
        return vertexSets;
    }
}

}
