//
//  Util.h
//  PA1
//

#ifndef Util_h
#define Util_h

#include "Types.h"
#include <cmath>

using std::abs;

// Compares two floats
inline bool compareFloats(const FloatType a, const FloatType b, const FloatType eps=0.00001) {
    return abs(a - b) < eps;
}


#endif /* Util_h */
