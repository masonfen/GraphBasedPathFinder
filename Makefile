CXX = g++

all: sixdegrees

sixdegrees: sixdegrees.o main.o
	$(CXX) $(CXXFLAGS) -o sixdegrees sixdegrees.o main.o

sixdegrees.o: sixdegrees.cpp sixdegrees.h
	$(CXX) $(CXXFLAGS) -c sixdegrees.cpp

main.o: main.cpp sixdegrees.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o sixdegrees
