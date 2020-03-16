CXX = g++
CXXFLAGS	= -std=c++17 -Wall

all: main

clean:
	rm main District.o ElectoralMap.o Election.o TextUI.o

main: main.cpp District.o ElectoralMap.o Election.o TextUI.o
	$(CXX) $(CXXFLAGS) main.cpp District.o ElectoralMap.o Election.o TextUI.o -o main

District.o: District.cpp
	$(CXX) $(CXXFLAGS) -c District.cpp

ElectoralMap.o: ElectoralMap.cpp
	$(CXX) $(CXXFLAGS) -c ElectoralMap.cpp

Election.o: Election.cpp
	$(CXX) $(CXXFLAGS) -c Election.cpp

TextUI.o: TextUI.cpp
	$(CXX) $(CXXFLAGS) -c TextUI.cpp
