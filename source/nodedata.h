#ifndef NODEDATA_H
#define NODEDATA_H
#include <memory>

namespace Grafz{

template<class T>
struct node_data {
public:
    bool visited;
    std::shared_ptr<T> parent;
    int depth;
    int low;

    node_data(){
        visited = false;
        depth = low = 0;
    }

};
}
#endif // NODEDATA_H

