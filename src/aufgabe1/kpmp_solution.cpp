#include <iostream>
#include <algorithm>
#include "kpmp_solution.h"

using namespace std;
KPMPSolution::KPMPSolution(uint k, uint numVertices) : k(k) {
	for (uint i = 0; i < k; i++) {
		pageToEdges.insert({ i, vector<Edge>() });
	}

	for (uint i = 0; i < numVertices; i++) {
		ordering.insert({ i, i });
	}
}

uint KPMPSolution::getPage(Edge e) {
	return edgeToPage.at(e);
}

std::vector<Edge> KPMPSolution::getEdgesFromPage(uint p) {
	return pageToEdges.at(p);
}

void KPMPSolution::KPMPSolution::addEdge(uint p, Edge e) {
	pageToEdges.at(p).push_back(e);
	edgeToPage.insert({ e,p });
}

void KPMPSolution::KPMPSolution::removeEdge(Edge e) {
	vector<Edge>& edges = pageToEdges.at(edgeToPage.at(e));
	edges.erase(std::remove(edges.begin(), edges.end(), e), edges.end());

	edgeToPage.erase(e);
}


void KPMPSolution::setOrdering(std::unordered_map<uint, uint> &newOrdering) {
	ordering = newOrdering;
}

uint KPMPSolution::computeCrossings() {
	uint crossings = 0;

	auto isCrossing = [&](Edge& e1, Edge& e2) {
		pair<uint, uint> o1 = { ordering.at(e1.first), ordering.at(e1.second) };
		pair<uint, uint> o2 = { ordering.at(e2.first), ordering.at(e2.second) };

		uint o1_max = std::max(o1.first, o1.second);
		uint o1_min = std::min(o1.first, o1.second);
		uint o2_max = std::max(o2.first, o2.second);
		uint o2_min = std::min(o2.first, o2.second);

		// is the min vertex of edge 2 inside the vertices of edge 1
		if (o1_min > o2_min && o1_min < o2_max) {
			// is the max vertex of edge 2 outside the vertices of edge 1
			if (o1_max < o2_min || o1_max > o2_max) {
				return true;
			}
		}
		else if(o2_min < o1_min) {
			// min vertex of edge 2 is outside the vertices of edge 1

			// is the max vertex of edge 2 inside the vertices of edge 1?
			if (o1_max > o2_min && o1_max < o2_max) {
				return true;
			}
		}

		return false;
	};

	for (uint i = 0; i < k; i++) {
		const auto& edges = pageToEdges.at(i);

		std::cout << "found edges: " << edges.size() << std::endl;
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

