CXX = g++
CXXFLAGS = -O2 -Wall -D_GLIBCXX_DEBUG -ftrapv
INCLUDES = ./

disjoint_set/union_find/a.out: header.h disjoint_set/union_find/src.cpp disjoint_set/union_find/test.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -o disjoint_set/union_find/a.out disjoint_set/union_find/test.cpp
union_find_test: disjoint_set/union_find/a.out
	./disjoint_set/union_find/a.out
