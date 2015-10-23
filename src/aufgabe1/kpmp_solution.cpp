#include <iostream>
#include <algorithm>
#include "kpmp_solution.h"

using namespace std;

KPMPSolution::KPMPSolution(uint k, uint numVertices) : k(k), numVertices(numVertices){
	for (uint i = 0; i < k; i++) {
		pageToEdges.insert({ i, vector<Edge>() });
	}

	for (uint i = 0; i < numVertices; i++) {
		positionToVertex.push_back(i);
		vertexToPosition.push_back(i);
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
		Edge e_ordered = { positionToVertex[e.v1], positionToVertex[e.v2], e.page };
		normalizeEdge(e_ordered);
		pageToEdges.at(e.page).push_back(e_ordered);
	}
}

void KPMPSolution::KPMPSolution::removeEdge(Edge e, bool orderingIncluded) {
	std::vector<Edge>& edges = pageToEdges.at(e.page);

	if (!orderingIncluded) {
		e = { positionToVertex[e.v1], positionToVertex[e.v2], e.page };
	}

	normalizeEdge(e);
	edges.erase(std::remove_if(edges.begin(), edges.end(), [&](Edge const& e_) {return e_.v1 == e.v1 && e_.v2 == e.v2; }), edges.end());
}


void KPMPSolution::setOrdering(std::vector<uint> ordering) {
	// ordering is just a new ordering of vertices (vertex -> position)
	for (uint i = 0; i < ordering.size(); i++) {
		positionToVertex[ordering[i]] = i;
	}

	// go through all pages
	for (auto& pte : pageToEdges) {
		auto& edges = pte.second;

		// go through all edges
		for (auto &edge : edges) {
			edge.v1 = positionToVertex[vertexToPosition[edge.v1]];
			edge.v2 = positionToVertex[vertexToPosition[edge.v2]];

			normalizeEdge(edge);
		}
	}

	// save new ordering
	vertexToPosition = ordering;
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
		std::swap(e.v1, e.v2);
	}
}

