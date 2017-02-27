//
//  main.cpp
//  PA1
//

#include <iostream>

#include "FibHeap.hpp"
#include "MST.hpp"
#include "Types.h"
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::stoul;

int main(int argc, const char * argv[]) {
    
    const bool exhaustive = static_cast<string>(argv[1]) == "1";
    
    // Check command line arguments
    if (argc != 5 && !(argc == 2 && exhaustive)) {
        
        cout << "Error: Please provide input in the form of " << argv[0] << " 0 numpoints numtrials dimension" << endl;
        return 0;
    }
    
    // Run exhaustive testing if specified with first argument
    if (exhaustive) {
    
        // Test on different dimensions
        unsigned int dims[4] = {0, 2, 3, 4};
        
        // Test on different sizes of graphs
        int nums[11] = { 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072 };
        
        for (const auto & dim : dims) {
            for (const auto & num : nums) {
                
                if (dim == 0) {
                    continue;
                }
                if (dim == 2 && num <= 65536) {
                    continue;
                }
                
                FloatType total = 0;
                const unsigned int trials = 5;
                for (int i = 0; i < trials; i++) {
                    
                    // Reseed with system time
                    unsigned int seed = static_cast<unsigned int>(time(NULL));
                    setSeed(seed);
                    
                    // Run prim's algorithm
                    total += prim(num, dim);
                }
                
                // Output results
                const FloatType avg = total / trials;
                cout << avg << " " << num << " " << trials << " " << dim << endl;
            }
        }
        
    // Otherwise run according to command line parameters
    } else {
        
        // Get command line input
        const SizeType points = static_cast<unsigned int>(stoul(argv[2]));
        const unsigned int trials = static_cast<unsigned int>(stoul(argv[3]));
        const unsigned int dimension = static_cast<unsigned int>(stoul(argv[4]));
        
        // Reseed with system time
        unsigned int seed = static_cast<unsigned int>(time(NULL));
        setSeed(seed);
        
        FloatType total = 0;
        for (int i = 0; i < trials; i++) {
            
            // Reseed with system time
            unsigned int seed = static_cast<unsigned int>(time(NULL));
            setSeed(seed);
            
            // Run algorithm
            total += prim(points, dimension);
        }
        const FloatType avg = total / trials;
        cout << avg << " " << points << " " << trials << " " << dimension << endl;
        
    }
    return 0;
}


