#ifndef MST_hpp
#define MST_hpp

#include "Random.h"
#include <cmath>
#include <set>
#include <vector>

using std::vector;
using std::set;

// Helper function for euclidean distances
FloatType euclid(Coordinate c1, Coordinate c2, unsigned int dimensions) {
	FloatType sumSquareDifferences = 0;
	for (unsigned int i = 0; i < dimensions; i++) {
		sumSquareDifferences += (c1[i] - c2[i]) * (c1[i] - c2[i]);
	}
	return sqrt(sumSquareDifferences);
}

// Return total weight of MST of graph
FloatType prim(SizeType n, unsigned int dimensions) {
    
    // Total weight of the MST
	FloatType total = 0;
    
    // The minimum distance from the seen set of vertices to each node
	vector<FloatType> dist = {};
    
    // Vertices that are not yet covered by the MST
	set<SizeType> notSeen;

	// Initialize distances to 0 for source and std::numeric_limits<FloatType>::infinity() for others
	// Put all nodes into the set notSeen
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			dist.push_back(0);
		}
		else {
			dist.push_back(std::numeric_limits<FloatType>::infinity());
		}
		notSeen.insert(i);
	}

    // In 0 dimensions, randomly generate edge weights as we go
	if (dimensions == 0) {

        // Add n - 1 edges
		for (int i = 0; i < n - 1; i++) {
            
            // Find the minimum edge/closest unseen vertex - TODO replace with heap
			FloatType min = std::numeric_limits<FloatType>::infinity();
			int minIndex = -1;
            set<SizeType>::iterator j;
			for (j = notSeen.begin(); j != notSeen.end(); j++) {
				if (dist[*j] < min) {
					min = dist[*j]; // Shortest edge length to not seen
					minIndex = *j; // Index of the closest node in not seen
				}
			}
            
            // Add the closest unseen vertex to seen
			notSeen.erase(minIndex);
            
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
            
            // Find the minimum edge - TODO replace with heap
            FloatType min = std::numeric_limits<FloatType>::infinity();
			int minIndex = -1;
            set<SizeType>::iterator j;
			for (j = notSeen.begin(); j != notSeen.end(); j++) {
				if (dist[*j] < min) {
					min = dist[*j];
					minIndex = *j;
				}
			}
            
            // Add the closest unseen vertex to seen
			notSeen.erase(minIndex);
            
            // Generate n new random edges from the added node.
            // If the generated edge provides a new shortest distance, add it to dist
			for (int k = 0; k < n; k++) {
				FloatType disttok = euclid(vertexCoordinates[minIndex], vertexCoordinates[k], dimensions);
				if (dist[k] > disttok) {
					dist[k] = disttok;
				}
			}

			total += min;
		}
		return total;
	}
}


#endif
