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

// Used to index the graph matrix
typedef unsigned int SizeType;

// Edges connect two vertex indices
typedef array<SizeType, 2> Edge;

// Types used by FibHeap class
typedef FloatType HeapKeyType;
typedef Edge HeapValueType;


#endif /* Types_h */
