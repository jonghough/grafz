#include <memory>
#include <functional>
#include <vector>

#include "spanningtreetest.h"
#include "../source/spanningtree.h"
#include "../source/base_vertex.h"
#include "../source/base_edge.h"
#include "../source/weighted_edge.h"
#include "../source/graph.h"
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
//using namespace std;
#include <iostream>



using namespace Grafz;
void spanningtreetest::runTest()
{

    vector<std::shared_ptr<base_vertex>> vs;
    vector<std::shared_ptr<weighted_edge<base_vertex>>> wes;

    shared_ptr<base_vertex> vert1 = std::make_shared<base_vertex>("v1");
    shared_ptr<base_vertex> vert2 = std::make_shared<base_vertex>("v2");
    shared_ptr<base_vertex> vert3 = std::make_shared<base_vertex>("v3");
    shared_ptr<base_vertex> vert4 = std::make_shared<base_vertex>("v4");
    shared_ptr<base_vertex> vert5 = std::make_shared<base_vertex>("v5");
    shared_ptr<base_vertex> vert6 = std::make_shared<base_vertex>("v6");
    shared_ptr<base_vertex> vert7 = std::make_shared<base_vertex>("v7");
    shared_ptr<base_vertex> vert8 = std::make_shared<base_vertex>("v8");

    vs.push_back(vert1);
    vs.push_back(vert2);
    vs.push_back(vert3);
    vs.push_back(vert4);
    vs.push_back(vert5);
    vs.push_back(vert6);
    vs.push_back(vert7);
    vs.push_back(vert8);

    shared_ptr<weighted_edge<base_vertex>> wedge1 = std::make_shared<weighted_edge<base_vertex>>(vert1, vert2, 2.0f);
    shared_ptr<weighted_edge<base_vertex>> wedge2 = std::make_shared<weighted_edge<base_vertex>>(vert1, vert3, 143.4f);
    shared_ptr<weighted_edge<base_vertex>> wedge3 = std::make_shared<weighted_edge<base_vertex>>(vert3, vert2, 260.4f);
    shared_ptr<weighted_edge<base_vertex>> wedge4 = std::make_shared<weighted_edge<base_vertex>>(vert4, vert2, 90.4f);
    shared_ptr<weighted_edge<base_vertex>> wedge5 = std::make_shared<weighted_edge<base_vertex>>(vert1, vert5, 55.76f);
    shared_ptr<weighted_edge<base_vertex>> wedge6 = std::make_shared<weighted_edge<base_vertex>>(vert2, vert6, 37.67f);
    shared_ptr<weighted_edge<base_vertex>> wedge7 = std::make_shared<weighted_edge<base_vertex>>(vert3, vert7, 60.44f);
    shared_ptr<weighted_edge<base_vertex>> wedge8 = std::make_shared<weighted_edge<base_vertex>>(vert2, vert7, 22.24f);
    shared_ptr<weighted_edge<base_vertex>> wedge9 = std::make_shared<weighted_edge<base_vertex>>(vert4, vert7, 11.24f);
    shared_ptr<weighted_edge<base_vertex>> wedge10 = std::make_shared<weighted_edge<base_vertex>>(vert5, vert8, 101.24f);
    shared_ptr<weighted_edge<base_vertex>> wedge11 = std::make_shared<weighted_edge<base_vertex>>(vert3, vert8, 41.24f);

    wes.push_back(wedge1);
    wes.push_back(wedge2);
    wes.push_back(wedge3);
    wes.push_back(wedge4);
    wes.push_back(wedge5);
    wes.push_back(wedge6);
    wes.push_back(wedge7);
    wes.push_back(wedge9);
    wes.push_back(wedge10);
    wes.push_back(wedge11);

    Graph<base_vertex, weighted_edge<base_vertex>> *h = new Graph<base_vertex, weighted_edge<base_vertex>>(vs, wes);

    auto spanningtree = Grafz::find_minimum_spanning_tree<>(*h);
    cout << "spanning tree size is: " << spanningtree.size() << endl;
    delete(h);
    CPPUNIT_ASSERT(spanningtree.size() == 7);
}

