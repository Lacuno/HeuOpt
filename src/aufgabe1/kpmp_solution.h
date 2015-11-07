#ifndef INSTANCE_SOLUTION_H_
#define INSTANCE_SOLUTION_H_

#include <vector>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <memory>

typedef unsigned int uint;
typedef std::vector<std::vector<int>> AdjacencyMatrix;
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

		void shiftOrdering(uint idx, uint shift);
		void setOrdering(std::vector<uint> newOrdering);

		uint computeEdgeCrossings(Edge e);
		void recomputeCrossings();

		uint getCrossings(); 
		std::vector<uint> getOrdering();
		uint getK();
		std::vector<Edge> getEdges();

		uint getNumVertices();
		std::vector<uint> getNeighbors(uint page, uint v);
		const AdjacencyMatrix& getAdjacencyMatrix();
		int getPageForEdge(uint v1, uint v2); // -1 if edge not found

	private:
		uint k;
		uint numVertices;
		uint crossings;

		std::vector<uint> ordering;
		std::vector<uint> orderingInv;

		AdjacencyMatrix adjacencyMatrix;
		std::vector<AdjacencyList> adjacencyLists;

		bool isCrossing(Edge& e1, Edge &e2);
		
};

#endif /* INSTANCE_SOLUTION_H_ */
