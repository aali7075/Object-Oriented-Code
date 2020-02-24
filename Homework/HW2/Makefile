CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: main

clean:
	rm test main

# Counter.o: Counter.hpp
# 	$(CXX) $(CXXFLAGS) -c Counter.hpp

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main


# test: Counter.o test.cpp
# 	$(CXX) $(CXXFLAGS) test.cpp Counter.o -o test
#
# cov: Rectangle.o test.cpp
# 	$(CXX) $(CXXFLAGS) $(CXXTESTFLAGS) test.cpp Counter.o -o test
