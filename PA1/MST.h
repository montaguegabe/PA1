#ifndef MST_hpp
#define MST_hpp

#include "Random.h"
#include <cmath>
#include <set>
#include <vector>

using std::vector;
using std::set;

// Helper function for distSquaredean distances
FloatType distSquared(Coordinate c1, Coordinate c2, unsigned int dimensions) {
	FloatType sumSquareDifferences = 0;
	for (unsigned int i = 0; i < dimensions; i++) {
		sumSquareDifferences += (c1[i] - c2[i]) * (c1[i] - c2[i]);
	}
	return sumSquareDifferences;
}

// Return total weight of MST of graph
FloatType prim(const SizeType n, unsigned int dimensions) {
    
    // Total weight of the MST
	FloatType total = 0;
    
    // The minimum distance from the seen set of vertices to each node
    vector<FloatType> dist = {};
    
    // Vertices that are not yet covered by the MST
	vector<bool> notSeen;

    // Initialize distances to 0 for source and infinity for others
    // Put all nodes into the set notSeen
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            dist.push_back(0);
        }
        else {
            dist.push_back(std::numeric_limits<FloatType>::max());
        }
		notSeen.push_back(true);
	}

    // In 0 dimensions, randomly generate edge weights as we go
	if (dimensions == 0) {

        // Add n - 1 edges
		for (int i = 0; i < n - 1; i++) {
            
            // Find the minimum edge/closest unseen vertex
            FloatType min = std::numeric_limits<FloatType>::max();
            SizeType minIndex = -1;
            for (SizeType j = 0; j < n; j++) {
                if (notSeen[j] == true && dist[j] < min) {
                    min = dist[j]; // Shortest edge length to not seen
                    minIndex = j; // Index of the closest node in not seen
                }
            }
            
            // Add the closest unseen vertex to seen
			notSeen[minIndex] = false;
            
            // Generate n new random edges from the added node.
            // If the generated edge provides a new shortest distance, add it to dist
			for (int k = 0; k < n; k++) {
				FloatType disttok = randomFloat(0.0f, 1.0f);
				if (dist[k] > disttok) {
					dist[k] = disttok;
				}
			}
            
            // Update total
			total += min;
		}
		return total;
	}

	// In other dimensions, access the list of vertex coordinates to calculate weights as we go
	else {
        
        // Generate coordinates for each vertex
        vector<Coordinate> vertexCoordinates;
        for (SizeType i = 0; i < n; i++) {
            
            Coordinate c = Coordinate();
            for (unsigned int d = 0; d < dimensions; d++) {
                c[d] = randomFloat(0.0f, 1.0f);
            }
            vertexCoordinates.push_back(c);
        }
        
        
        // Add n - 1 edges to MST
		for (int i = 0; i < n - 1; i++) {
            
            // Find the minimum edge/closest unseen vertex
            FloatType min = std::numeric_limits<FloatType>::max();
            SizeType minIndex = -1;
            for (SizeType j = 0; j < n; j++) {
                if (notSeen[j] == true && dist[j] < min) {
                    min = dist[j]; // Shortest edge length to not seen
                    minIndex = j; // Index of the closest node in not seen
                }
            }
            
            // Add the closest unseen vertex to seen
            notSeen[minIndex] = false;
            
            // Generate n new random edges from the added node.
            // If the generated edge provides a new shortest distance, add it to dist
			for (SizeType k = 0; k < n; k++) {
                if (notSeen[k]) {
                    FloatType disttok = distSquared(vertexCoordinates[minIndex], vertexCoordinates[k], dimensions);
                    if (dist[k] > disttok) {
                        dist[k] = disttok;
                    }
                }
			}

			total += sqrt(min);
		}
		return total;
	}
}


#endif
