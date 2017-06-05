#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#include <iostream>

namespace Grafz
{
template<class T, class U>

/**
 * @brief The disjoint_set class
 * Disjoint sets are used primarily by Kruskal's minimum spanning tree algroithm.
 */
class  disjoint_set
{

private:
    set<shared_ptr<set<long>>> linkedsets;
public:
    disjoint_set()
    {

    }


    bool can_add_edge(std::shared_ptr<U> otheredge)
    {
        vector<shared_ptr<set<long>>> connected_sets;

        for(auto ln : linkedsets)
        {
            int c = 0;
            long fromptr = (long)(otheredge->from().get());
            long toptr = (long)(otheredge->to().get());

            bool fromin = ln->find(fromptr) != ln->end();
            bool toin = ln->find(toptr) != ln->end();

            if(fromin)
                c++;
            if(toin)
                c++;

            if(c > 1)
                return false;

            else if(c == 1)
            {
                connected_sets.push_back(ln);
            }

        }

        if(connected_sets.size() == 0)
        {
            shared_ptr<set<long>> newset = make_shared<set<long>>();
            newset->insert((long)otheredge->from().get());
            newset->insert((long)otheredge->to().get());

            linkedsets.insert(newset);
        }
        else
        {
            shared_ptr<set<long>> first = connected_sets.at(0);
            if(connected_sets.size() == 2)
            {
                shared_ptr<set<long>> second = connected_sets.at(1);

                first->insert(second->begin(), second->end());
                linkedsets.erase(second);
            }

            first->insert((long)otheredge->from().get());
            first->insert((long)otheredge->to().get());
            linkedsets.insert(first);

            if(connected_sets.size() > 2){
                cout << "BAD ! size of connected sets is too big"<<endl;
            }
        }
        return true;
    }
};
}
#endif
