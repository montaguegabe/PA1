//
//  FibHeap.cpp
//  PA1
//

#include "FibHeap.hpp"
#include <exception>
#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>

using std::logic_error;
using std::cout;
using std::vector;

#pragma mark - Node

void FibHeap::Node::print(const Node* start) const {
    
    // Base case: no more siblings
    if (this == start) {
        return;
    }
    
    // Print key and children
    cout << "(" << key << ",{";
    if (child != nullptr) {
        //child->print();
    }
    cout << "}),";
    
    // Print siblings
    next->print(start == nullptr ? this : start);
}

void FibHeap::Node::deleteSiblings() {
    
    // Delete siblings of the node
    Node* iteratedNode = next; // i.e. this->child
    
    while (iteratedNode != this) {
        
        if (iteratedNode == nullptr) {
            throw logic_error("Found null sibling in a tree while deleting! This should never happen.");
        }
        
        // Delete the children of a node before deleting the node
        Node* iteratedNodeAfter = iteratedNode->next;
        iteratedNode->deleteChildren();
        delete iteratedNode;
        iteratedNode = iteratedNodeAfter;
    }
    
    next = nullptr;
    prev = nullptr;
}

void FibHeap::Node::deleteChildren() {
    
    // Delete children of the node
    if (child != nullptr) {
        child->deleteSiblings();
        delete child;
        child = nullptr;
    }
}


#pragma mark - Fibonacci Heap

// Testing
void FibHeap::test() {
    
    FibHeap fh = FibHeap();
    fh.insert(21.0, {1, 100});
    fh.insert(48.2, {2, 200});
    fh.insert(21.0, {3, 300});
    fh.insert(54.0, {4, 400});
    fh.insert(96.0, {5, 500});
    fh.insert(0.05, {6, 600});
    fh.insert(3.14, {7, 700});
    fh.insert(134.0, {8, 800});
    
    fh.print();
    
    fh.popMin();
    fh.print();
}

// Destructor
FibHeap::~FibHeap() {
    
    if (_min != nullptr) {
        
        _min->deleteChildren();
        _min->deleteSiblings();
        delete _min;
        _min = nullptr;
    }
}

void FibHeap::insert(const KeyType key, const ValueType value) {
    
    Node* created = new Node();
    created->key = key;
    created->value = value;
    
    if (_min == nullptr) {
        
        // Create a new root list
        _min = created;
        created->next = created;
        created->prev = created;
        
    } else {
        
        // Insert into an existing root list
        created->next = _min->next;
        created->prev = _min;
        _min->next->prev = created;
        _min->next = created;
        
        // Check if we should change the min
        if (created->key < _min->key) {
            _min = created;
        }
    }
    
    // Increase the total number of elements
    _n += 1;
}

void FibHeap::combineWith(const FibHeap & other) {
    
    _n += other._n;
    
    // Combine the root linked lists
    Node* thisStart = _min;
    Node* thisEnd = _min->prev;
    Node* otherStart = other._min;
    Node* otherEnd = other._min->prev;
    
    thisEnd->next = otherStart;
    otherStart->prev = thisEnd;
    thisStart->prev = otherEnd;
    otherEnd->next = thisStart;
    
    // Update the minimum pointer
    if (_min == nullptr) {
        _min = other._min; // whether or not it is nullptr, other must be the min
    } else if (other._min != nullptr && other._min->key < _min->key) {
        _min = other._min;
    }
}

KVPair FibHeap::peekMin() const {
    return _min->getKV();
}

KVPair FibHeap::popMin() {
    
    if (_min == nullptr) {
        throw logic_error("Attempted to pop item from empty heap");
    }
    
    const KVPair result = _min->getKV();
    const bool isLastElement = _min == _min->next;
    
    // Handle case of one element
    if (isLastElement) {
        assert(_min->child == nullptr);
        delete _min;
        _min = nullptr;
    } else {
        
        // Add children of _min to the root list
        if (_min->child != nullptr) {
            Node* firstChild = _min->child;
            Node* lastChild = _min->child->prev;
            Node* insertionLower = _min;
            Node* insertionUpper = _min->next;
            
            insertionLower->next = firstChild;
            insertionUpper->prev = lastChild;
            firstChild->prev = insertionLower;
            lastChild->next = insertionUpper;
            
            // Iterate over added children and set parents to null
            firstChild->parent = nullptr;
            Node* iteratedNode = firstChild->next;
            while (iteratedNode != firstChild) {
                iteratedNode->parent = nullptr;
                iteratedNode = iteratedNode->next;
            }
        }
        
        // Now remove the old min from the root list, and set the new min to the first child added (temporarily).
        _min->prev->next = _min->next;
        _min->next->prev = _min->prev;
        _min = _min->next;
        delete _min;
        
        // Consolidate nodes
        _consolidate();
    }
    
    _n -= 1;
    
    return result;
}

void FibHeap::print() const {
    
    cout << "FibHeap of " << _n << "nodes:\n";
    _min->print();
    cout << "\n";
}

static const FloatType PHI = 1.61803;

// Subroutine for the pop method
void FibHeap::_consolidate() {
    
    // The non-inclusive upper bound of the degree of any tree
    const SizeType maxDegree = static_cast<SizeType>(floor(log(_n) / log(PHI))) + 1;
    
    // Allocate a vector with space maxDegree - all null.
    auto a = vector<Node*>(maxDegree, nullptr);
    
    // Iterate over the root list
    const Node* start = _min;
    Node* iteratedNode = _min;
    
    do {

        SizeType degree = iteratedNode->degree;
        
        // See if there is an existing tree we have already iterated over with matching degree
        while (a[degree] != nullptr) {
            
            // This will have the same degree as the iterated node
            Node* otherNode = a[degree]; // Called y in notes
            
            const bool iteratedIsSmaller = iteratedNode->key <= otherNode->key;
            Node* smaller = iteratedIsSmaller ? iteratedNode : otherNode;
            Node* larger = iteratedIsSmaller ? otherNode : iteratedNode;
            
            // Parent the smaller under the larger: first remove larger from the root list
            larger->prev->next = larger->next;
            larger->next->prev = larger->prev;
            
            // Now parent the larger under the smaller
            larger->parent = smaller;
            if (smaller->child == nullptr) {
                smaller->child = larger;
            } else {
                Node* sibling = smaller->child;
                larger->next = sibling;
                larger->prev = sibling->prev;
                sibling->prev->next = larger;
                sibling->prev = larger;
                smaller->child = larger;
            }
            smaller->degree++;
            
            a[degree] = nullptr;
            
            // Now set the while loop to search for trees of the new degree
            degree++;
        }
        
        // Record this tree in the array as having degree degree
        a[degree] = iteratedNode;
        iteratedNode = iteratedNode->next;
        
    } while (iteratedNode != start);
    
    _min = nullptr; // We are safe to do this because currently all nodes are stored in the degree array
    
    // Recalculate the min, and reform connections (necessary?)
    for (int i = 0; i < maxDegree; i++) {
        
        Node* node = a[i];
        
        // Skip null entries in the degree array
        if (node == nullptr) {
            continue;
        }
        
        // Create a new root list from a single node
        if (_min == nullptr) {
            node->parent = nullptr;
            node->next = node;
            node->prev = node;
            _min = node;
            
        // ...or grow the new root list if it's been made
        } else {
            
            // Insert node
            node->next = _min->next;
            node->prev = _min;
            _min->next->prev = node;
            _min->next = node;
            
            // Update the min if necessary
            if (node->key < _min->key) {
                _min = node;
            }
        }
    }
}


