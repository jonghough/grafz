#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "graphsearchtest.h"
#include "spanningtreetest.h"
#include "cycletest.h"


using namespace Grafz;
int main()
{


    auto test = new graphsearchtest("1");
    test->runTest();
    test->runTest2();
    test->runTest3();

    auto spt = new spanningtreetest("spt");
    spt->runTest();

    
    auto ct = new cycletest("ct");
    ct->runTest1();
    ct->runTest2();
    ct->runTest3();
    ct->runTest4();
    return 0;
}


