#ifndef DIRECTED_WEIGHTED_EDGE_H
#define DIRECTED_WEIGHTED_EDGE_H
#include "base_edge.h"
#include "weighted_edge.h"
#include "directed_edge.h"
#include "edge_direction.h"


namespace Grafz
{
template<class T>
class directed_weighted_edge : public weighted_edge<T>
{
public:
  
  directed_weighted_edge(std::shared_ptr<T> from, std::shared_ptr<T> to, float weight, Edge_Direction dir ) :
        weighted_edge<T>(from, to, weight), m_direction(dir) {
        //ctor
    }
    ~directed_weighted_edge() {
        //dtor
    }

    void set_direction(Edge_Direction dir){
      m_direction = dir;
    }
    
    Edge_Direction get_direction(){
	return m_direction;
    }
protected:
    //float m_weight;
    Edge_Direction m_direction;

};
}
#endif
