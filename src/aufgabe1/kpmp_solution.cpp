#include <iostream>
#include <algorithm>
#include "kpmp_solution.h"

using namespace std;

KPMPSolution::KPMPSolution(uint k, uint numVertices) : k(k), numVertices(numVertices){
	for (uint i = 0; i < k; i++) {
		pageToEdges.insert({ i, vector<Edge>() });
	}

	for (uint i = 0; i < numVertices; i++) {
		ordering.insert({ i, i });
	}
}

std::vector<Edge> KPMPSolution::getEdgesFromPage(uint p) {
	return pageToEdges.at(p);
}

void KPMPSolution::KPMPSolution::addEdge(Edge e, bool orderingIncluded) {
	if(orderingIncluded) {
		normalizeEdge(e);
		pageToEdges.at(e.page).push_back(e);
	}
	else {
		Edge e_ordered = { ordering.at(e.v1), ordering.at(e.v2), e.page };
		normalizeEdge(e_ordered);
		pageToEdges.at(e.page).push_back(e_ordered);
	}
}

void KPMPSolution::KPMPSolution::removeEdge(Edge e) {
	std::vector<Edge>& edges = pageToEdges.at(e.page);
	edges.erase(std::remove_if(edges.begin(), edges.end(), [&](Edge const& e_) {return e_.v1 == e.v1 && e_.v2 == e.v2; }), edges.end());
}


void KPMPSolution::setOrdering(std::vector<uint> newOrdering) {
	// go through all pages
	for (auto& pte : pageToEdges) {
		auto& edges = pte.second;

		// go through all edges
		for (auto &edge : edges) {
			edge.v1 = newOrdering[ordering[edge.v1]];
			edge.v2 = newOrdering[ordering[edge.v2]];

			normalizeEdge(edge);
		}
	}

	// save new ordering
	ordering.clear();
	for (uint i = 0; i < newOrdering.size(); i++) {
		ordering.insert({ newOrdering[i], i });
	}
}

uint KPMPSolution::computeCrossings() {
	uint crossings = 0;

	auto isCrossing = [&](Edge& e1, Edge& e2) {
		// entire intervals not overlapping?
		if (e1.v2 <= e2.v1 || e2.v2 <= e1.v1)
			return false;

		// entire interval inside the other?
		if (e1.v1 >= e2.v1 && e1.v2 <= e2.v2
			|| e2.v1 >= e1.v1 && e2.v2 <= e1.v2)
			return false;

		return true;
	};

	for (uint i = 0; i < k; i++) {
		const auto& edges = pageToEdges.at(i);

		for (auto iterator1 = edges.begin(); iterator1 != edges.end(); ++iterator1) {
			for (auto iterator2 = iterator1 + 1; iterator2 != edges.end(); ++iterator2) {
				Edge edge1 = *iterator1;
				Edge edge2 = *iterator2;

				if (isCrossing(edge1, edge2)) {
					crossings++;
				}
			}
		}
	}

	return crossings;
}

void KPMPSolution::normalizeEdge(Edge& e)
{
	if (e.v1 > e.v2) {
		uint tmp = e.v1;
		e.v1 = e.v2;
		e.v2 = tmp;
	}
}

