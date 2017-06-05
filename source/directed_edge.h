#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H
#include "base_edge.h"
#include "edge_direction.h"


namespace Grafz
{

template<class T>
class directed_edge : public base_edge<T>
{

public:
    directed_edge(std::shared_ptr<T>from , std::shared_ptr<T> to, Edge_Direction direction): base_edge<T>(from, to), m_direction(direction)
    {}

    Edge_Direction get_direction() {
        return m_direction;
    }

    void change_direction(Edge_Direction direction) {
        m_direction = direction;
    }
protected:
    Edge_Direction m_direction;

};
}
#endif // DIRECTED_EDGE_H
