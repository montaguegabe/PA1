//
//  main.cpp
//  PA1
//

#include <iostream>

#include "FibHeap.hpp"
#include "MST.hpp"
#include "Types.h"

int main(int argc, const char * argv[]) {
    
	unsigned int dims[4] = { 0, 2, 3, 4 };
	int nums[11] = { 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072 };
	for (const auto& dim : dims) {
		for (const auto& num : nums) {
            
			FloatType total = 0;
			for (int i = 0; i < 5; i++) {
                
                // Reseed with system time
                unsigned int seed = static_cast<unsigned int>(time(NULL));
                setSeed(seed);
                
				total += prim(num,  dim);
			}
			std::cout << dim << ", " << num << ", " << total / 5 << std::endl;
		}
	}
    return 0;
}


