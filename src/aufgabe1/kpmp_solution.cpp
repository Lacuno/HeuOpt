#include <iostream>
#include <algorithm>
#include "kpmp_solution.h"

using namespace std;

KPMPSolution::KPMPSolution(uint k, uint numVertices) : k(k), numVertices(numVertices), crossings(0) {
	for (uint p = 0; p < k; p++) {
		// add an adjacency matrix/list for a page
		adjacencyMatrices.push_back(AdjacencyMatrix());

		for (uint x = 0; x < numVertices; x++) {
			adjacencyMatrices[p].push_back(std::vector<bool>());

			for (uint y= 0; y < numVertices; y++) {
				adjacencyMatrices[p][x].push_back(false);
			}
		}
	}

	for (uint i = 0; i < numVertices; i++) {
		ordering.push_back(i);
		orderingInv.push_back(i);

		adjacencyList.push_back(std::vector<std::reference_wrapper<uint>>());
	}

	
}

void KPMPSolution::KPMPSolution::addEdge(Edge e) {
	if (adjacencyMatrices[e.page][e.v1][e.v2] || adjacencyMatrices[e.page][e.v2][e.v1])
		throw new runtime_error("edge does already exist!");

	// add edge to adjacency matrix
	adjacencyMatrices[e.page][e.v1][e.v2] = true;
	adjacencyMatrices[e.page][e.v2][e.v1] = true;

	// add edge to adjacency list
	adjacencyList[ordering[e.v1]].push_back(ordering[e.v2]);
	adjacencyList[ordering[e.v2]].push_back(ordering[e.v1]);

	// update crossings
	crossings += computeEdgeCrossings(e);
}

void KPMPSolution::KPMPSolution::removeEdge(Edge e) {
	if (!adjacencyMatrices[e.page][e.v1][e.v2] || !adjacencyMatrices[e.page][e.v2][e.v1])
		throw new runtime_error("edge does not exist!");

	// update crossings
	crossings -= computeEdgeCrossings(e);

	// remove edge from adjacency matrix
	adjacencyMatrices[e.page][e.v1][e.v2] = false;
	adjacencyMatrices[e.page][e.v2][e.v1] = false;

	// remove edge from adjacency list
	auto &vertices1 = adjacencyList[ordering[e.v1]];
	auto &vertices2 = adjacencyList[ordering[e.v2]];
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
	// we have to flip ordering (vertex -> index to index -> vertex)
	std::vector<uint> orderingFlipped = ordering;
	for (uint i = 0; i < ordering.size(); i++) {
		orderingFlipped[ordering[i]] = i;
	}

	return orderingFlipped;
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

	for (uint p = 0; p < k; p++) {
		for (uint v1 = 0; v1 < numVertices; v1++) {
			for (uint v2 = v1 + 1; v2 < numVertices; v2++) {
				if (adjacencyMatrices[p][v1][v2]) {
					edges.push_back({v1, v2, p});
				}
			}
		}
	}

	return edges;
}

/*void KPMPSolution::normalizeEdge(Edge& e)
{
	if (e.v1 > e.v2) {
		std::swap(e.v1, e.v2);
	}
}*/

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
		for (uint v_neighbor : adjacencyList[v]) {
			// check if the edge lies on the page and the neighbor is outside
			if (adjacencyMatrices[e.page][orderingInv[v]][orderingInv[v_neighbor]] && (v_neighbor < v_min || v_neighbor > v_max)) {
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


	// for all vertices
	for (uint v1_min = 0; v1_min < numVertices; v1_min++) {

		// for all neighbors of the vertex
		for (uint v1_max : adjacencyList[v1_min]) {

			// on what page is the edge?
			uint page = 0;
			for (uint p = 0; p < k; p++) {
				if (adjacencyMatrices[p][orderingInv[v1_min]][orderingInv[v1_max]]) {
					page = p;
					break;
				}
			}

			// only consider the 'smaller to bigger' edges: this takes care of not counting edges twice
			if (v1_min < v1_max && adjacencyMatrices[page][orderingInv[v1_min]][orderingInv[v1_max]]) {

				// iterate every vertex between v1 min and v1 max
				for (uint v2_min = v1_min + 1; v2_min < v1_max; v2_min++) {

					// iterate over all neighbors of v2_min
					for (uint v2_max : adjacencyList[v2_min]) {

						// check if the edge lies on the page and the neighbor is greater
						if (adjacencyMatrices[page][orderingInv[v2_min]][orderingInv[v2_max]] && v1_max < v2_max) {
							crossings++;

							std::cout << crossings << ". crossing detected: " << v1_min << ", " << v1_max << " | " << v2_min << ", " << v2_max << std::endl;
						}
					}
				}
			}
		}
	}
}
