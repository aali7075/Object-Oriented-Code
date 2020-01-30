# This is an example make file

CXX = g++  # the compiler
CXXFLAGS = -std=c++17 -Wall  # flags for the compiler (use c++17 standards, turn on all optional warnings); add -ggdb if you want to use gdb to debug!

# runs for "make all"
all: pe3_references # Should only be the excutables you want to run

pe3_references: pe3_references.o
	$(CXX) $(CXXFLAGS) -o pe3_references pe3_references.o

pe3_references.o: pe3_references.cpp
	$(CXX) $(CXXFLAGS) -c pe3_references.cpp

# note that lines below targets must be
# TABBED in (not spaces!)
clean:
	rm pe3_references pe3_references.o
