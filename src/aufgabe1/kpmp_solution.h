#ifndef INSTANCE_SOLUTION_H_
#define INSTANCE_SOLUTION_H_

#include <vector>
#include <tuple>
#include <unordered_map>
#include <algorithm>

typedef unsigned int uint;

struct Edge {
	uint v1; // vertex number with ordering
	uint v2; // vertex number with ordering
	uint page;
};

class KPMPSolution {
    public:
		KPMPSolution(uint k, uint numVertices);
        
		std::vector<Edge> getEdgesFromPage(uint p);
		// the edge must not be in the graph yet! this is not checked!
		void addEdge(Edge e, bool orderingIncluded = true);
		// the edge must be in the graph yet! this is not checked!
		void removeEdge(Edge e, bool orderingIncluded = true);
		void setOrdering(std::vector<uint> ordering);

		uint getCrossings(); 
		std::vector<uint> getOrdering();
		uint getK();

	private:
		uint k;
		uint numVertices;
		uint crossings;

		std::vector<uint> vertexToPosition;
		std::vector<uint> positionToVertex;
		std::unordered_map<uint, std::vector<Edge>> pageToEdges;

		void normalizeEdge(Edge& e);

		bool isCrossing(Edge& e1, Edge &e2);
		uint computeEdgeCrossings(Edge &e);
		void recomputeCrossings();
};

#endif /* INSTANCE_SOLUTION_H_ */
