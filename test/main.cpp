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


    graphsearchtest test("1");
    test.runTest();
    test.runTest2();
    test.runTest3();

    spanningtreetest spt("spt");
    spt.runTest();

    
    cycletest ct("ct");
    ct.runTest1();
    ct.runTest2();
    ct.runTest3();
    ct.runTest4();
    return 0;
}


