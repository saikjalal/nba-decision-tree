CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: decision_tree_E_18_19 decision_tree_W_18_19 decision_tree_E_17_18 decision_tree_W_17_18

decision_tree_E_18_19: decision_tree_E_18_19.o
	$(CXX) $(CXXFLAGS) -o decision_tree_E_18_19 decision_tree_E_18_19.o

decision_tree_W_18_19: decision_tree_W_18_19.o
	$(CXX) $(CXXFLAGS) -o decision_tree_W_18_19 decision_tree_W_18_19.o

decision_tree_E_17_18: decision_tree_E_17_18.o
	$(CXX) $(CXXFLAGS) -o decision_tree_E_17_18 decision_tree_E_17_18.o

decision_tree_W_17_18: decision_tree_W_17_18.o
	$(CXX) $(CXXFLAGS) -o decision_tree_W_17_18 decision_tree_W_17_18.o

decision_tree_E_18_19.o: decision_tree_E_18_19.cpp
	$(CXX) $(CXXFLAGS) -c decision_tree_E_18_19.cpp

decision_tree_W_18_19.o: decision_tree_W_18_19.cpp
	$(CXX) $(CXXFLAGS) -c decision_tree_W_18_19.cpp

decision_tree_E_17_18.o: decision_tree_E_17_18.cpp
	$(CXX) $(CXXFLAGS) -c decision_tree_E_17_18.cpp

decision_tree_W_17_18.o: decision_tree_W_17_18.cpp
	$(CXX) $(CXXFLAGS) -c decision_tree_W_17_18.cpp

clean:
	rm -f *.o decision_tree_E_18_19 decision_tree_W_18_19 decision_tree_E_17_18 decision_tree_W_17_18