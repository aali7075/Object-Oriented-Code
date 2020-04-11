CXX = g++
CXXTESTFLAGS = --coverage #for unit testing
CXXFLAGS = -std=c++17 -Wall

all: main test

clean:
	rm main test

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main


test: test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -o test
