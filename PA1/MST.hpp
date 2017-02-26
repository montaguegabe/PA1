#ifndef MST_hpp
#define MST_hpp

#include "Graph.hpp"
#include "Random.h"
#include<set>

std::set<SizeType>::iterator j;

// Helper function for Euclidean distances
float Euclid(Coordinate c1, Coordinate c2, unsigned int d) {
	FloatType sumSquareDifferences = 0;
	for (unsigned int i = 0; i < d; i++) {
		sumSquareDifferences += (c1[i] - c2[i]) * (c1[i] - c2[i]);
	}
	return sqrt(sumSquareDifferences);
}

float prim(const Graph g) {
	int n = g._n;
	unsigned int d = g._dimensions;
	float total = 0;
	vector<FloatType> dist = {};
	std::set<SizeType> notSeen;

	// Initialize distances to 0 for source and infinity for others
	// Put all nodes into the set notSeen
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			dist.push_back(0);
		}
		else {
			dist.push_back(std::numeric_limits<float>::infinity());
		}
		notSeen.insert(i);
	}

    // In 0 dimensions, randomly generate edge weights as we go
	if (d == 0) {

		// 0 is the default argument for seed
		if (g.myseed == 0) {

			// If a seed is left unspecified, set it to the system time
			unsigned int timeUI = static_cast<unsigned int>(time(NULL));
			srand(timeUI);

		}
		else {
			setSeed(seed);
		}


		for (int i = 0; i < n - 1; i++) {
			float min = std::numeric_limits<float>::infinity();
			int minindex = -1;
			for (j = notSeen.begin(); j != notSeen.end(); j++) {
				if (dist[*j] < min) {
					min = dist[*j];
					minindex = *j;
				}
			}
			notSeen.erase(minindex);
			for (int k = 0; k < n; k++) {
				float disttok = randomFloat(0.0f, 1.0f);
				if (dist[k] > disttok) {
					dist[k] = disttok;
				}
			}
			total += min;
		}
		return total
	}

	// In other dimensions, access the list of vertex coordinates to calculate weights as we go
	else {
		for (int i = 0; i < n - 1; i++) {
			float min = std::numeric_limits<float>::infinity();
			int minindex = -1;
			for (j = notSeen.begin(); j != notSeen.end(); j++) {
				if (dist[*j] < min) {
					min = dist[*j];
					minindex = *j;
				}
			}
			notSeen.erase(minindex);
			for (int k = 0; k < n; k++) {
				float disttok = Euclid(g._vertices[minindex], g._vertices[k], d);
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