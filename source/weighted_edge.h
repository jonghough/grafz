#ifndef WEIGHTED_EDGE_H
#define WEIGHTED_EDGE_H
#include <memory>
#include "base_edge.h"

namespace Grafz{
template<class T>
class weighted_edge : public base_edge<T>
{
public:

    weighted_edge(std::shared_ptr<T> from, std::shared_ptr<T> to, float weight) :
        base_edge<T>(from, to), m_weight(weight) {
        //ctor
    }
    ~weighted_edge() {
        //dtor
    }

    float get_weight() {
        return m_weight;
    }

protected:
    float m_weight;


};
}
#endif // WEIGHTED_EDGE_H
