#ifndef MST_hpp
#define MST_hpp

#include "Graph.hpp"
#include<set>
std::set<SizeType>::iterator j;

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
	if (d == 0) {
		return 0;
	}
	else {
		float total = 0;
		vector<FloatType> dist = {};
		std::set<SizeType> notSeen;
		for (int i = 0; i < n; i++) {
			if (i == 0) {
				dist.push_back(0);
			}
			else {
				dist.push_back(std::numeric_limits<float>::infinity());
			}
			notSeen.insert(i);
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
				float disttok = Euclid(g._vertices[minindex], g._vertices[k], d);
				if (dist[k] > disttok) {
					dist[k] = disttok;
				}
			}

			total += min;

			/*
			for element in notSeen
			if dist(elment) is minimal
			remove element from notseen
			update dist with new connections
			add the edge to total
			*/
		}
		return total;
	}
}


#endif