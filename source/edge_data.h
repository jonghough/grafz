#ifndef EDGE_DATA
#define EDGE_DATA
#include <vector>
#include <memory>
#include "base_vertex.h"
using namespace std;
namespace Grafz{
template<class T, class U>
class edge_data{

protected:
    bool m_visited;
    shared_ptr<U> m_edge;
    shared_ptr<U> m_previous;
public:
    edge_data(shared_ptr<U> edge){
        m_edge = edge;
        m_visited = false;
        m_previous = nullptr;
    }
    bool is_visited(){
        return m_visited;
    }
    void set_visited(bool visited){
        m_visited = visited;
    }

    shared_ptr<U> get_previous(){
        return m_previous;
    }

    void set_previous(shared_ptr<U> previous){
        m_previous = previous;
    }

    shared_ptr<U> get_edge(){
        return m_edge;
    }
};
}

#endif
