//
//  Random.h
//  PA1
//
//  Created by Gabe Montague on 2/19/17.
//  Copyright © 2017 Gabe Montague. All rights reserved.
//

#ifndef Random_h
#define Random_h

#include <cstdlib>
#include "Types.h"

// Returns a random float between a and b
FloatType randomFloat(FloatType a, FloatType b) {
    
    FloatType random = ((FloatType) rand()) / (FloatType) RAND_MAX;
    FloatType diff = b - a;
    FloatType r = random * diff;
    return a + r;
}

void setSeed(unsigned int seed) {
    srand (seed);
}

#endif /* Random_h */
