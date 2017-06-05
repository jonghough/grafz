#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "cppunit/TestCase.h"
#include "cppunit/TestSuite.h"
#include "cppunit/TestCaller.h"
#include "cppunit/TestRunner.h"
class graphsearchtest : public CppUnit::TestCase { 
public: 
  graphsearchtest( std::string name ) : CppUnit::TestCase( name ) {}
  
  void runTest();
  void runTest2();
  void runTest3();
};