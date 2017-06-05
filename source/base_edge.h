#ifndef BASE_EDGE_H
#define BASE_EDGE_H
#include "base_vertex.h"
#include <memory>


namespace Grafz{
/**
 * Base edge class. An edge of any graph, G<V,E>, needs to
 * extend this class.
 */
template<class T>
class base_edge
{
protected:

    std::shared_ptr<T> m_from;
    std::shared_ptr<T> m_to;
    bool m_visited;
public:
    base_edge(std::shared_ptr<T> from , std::shared_ptr<T> to):  m_to(to), m_from(from)
    {
    }

    /**
     * @brief from
     * Gets the FROM vertex.
     * @return FROM vertex
     */
    std::shared_ptr<T> from() const
    {
        return m_from;
    }

    /**
     * @brief to
     * Gets the TO vertex
     * @return TO vertex
     */
    std::shared_ptr<T> to() const
    {
        return m_to;
    }
};
}
#endif // BASE_EDGE_H
