#include <memory>
#include <functional>
#include <vector>
#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "graphsearchtest.h"
#include "../source/graphsearch.h"
#include "../source/base_vertex.h"
#include "../source/base_edge.h"
#include "../source/weighted_edge.h"
#include "../source/graph.h"
#include "../source/directed_weighted_edge.h"
#include "../source/directed_edge.h"
#include "../source/edge_direction.h"


using namespace Grafz;
void graphsearchtest::runTest()
{
    shared_ptr<base_vertex> vert1 = std::make_shared<base_vertex>("v1");
    shared_ptr<base_vertex> vert2 = std::make_shared<base_vertex>("v2");
    shared_ptr<base_vertex> vert3 = std::make_shared<base_vertex>("v3");
    shared_ptr<base_vertex> vert4 = std::make_shared<base_vertex>("v4");

    vector<std::shared_ptr<base_vertex>> vs;
    vs.push_back(vert1);
    vs.push_back(vert2);
    vs.push_back(vert3);
    vs.push_back(vert4);

    shared_ptr<weighted_edge<base_vertex>> edge1 = std::make_shared<weighted_edge<base_vertex>>(vert1, vert2, 1.0f);
    shared_ptr<weighted_edge<base_vertex>> edge2 = std::make_shared<weighted_edge<base_vertex>>(vert1, vert3, 12.1f);
    shared_ptr<weighted_edge<base_vertex>> edge3 = std::make_shared<weighted_edge<base_vertex>>(vert3, vert2, 9.0f);
    shared_ptr<weighted_edge<base_vertex>> edge4 = std::make_shared<weighted_edge<base_vertex>>(vert3, vert4, 6.3f);

    vector<std::shared_ptr<weighted_edge<base_vertex>>> es;
    es.push_back(edge1);
    es.push_back(edge2);
    es.push_back(edge3);
    es.push_back(edge4);
    Graph<base_vertex, weighted_edge<base_vertex>> *g = new Graph<base_vertex, weighted_edge<base_vertex>>(vs, es);

    auto path2 = Grafz::find_min_path_with_dijkstra(*g, vert1, vert4);
    auto len = path2.size();
    delete(g);
    CPPUNIT_ASSERT(len == 4);

}


void graphsearchtest::runTest3()
{

    vector<std::shared_ptr<base_vertex>> vs;
    vector<std::shared_ptr<Grafz::directed_weighted_edge<base_vertex>>> wes;

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

    shared_ptr<directed_weighted_edge<base_vertex>> wedge1 = std::make_shared<directed_weighted_edge<base_vertex>>(vert1, vert2, 2.3f, Grafz::Edge_Direction::FORWARD);
    shared_ptr<directed_weighted_edge<base_vertex>> wedge2 = std::make_shared<directed_weighted_edge<base_vertex>>(vert2, vert3, 5.5f, Grafz::Edge_Direction::FORWARD);
    shared_ptr<directed_weighted_edge<base_vertex>> wedge3 = std::make_shared<directed_weighted_edge<base_vertex>>(vert3, vert4, 1.3f, Grafz::Edge_Direction::FORWARD);
    shared_ptr<directed_weighted_edge<base_vertex>> wedge4 = std::make_shared<directed_weighted_edge<base_vertex>>(vert4, vert5, 6.5f, Grafz::Edge_Direction::FORWARD);
    shared_ptr<directed_weighted_edge<base_vertex>> wedge5 = std::make_shared<directed_weighted_edge<base_vertex>>(vert5, vert6, 0.5f, Grafz::Edge_Direction::FORWARD);
    shared_ptr<directed_weighted_edge<base_vertex>> wedge6 = std::make_shared<directed_weighted_edge<base_vertex>>(vert6, vert7, 3.5f, Grafz::Edge_Direction::FORWARD);
    shared_ptr<directed_weighted_edge<base_vertex>> wedge7 = std::make_shared<directed_weighted_edge<base_vertex>>(vert7, vert8, 1.5f, Grafz::Edge_Direction::FORWARD);
    shared_ptr<directed_weighted_edge<base_vertex>> wedge8 = std::make_shared<directed_weighted_edge<base_vertex>>(vert8, vert1, 10.5f, Grafz::Edge_Direction::FORWARD);

    wes.push_back(wedge1);
    wes.push_back(wedge2);
    wes.push_back(wedge3);
    wes.push_back(wedge4);
    wes.push_back(wedge5);
    wes.push_back(wedge6);
    wes.push_back(wedge7);
    wes.push_back(wedge8);

    Graph<base_vertex, directed_weighted_edge<base_vertex>> *h = new Graph<base_vertex, directed_weighted_edge<base_vertex>>(vs, wes);

  
    auto path_bellman_ford = find_min_path_with_bellman_ford(*h, vert1, vert8);

    delete(h);
    CPPUNIT_ASSERT(path_bellman_ford.size() == 8);
}

void graphsearchtest::runTest2()
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
    shared_ptr<weighted_edge<base_vertex>> wedge3 = std::make_shared<weighted_edge<base_vertex>>(vert3, vert2, 60.4f);
    shared_ptr<weighted_edge<base_vertex>> wedge4 = std::make_shared<weighted_edge<base_vertex>>(vert4, vert2, 90.4f);
    shared_ptr<weighted_edge<base_vertex>> wedge5 = std::make_shared<weighted_edge<base_vertex>>(vert1, vert5, 30.4f);
    shared_ptr<weighted_edge<base_vertex>> wedge6 = std::make_shared<weighted_edge<base_vertex>>(vert2, vert6, 7.67f);
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

    function<float(shared_ptr<base_vertex>, shared_ptr<base_vertex>)>  lm = [](shared_ptr<base_vertex> vertex1, shared_ptr<base_vertex> vertex2) {
        return 400.0f;
    };

    auto path_astar = Grafz::find_min_path_with_astar(*h, vert1, vert8, lm);
    auto path_dijkstra = Grafz::find_min_path_with_dijkstra(*h, vert1, vert8);

    delete(h);
    CPPUNIT_ASSERT(path_astar.size() == 4);
    CPPUNIT_ASSERT(path_dijkstra.size() == 4);
}


