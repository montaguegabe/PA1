//
//  main.cpp
//  PA1
//

#include <iostream>

#include "Graph.hpp"
#include "FibHeap.hpp"
#include "MST.hpp"

int main(int argc, const char * argv[]) {
    
    Graph::test();
    FibHeap::test();
	Graph g1 = Graph(50000, 4);
	std::cout << prim(g1) << std::endl;
    return 0;
}


