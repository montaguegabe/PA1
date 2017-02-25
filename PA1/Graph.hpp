//
//  Graph.hpp
//  PA1
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <array>
#include <cassert>

#include "Types.h"

using std::array;
using std::vector;

typedef array<FloatType, 4> Coordinate;

class Graph {
public:
    Graph(const SizeType n, const unsigned int dimensions, unsigned int seed=0);
    
    void print() const;
    void printVertices() const;
    
    static void test();
	SizeType _n;
	vector<vector<FloatType> > _weights;


private:
    
    unsigned int _dimensions;
    
    vector<Coordinate> _vertices;
};


#endif /* Graph_hpp */
