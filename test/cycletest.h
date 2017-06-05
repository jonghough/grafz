#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "cppunit/TestCase.h"
#include "cppunit/TestSuite.h"
#include "cppunit/TestCaller.h"
#include "cppunit/TestRunner.h"

#include "base_vertex.h"

class cycletest : public CppUnit::TestCase { 
public: 
  cycletest( std::string name ) : CppUnit::TestCase( name ) {}
  
  void runTest1();
  void runTest2();
  void runTest3();
  void runTest4();
  template <class base_vertex>
    static base_vertex cloneme(base_vertex& t){
        base_vertex bv(t.get_label());
        return bv;
    };
};
