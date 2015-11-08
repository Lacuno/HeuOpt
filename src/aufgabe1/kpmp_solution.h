#ifndef INSTANCE_SOLUTION_H_
#define INSTANCE_SOLUTION_H_

#include <vector>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <memory>

typedef unsigned int uint;
typedef std::vector<std::vector<int>> AdjacencyMatrix;
typedef std::vector<std::vector<uint>> CrossingsMatrix;
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

		uint getK();
		uint getNumVertices();

		void addEdge(Edge e);
		void removeEdge(Edge e);
		std::vector<Edge> getEdges();
		int getPageForEdge(uint v1, uint v2); // -1 if edge not found
		
		const std::vector<uint>& getOrdering();
		void setOrdering(std::vector<uint> newOrdering);
		void shiftOrdering(uint elementToMove, uint shift);
		uint getPositionInOrdering(uint v);

		void recomputeCrossings();
		uint getCrossings(); 
		uint getEdgeCrossings(Edge e);
		const CrossingsMatrix& getCrossingMatrix();

		std::vector<uint> getNeighbors(uint page, uint v);
		const AdjacencyMatrix& getAdjacencyMatrix();

		void printCrossingMatrix();

	private:
		uint k;
		uint numVertices;
		uint crossings;

		std::vector<uint> ordering;
		std::vector<uint> orderingInv;

		// -1 = no edge, otherwise the entry corresponds with the page
		AdjacencyMatrix adjacencyMatrix;
		// stores the number of crossings of every edge
		CrossingsMatrix crossingsMatrix;
		// each page has its own adjacency list. the adjacent vertices are pointing to the ordering (use orderingInv to get the original vertex)
		std::vector<AdjacencyList> adjacencyLists;

		bool isCrossing(Edge& e1, Edge &e2);

		// computes the crossings with the edge e and updates the counters (crossings, crossingsMatrix)
		// inc = 1 add to crossings
		// inc = -1 subtract from crossings
		// inc = 0 dont change crossings
		uint updateEdgeCrossings(Edge e, char inc = 0);
		
};

#endif /* INSTANCE_SOLUTION_H_ */
