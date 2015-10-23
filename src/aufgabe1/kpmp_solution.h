#ifndef INSTANCE_SOLUTION_H_
#define INSTANCE_SOLUTION_H_

#include <vector>
#include <tuple>
#include <unordered_map>

typedef unsigned int uint;

struct Edge {
	uint v1; // vertex number with ordering
	uint v2; // vertex number with ordering
	uint page;
};

class KPMPSolution {
    private:
    	uint k;
		uint numVertices;
		std::vector<uint> vertexToPosition;
		std::vector<uint> positionToVertex;
		std::unordered_map<uint, std::vector<Edge>> pageToEdges;

		void normalizeEdge(Edge& e);

    public:
		KPMPSolution(uint k, uint numVertices);
        
		std::vector<Edge> getEdgesFromPage(uint p);
		void addEdge(Edge e, bool orderingIncluded = true);
		void removeEdge(Edge e, bool orderingIncluded = true);
		void setOrdering(std::vector<uint> ordering);

		uint computeCrossings(); 
};

#endif /* INSTANCE_SOLUTION_H_ */
