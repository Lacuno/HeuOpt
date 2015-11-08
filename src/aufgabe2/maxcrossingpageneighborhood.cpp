#include <vector>
#include <iostream>
#include "maxcrossingpageneighborhood.h"

using namespace std;

MaxCrossingPageNeighborhood::MaxCrossingPageNeighborhood()
	: Neighborhood()
{
}
	
shared_ptr<KPMPSolution> MaxCrossingPageNeighborhood::randomNeighbor() {
	shared_ptr<KPMPSolution> neighbor = shared_ptr<KPMPSolution>(new KPMPSolution(currentSolution));


	uint p = distribution(rng) % currentSolution->getK();
	uint idx = distribution(rng) % maxCrossingsEdges.size();

	const Edge& maxEdge = maxCrossingsEdges[idx];

	// add the edge on a new page
	if (maxEdge.page != p) {
		//std::cout << "moving edge " << edge.v1 << ", " << edge.v2 << " from page " << edge.page << " to " << currentPage << std::endl;
		neighbor->removeEdge(maxEdge);
		neighbor->addEdge({ maxEdge.v1, maxEdge.v2, p });
	}

	return neighbor;
}

bool MaxCrossingPageNeighborhood::hasNextNeighbor() {
	
	// the first iteration is special: we actually dont change anything with the iterating variables.
	if (firstIteration) {
		return true;
	}

	// page left
	if (currentPage + 1 < currentSolution->getK()) {
		return true;
	}

	// no max edge left
	if (currentMaxIdx + 1 < maxCrossingsEdges.size()) {
		return true;
	}

	return false;
}

shared_ptr<KPMPSolution> MaxCrossingPageNeighborhood::nextNeighbor() {

	shared_ptr<KPMPSolution> neighbor = shared_ptr<KPMPSolution>(new KPMPSolution(currentSolution));

	if (!firstIteration) {

		if (currentPage + 1 < currentSolution->getK()) {
			currentPage++;

		} else {
			currentPage = 0;
			currentMaxIdx++;

		} 

	}
	else {
		firstIteration = false;
	}
	
	const Edge& maxEdge = maxCrossingsEdges[currentMaxIdx];

	// add the edge on a new page
	if (maxEdge.page != currentPage) {
		//std::cout << "moving edge " << edge.v1 << ", " << edge.v2 << " from page " << edge.page << " to " << currentPage << std::endl;
		neighbor->removeEdge(maxEdge);
		neighbor->addEdge({ maxEdge.v1, maxEdge.v2, currentPage });
	}

	return neighbor;
}

void MaxCrossingPageNeighborhood::setCurrentSolution(shared_ptr<KPMPSolution> newSolution) {
	Neighborhood::setCurrentSolution(newSolution);

	const auto& adjacencyMatrix = newSolution->getAdjacencyMatrix();
	const auto& crossingMatrix = newSolution->getCrossingMatrix();
	const uint n = newSolution->getNumVertices();

	uint max = 0;
	uint min = n*n;

	for (uint x = 0; x < n; x++) {
		for (uint y = x + 1; y < n; y++) {
			if (adjacencyMatrix[x][y] >= 0) {

				if (crossingMatrix[x][y] > max) {
					maxCrossingsEdges.clear();
					max = crossingMatrix[x][y];
				}

				if (crossingMatrix[x][y] >= max) {
					maxCrossingsEdges.push_back({ x, y, (uint)newSolution->getPageForEdge(x, y) });
				}			
			}
		}
	}

	//for (auto e : maxCrossingsEdges)
	//	std::cout << e.v1 << ", " << e.v2 << " | " << e.page << ", max: " << max  << std::endl;
	//for (auto e : minCrossingsEdges)
	//	std::cout << e.v1 << ", " << e.v2 << " | " << e.page << ", min: " << min << std::endl;

	currentPage = 0;
	currentMaxIdx = 0;

	firstIteration = true;

	// Reinitialze Random Number Generator
	distribution = uniform_int_distribution<uint>(0, newSolution->getNumVertices() * newSolution->getNumVertices());
}