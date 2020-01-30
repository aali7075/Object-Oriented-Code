# This is an example make file

CXX = g++  # the compiler
CXXFLAGS = -std=c++17 -Wall  # flags for the compiler (use c++17 standards, turn on all optional warnings); add -ggdb if you want to use gdb to debug!

# runs for "make all"
all: main # Should only be the excutables you want to run

main: main.o Point.o
	$(CXX) $(CXXFLAGS) -o main main.o Point.o
    
main.o: main.cpp Point.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# note that lines below targets must be
# TABBED in (not spaces!)
clean:
	rm main main.o Point.o

Point.o: Point.cpp
	$(CXX) $(CXXFLAGS) Point.cpp -c #Will produce point.o
