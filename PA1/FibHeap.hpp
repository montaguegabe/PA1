//
//  FibHeap.hpp
//  PA1
//

// Note: All heap values currently passed by value.

#ifndef FibHeap_hpp
#define FibHeap_hpp

#include "Types.h"
#include <array>
#include <iostream>

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
    void insert(const KeyType key, const ValueType value);
    
    // Adds another Fibonacci heap to the current one
    void combineWith(const FibHeap & other);
    
    // Peeks at the new value
    KVPair peekMin() const;
    
    // Pops the value from the heap, removing and returning it
    KVPair popMin();
    
    // Run tests
    static void test();
    
    // Print
    void print() const;
    
    // Destructor
    virtual ~FibHeap();
    
private:

    // Number of elements
    KeyType _n = 0;
    
    class Node {
    public:
        KeyType key;
        ValueType value;
        SizeType degree = 0;
        
        Node* next = nullptr;
        Node* prev = nullptr;
        Node* parent = nullptr;
        Node* child = nullptr;
        
        KVPair getKV() const {
            KVPair kv;
            kv.key = key;
            kv.value = value;
            return kv;
        }
        
        void print(const Node* start=nullptr) const;
        void deleteChildren();
        void deleteSiblings();
    };
    
    // Pointer to the minimum element. Don't throw away the value or you leak the entire heap.
    Node* _min = nullptr;
    
    void _consolidate();
};

#endif /* FibHeap_hpp */
