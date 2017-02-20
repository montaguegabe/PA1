//
//  FibHeap.hpp
//  PA1
//

#ifndef FibHeap_hpp
#define FibHeap_hpp

#include "Types.h"
#include <array>

using std::array;

// Rather than using a template we are going to just use these two typedefs
typedef HeapKeyType KeyType;
typedef HeapValueType ValueType; // The values contain edges

// Define a type for a key-value pair
struct KVPair {
    KeyType key;
    ValueType value;
};

class FibHeap {
public:
    FibHeap() {}
    
    // Adds a new value to the heap
    void insert(const KeyType key, ValueType && value);
    
    // Peeks at the new value
    KVPair peekMin() const;
    
    // Pops the value from the heap, removing and returning it
    KVPair popMin();
};

class Node {
    
    // ...
};

#endif /* FibHeap_hpp */
