//
//  Graph.cpp
//  PA1
//
//  Created by Gabe Montague on 2/19/17.
//  Copyright © 2017 Gabe Montague. All rights reserved.
//

#include "Random.h"
#include "Graph.hpp"

#include <iostream>
#include <cmath>
#include <ctime>

using std::cout;

// Constructor
Graph::Graph(const unsigned int n, const unsigned int dimensions, unsigned int seed) {
    
    // 0 is the default argument for seed
    if (seed == 0) {
        
        // If a seed is left unspecified, set it to the system time
        unsigned int timeUI = static_cast<unsigned int>(time(NULL));
        srand(timeUI);
        
    } else {
        setSeed(seed);
    }
    
    _n = n;
    _dimensions = dimensions;
    
    if (dimensions == 0) {
        
        // Fill in all weights randomly
        for (unsigned int row = 0; row < n; row++) {
            
            vector<FloatType> currentRow = {};
            
            for (unsigned int column = 0; column < row; column++) {
            
                // Generate a random number
                FloatType entry = randomFloat(0.0f, 1.0f);
                currentRow.push_back(entry);
                
            }
            
            _weights.push_back(currentRow);
        }
    } else {
            
        // Generate n points in dimension dimensions
        for (unsigned int i = 0; i < n; i++) {
            
            // Generate two random numbers
            Coordinate c = Coordinate();
            for (unsigned int d = 0; d < dimensions; d++) {
                c[d] = randomFloat(0.0f, 1.0f);
            }
            
            // Calculate distance to all other vertices
            for (unsigned int j = 0; j < i; j++) {
                
                Coordinate other = _vertices[j];
                
                FloatType sumSquareDifferences = 0;
                
                for (unsigned int d = 0; d < dimensions; d++) {
                    sumSquareDifferences += (c[d] - other[d]) * (c[d] - other[d]);
                }
                
                FloatType distance = sqrt(sumSquareDifferences);
                
                // Put the distance in the matrix
                // We are filling in the bottom left of the matrix
                _weights[i][j] = distance;
            }
                
            _vertices.push_back(c);
        }
    }
}

// Print
void Graph::print() {
    
    for (unsigned int row = 0; row < _n; row++) {
        for (unsigned int column = 0; column < row; column++) {
            
            cout << _weights[row][column] << ", ";
        }
        
        cout << "\n";
    }
}
