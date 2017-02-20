//
//  Types.h
//  PA1
//

#ifndef Types_h
#define Types_h

#include <array>

using std::array;

// Types used by Graph class
typedef double FloatType;
typedef unsigned int SizeType; // Used to index the graph matrix
typedef array<SizeType, 2> EdgeType; // Edges connect two vertex indices

// Types used by FibHeap class
typedef FloatType HeapKeyType;
typedef EdgeType HeapValueType;


#endif /* Types_h */
