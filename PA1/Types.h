//
//  Types.h
//  PA1
//

#ifndef Types_h
#define Types_h

#include <array>

using std::array;

// Type used for real numbers
typedef float FloatType;

// Tuples of real numbers
typedef array<FloatType, 4> Coordinate;

// Used to index the graph matrix
typedef unsigned int SizeType;

// Types used by FibHeap class
typedef FloatType HeapKeyType;
typedef SizeType HeapValueType;


#endif /* Types_h */
