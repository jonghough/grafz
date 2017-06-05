#Makefile
# Creates test executable and runs the tests.
CXX = g++ -std=c++11 -g
LDLIBS = -lcppunit
OBJS = ../objects/*
OUT = ../bin/Test
INC_PATH = -I ../source/ 
CPPFILES = *.cpp

all:  clean $(OUT) run

clean: 
	rm -f $(OUT)
	echo Clean done
	
$(OUT): $(OUT)
	$(CXX) -o $@ $^ $(CPPFILES) $(INC_PATH)  $(LDLIBS) # -L../bin/libgrafz.so



run: $(OUT)
	./$(OUT)
