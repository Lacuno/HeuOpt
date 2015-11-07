#include <iostream>
#include <algorithm>
#include <functional>
#include "kpmp_solution.h"

using namespace std;

KPMPSolution::KPMPSolution(uint k, uint numVertices) : k(k), numVertices(numVertices), crossings(0) {

	for (uint p = 0; p < k; p++) {
		adjacencyLists.push_back(AdjacencyList());

		for (uint i = 0; i < numVertices; i++) {
			adjacencyLists[p].push_back(std::vector<std::reference_wrapper<uint>>());
		}
	}

	for (uint x = 0; x < numVertices; x++) {
		adjacencyMatrix.push_back(std::vector<int>());

		ordering.push_back(x);
		orderingInv.push_back(x);

		for (uint y= 0; y < numVertices; y++) {
			adjacencyMatrix[x].push_back(-1);
		}
	}
	
}

KPMPSolution::KPMPSolution(shared_ptr<KPMPSolution> solution) {
	k = solution->k;
	numVertices = solution->numVertices;
	crossings = solution->crossings;

	ordering = solution->ordering;
	orderingInv = solution->orderingInv;
	adjacencyMatrix = solution->adjacencyMatrix;

	for (uint p = 0; p < k; p++) {
		adjacencyLists.push_back(AdjacencyList());

		for (uint i = 0; i < numVertices; i++) {
			adjacencyLists[p].push_back(std::vector<std::reference_wrapper<uint>>());

			for (uint v_ : solution->adjacencyLists[p][i]) {
				uint v = orderingInv[v_];
				adjacencyLists[p][i].push_back(std::ref(ordering[v]));
			}
		}
	}

}

void KPMPSolution::KPMPSolution::addEdge(Edge e) {
	if (adjacencyMatrix[e.v1][e.v2] >= 0)
		throw std::invalid_argument("edge does already exist!");

	// add edge to adjacency matrix
	adjacencyMatrix[e.v1][e.v2] = e.page;
	adjacencyMatrix[e.v2][e.v1] = e.page;

	// add edge to adjacency list
	adjacencyLists[e.page][e.v1].push_back(std::ref(ordering[e.v2]));
	adjacencyLists[e.page][e.v2].push_back(std::ref(ordering[e.v1]));


	// update crossings
	crossings += computeEdgeCrossings(e);
}

void KPMPSolution::KPMPSolution::removeEdge(Edge e) {
	if (adjacencyMatrix[e.v1][e.v2] == -1)
		throw std::invalid_argument("edge does not exist!");

	// update crossings
	crossings -= computeEdgeCrossings(e);

	// remove edge from adjacency matrix
	adjacencyMatrix[e.v1][e.v2] = -1;
	adjacencyMatrix[e.v2][e.v1] = -1;

	// remove edge from adjacency list
	auto &vertices1 = adjacencyLists[e.page][e.v1];
	auto &vertices2 = adjacencyLists[e.page][e.v2];
	vertices1.erase(std::remove_if(vertices1.begin(), vertices1.end(), [&](uint const &v) { return v == ordering[e.v2]; }), vertices1.end());
	vertices2.erase(std::remove_if(vertices2.begin(), vertices2.end(), [&](uint const &v) { return v == ordering[e.v1]; }), vertices2.end());
}

void KPMPSolution::setOrdering(std::vector<uint> newOrdering) {
	// we have to flip ordering (index -> vertex to vertex -> index)
	for (uint i = 0; i < ordering.size(); i++) {
		ordering[newOrdering[i]] = i;
		orderingInv[i] = newOrdering[i];
	}

	// recompute crossings
	recomputeCrossings();
}

std::vector<uint> KPMPSolution::getOrdering() {
	return orderingInv;
}

uint KPMPSolution::getCrossings() {
	return crossings;
}

uint KPMPSolution::getK() {
	return k;
}

std::vector<Edge> KPMPSolution::getEdges()
{
	std::vector<Edge> edges;

	for (uint v1 = 0; v1 < numVertices; v1++) {
		for (uint v2 = v1 + 1; v2 < numVertices; v2++) {
			if (adjacencyMatrix[v1][v2] >= 0) {
				edges.push_back({v1, v2, (uint)adjacencyMatrix[v1][v2] });
			}
		}
	}

	return edges;
}

bool KPMPSolution::isCrossing(Edge &e1, Edge &e2) {
	uint e1_min = std::min(ordering[e1.v1], ordering[e1.v2]);
	uint e1_max = std::max(ordering[e1.v1], ordering[e1.v2]);
	uint e2_min = std::min(ordering[e2.v1], ordering[e2.v2]);
	uint e2_max = std::max(ordering[e2.v1], ordering[e2.v2]);

	// entire intervals not overlapping?
	if (e1_max <= e2_min || e2_max <= e1_min)
		return false;

	// entire interval inside the other?
	if (e1_min >= e2_min && e1_max <= e2_max
		|| e2_min >= e1_min && e2_max <= e1_max)
		return false;

	return true;
}

uint KPMPSolution::computeEdgeCrossings(Edge e) {
	uint edgeCrossings = 0;
	uint v_min = ordering[e.v1];
	uint v_max = ordering[e.v2];

	if (v_min > v_max)
		std::swap(v_min, v_max);

	// a crossing must go from the inside of the interval to the outside
	for (uint v = v_min + 1; v < v_max; v++) {

		// iterate over all neighbors of v
		for (uint v_neighbor : adjacencyLists[e.page][orderingInv[v]]) {

			// check if the edge lies on the page and the neighbor is outside
			if (v_neighbor < v_min || v_neighbor > v_max) {
				edgeCrossings++;
			}
		}
	}

	return edgeCrossings;
}

void KPMPSolution::recomputeCrossings() {
	crossings = 0;

	// the fankhausersche cross finding algorithm (c) d. fankhauser 
	// written at 03:00am, so no bugs guaranteed!

	// sum crossings of all pages
	for (uint p = 0; p < k; p++) {

		// for all vertices
		for (uint v1_min = 0; v1_min < numVertices; v1_min++) {

			// for all neighbors of the vertex
			for (uint v1_max : adjacencyLists[p][orderingInv[v1_min]]) {

				// only consider the 'smaller to bigger' edges: this takes care of not counting edges twice
				if (v1_min < v1_max) {

					// iterate every vertex between v1 min and v1 max
					for (uint v2_min = v1_min + 1; v2_min < v1_max; v2_min++) {

						// iterate over all neighbors of v2_min
						for (uint v2_max : adjacencyLists[p][orderingInv[v2_min]]) {

							// check if the edge lies on the page and the neighbor is greater
							if (v1_max < v2_max) {
								crossings++;
							}
						}
					}
				}
			}
		}
	}
}

uint KPMPSolution::getNumVertices() {
	return numVertices;
}

std::vector<uint> KPMPSolution::getNeighbors(uint page, uint v) {
	std::vector<uint> neighbors;

	for (uint n : adjacencyLists[page][v]) {
		neighbors.push_back(orderingInv[n]);
	}

	return neighbors;
}

const AdjacencyMatrix& KPMPSolution::getAdjacencyMatrix() {
	return adjacencyMatrix;
}

int KPMPSolution::getPageForEdge(uint v1, uint v2) {
	return adjacencyMatrix[v1][v2];
}
