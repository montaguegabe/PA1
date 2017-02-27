//
//  main.cpp
//  PA1
//

#include <iostream>

#include "MST.h"
#include "Types.h"
#include <string>
#include <vector>
#include <ctime>
#include <time.h>

using std::cout;
using std::endl;
using std::string;
using std::stoul;
using std::clock_t;
using std::clock;

int main(int argc, const char * argv[]) {
    
    // Check command line arguments
    if (argc != 5 && !(argc == 2 && static_cast<string>(argv[1]) == "1")) {
        
        cout << "Error: Please provide input in the form of " << argv[0] << " 0 numpoints numtrials dimension" << endl;
        return 0;
    }

    const bool exhaustive = static_cast<string>(argv[1]) == "1";
    
    // Run exhaustive testing if specified with first argument
    if (exhaustive) {
    
        // Test on different dimensions
        vector<unsigned int> dims = {0, 2, 3, 4};
        
        // Test on different sizes of graphs
        vector<SizeType> nums = { 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072 /*, 262144*/ };
        
        for (const auto & dim : dims) {
            for (const auto & num : nums) {
                
                FloatType total = 0;
                const unsigned int trials = 5;
                for (int i = 0; i < trials; i++) {
                    
                    // Reseed with system time
                    unsigned int seed = static_cast<unsigned int>(time(NULL));
                    setSeed(seed);
                    
                    // Run prim's algorithm and time it
                    clock_t begin = clock();
                    total += prim(num, dim);
                    clock_t end = clock();
                    double elapsed = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
                    cout << elapsed << endl;
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


