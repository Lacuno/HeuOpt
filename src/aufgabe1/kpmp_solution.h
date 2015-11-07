#ifndef INSTANCE_SOLUTION_H_
#define INSTANCE_SOLUTION_H_

#include <vector>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <memory>

typedef unsigned int uint;
typedef std::vector<std::vector<bool>> AdjacencyMatrix;
typedef std::vector<std::vector<std::reference_wrapper<uint>>> AdjacencyList;

struct Edge {
	uint v1;
	uint v2;
	uint page;
};

class KPMPSolution {
    public:
		KPMPSolution(uint k, uint numVertices);
		KPMPSolution(std::shared_ptr<KPMPSolution> solution);

		void addEdge(Edge e);
		void removeEdge(Edge e);
		void setOrdering(std::vector<uint> newOrdering);
		uint computeEdgeCrossings(Edge e);
		void recomputeCrossings();

		uint getCrossings(); 
		std::vector<uint> getOrdering();
		uint getK();
		std::vector<Edge> getEdges();

		uint getNumVertices();

	private:
		uint k;
		uint numVertices;
		uint crossings;

		std::vector<uint> ordering;
		std::vector<uint> orderingInv;

		// each page has an adjacency matrix
		std::vector<AdjacencyMatrix> adjacencyMatrices;
		// only one adjacency list for all pages. it would be very expensive to change the page otherwise
		// use the adjacency matrix for a page lookup
		AdjacencyList adjacencyList;

		bool isCrossing(Edge& e1, Edge &e2);
		
};

#endif /* INSTANCE_SOLUTION_H_ */
