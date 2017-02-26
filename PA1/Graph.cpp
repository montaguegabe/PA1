//
//  Graph.cpp
//  PA1
//

#include "Random.h"
#include "Graph.hpp"
#include "Util.h"

#include <iostream>
#include <cmath>
#include <ctime>

using std::cout;

// Constructor
Graph::Graph(const SizeType n, const unsigned int dimensions, unsigned int seed) {   
	myseed = seed;
    _n = n;
    _dimensions = dimensions;
    /*
    if (dimensions == 0) {
        
        // Fill in all weights randomly
        for (SizeType row = 0; row < n; row++) {
            
            vector<FloatType> currentRow = {};
            
            for (SizeType column = 0; column < row; column++) {
            
                // Generate a random number
                FloatType entry = randomFloat(0.0f, 1.0f);
                currentRow.push_back(entry);
                
            }
            
            _weights.push_back(currentRow);
        }
		for (SizeType row = 0; row < n; row++) {
			for (SizeType column = row; column < n; column++) {
				if (column == row) {
					_weights[row].push_back(0);
				}
				else {
					_weights[row].push_back(_weights[column][row]);
				}
			}
		}
    } 
	*/
	if (dimensions != 0) {
            
        // Generate n points in dimension dimensions
        for (SizeType i = 0; i < n; i++) {
            /*
            vector<FloatType> currentRow = {};
			*/
            
            Coordinate c = Coordinate();
            for (unsigned int d = 0; d < dimensions; d++) {
                c[d] = randomFloat(0.0f, 1.0f);
            }
            /*
            // Calculate distance to all other vertices
            for (SizeType j = 0; j < i; j++) {
                
                Coordinate other = _vertices[j];
                
                FloatType sumSquareDifferences = 0;
                
                for (unsigned int d = 0; d < dimensions; d++) {
                    sumSquareDifferences += (c[d] - other[d]) * (c[d] - other[d]);
                }
                
                FloatType distance = sqrt(sumSquareDifferences);
                
                // Put the distance in the matrix
                // We are filling in the bottom left of the matrix
                currentRow.push_back(distance);
            }
            
            _weights.push_back(currentRow);
			*/
            _vertices.push_back(c);
        }
    }
}

// Print
/*
void Graph::print() const {
    
    for (SizeType row = 0; row < _n; row++) {
        for (SizeType column = 0; column < _n; column++) {
            
            cout << _weights[row][column] << ", ";
        }
        cout << "\n";
    }
}
*/

void Graph::printVertices() const {
    
    for (SizeType i = 0; i < _n; i++) {
        cout << "[";
        for (unsigned int d = 0; d < _dimensions; d++) {
            cout << _vertices[i][d] << ",";
        }
        cout << "]\n";
    }
}

// Testing
void Graph::test() {
    
    // Make a graph
    auto g1 = Graph(5, 0, 1487555058);
	g1.print();
	/*
    assert(compareFloats(g1._weights[1][0], 0.155178));
    assert(compareFloats(g1._weights[4][3], 0.0334458));
    */
    auto g2 = Graph(5, 2, 1487555058);
	/*
    assert(compareFloats(g2._vertices[3][1], 0.275206));*/
}
