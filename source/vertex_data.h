#ifndef VERTEX_DATA
#define VERTEX_DATA
#include <vector>
#include <memory>
using namespace std;

template<class T>
class vertex_data{

protected:
    bool m_visited;
    float m_distance;
    shared_ptr<T> m_previous;
public:
    vertex_data(float distance):m_distance(distance),m_visited(false){
        m_previous = nullptr;
    }
    bool is_visited(){
        return m_visited;
    }
    void set_visited(bool visited){
        m_visited = visited;
    }
    void set_distance(float distance){
        m_distance = distance;
    }
    float get_distance(){
        return m_distance;
    }

    shared_ptr<T> get_previous(){
        return m_previous;
    }

    void set_previous(shared_ptr<T> previous){
        m_previous = previous;
    }
};


#endif
