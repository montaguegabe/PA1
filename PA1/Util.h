//
//  Util.h
//  PA1
//
//  Created by Gabe Montague on 2/19/17.
//  Copyright © 2017 Gabe Montague. All rights reserved.
//

#ifndef Util_h
#define Util_h

#include "Types.h"
#include <cmath>

using std::abs;

// Compares two floats
inline bool compareFloats(FloatType a, FloatType b, FloatType eps=0.00001) {
    return abs(a - b) < eps;
}


#endif /* Util_h */
