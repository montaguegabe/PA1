//
//  Random.h
//  PA1
//

#ifndef Random_h
#define Random_h

#include <cstdlib>
#include "Types.h"

// Returns a random float between a and b
FloatType randomFloat(const FloatType a, const FloatType b) {
    
    FloatType random = static_cast<FloatType>(rand()) / static_cast<FloatType>(RAND_MAX);
    FloatType diff = b - a;
    FloatType r = random * diff;
    return a + r;
}

// Seeds the random number generator
void setSeed(unsigned int seed) {
    srand(seed);
}

#endif /* Random_h */
