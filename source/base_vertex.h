#ifndef BASE_VERTEX_H
#define BASE_VERTEX_H
#include <string>
#include <vector>
#include <memory>
using std::string;
namespace Grafz{
class base_vertex
{
protected:
    string m_label;
public:
    
base_vertex(const string& label)
{
    m_label = label;
}

string get_label() const
{
    return m_label;
}

void set_label(const string& label)
{
    m_label = label;
}


};
}
#endif // BASE_VERTEX_H
