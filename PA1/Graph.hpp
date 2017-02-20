//
//  Graph.hpp
//  PA1
//
//  Created by Gabe Montague on 2/19/17.
//  Copyright © 2017 Gabe Montague. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <array>
#include <cassert>

#include "Types.h"
#include "Util.h"

using std::array;
using std::vector;

typedef array<FloatType, 4> Coordinate;

class Graph {
public:
    Graph(const unsigned int n, const unsigned int dimensions, unsigned int seed=0);
    
    void print();
    void printVertices();
    
    static void test();

private:
    unsigned int _n;
    unsigned int _dimensions;
    
    vector<Coordinate> _vertices;
    vector<vector<FloatType> > _weights;
};


#endif /* Graph_hpp */
