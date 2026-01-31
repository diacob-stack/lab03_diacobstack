CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

all: testbst

testbst: intbst.o testbst.o
	$(CXX) $(CXXFLAGS) intbst.o testbst.o -o testbst

intbst.o: intbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c intbst.cpp

testbst.o: testbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c testbst.cpp

clean:
	rm -f *.o testbst
