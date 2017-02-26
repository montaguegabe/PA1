//
//  main.cpp
//  PA1
//

#include <iostream>

#include "Graph.hpp"
#include "FibHeap.hpp"
#include "MST.hpp"

int main(int argc, const char * argv[]) {
    
	Graph g1 = Graph(131072, 3);
	std::cout << prim(g1) << std::endl;
	int dims[3] = { 0, 2, 3, 4 };
	int nums[11] = { 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072 };
	for (const auto& dim : dims) {
		for (const auto& num : nums) {
			float total = 0;
			for (int i = 0; i < 5; i++) {
				total += prim(Graph(num, dim));
			}
			std::cout << dim << ", " << num << ", " << total / 5 << std::endl;
		}
	}
    return 0;
}


