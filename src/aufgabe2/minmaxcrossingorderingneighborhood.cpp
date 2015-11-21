#include <vector>
#include <iostream>
#include "minmaxcrossingorderingneighborhood.h"

using namespace std;

MinMaxCrossingOrderingNeighborhood::MinMaxCrossingOrderingNeighborhood()
	: Neighborhood()
{
}
	
shared_ptr<KPMPSolution> MinMaxCrossingOrderingNeighborhood::randomNeighbor() {
	shared_ptr<KPMPSolution> neighbor = shared_ptr<KPMPSolution>(new KPMPSolution(currentSolution));

	uint idxMin = distribution(rng) % minCrossingsEdges.size();
	uint idxMax = distribution(rng) % maxCrossingsEdges.size();

	const Edge& minEdge = minCrossingsEdges[idxMin];
	const Edge& maxEdge = maxCrossingsEdges[idxMax];

	uint minV1 = currentSolution->getPositionInOrdering(minEdge.v1);
	uint minV2 = currentSolution->getPositionInOrdering(minEdge.v2);

	neighbor->shiftOrdering(maxEdge.v1, minV1);
	neighbor->shiftOrdering(maxEdge.v2, minV2);

	return neighbor;
}

bool MinMaxCrossingOrderingNeighborhood::hasNextNeighbor() {
	
	// the first iteration is special: we actually dont change anything with the iterating variables.
	if (firstIteration) {
		return true;
	}

	// page left
	if (currentPage + 1 < currentSolution->getK()) {
		return true;
	}

	// can also be false
	if (currentFlipped) {
		return true;
	}

	// no max edge left
	if (currentMaxIdx + 1 < maxCrossingsEdges.size()) {
		return true;
	}

	// min edge left
	if (currentMinIdx + 1 < minCrossingsEdges.size()) {
		return true;
	}

	return false;
}

shared_ptr<KPMPSolution> MinMaxCrossingOrderingNeighborhood::nextNeighbor() {

	shared_ptr<KPMPSolution> neighbor = shared_ptr<KPMPSolution>(new KPMPSolution(currentSolution));

	if (!firstIteration) {

		if (currentPage + 1 < currentSolution->getK()) {
			currentPage++;

		} else if (currentFlipped) {
			currentPage = 0;
			currentFlipped = false;

		} else if (currentMaxIdx + 1 < maxCrossingsEdges.size()) {
			currentFlipped = true;
			currentMaxIdx++;

		} else {
			currentMaxIdx = 0;
			currentMinIdx++;

			//std::cout << "currentShiftV1: " << currentShiftV1 << "/" << currentSolution->getNumVertices() << std::endl;
		}

	}
	else {
		firstIteration = false;
	}
	
	const Edge& minEdge = minCrossingsEdges[currentMinIdx];
	const Edge& maxEdge = maxCrossingsEdges[currentMaxIdx];

	// add the edge on a new page
	/*if (maxEdge.page != currentPage) {
		//std::cout << "moving edge " << edge.v1 << ", " << edge.v2 << " from page " << edge.page << " to " << currentPage << std::endl;
		neighbor->removeEdge(maxEdge);
		neighbor->addEdge({ maxEdge.v1, maxEdge.v2, currentPage });
	}*/

	// only do the shifting part if the flag is not set
	// ordering shift
	//std::cout << "shifting v1 " << edge.v1 << " to " << currentShiftV1 << " and v2 " << edge.v2 << " to " << currentShiftV2 << std::endl;
	uint minV1 = currentSolution->getPositionInOrdering(minEdge.v1);
	uint minV2 = currentSolution->getPositionInOrdering(minEdge.v2);

	if (currentFlipped) {
		std::swap(minV1, minV2);
	}

	neighbor->shiftOrdering(maxEdge.v1, minV1);
	neighbor->shiftOrdering(maxEdge.v2, minV2);

	return neighbor;
}

void MinMaxCrossingOrderingNeighborhood::setCurrentSolution(shared_ptr<KPMPSolution> newSolution) {
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

				if (crossingMatrix[x][y] < min) {
					minCrossingsEdges.clear();
					min = crossingMatrix[x][y];
				}

				if (crossingMatrix[x][y] <= min) {
					minCrossingsEdges.push_back({ x, y, (uint)newSolution->getPageForEdge(x, y) });
				}				
			}
		}
	}

	//for (auto e : maxCrossingsEdges)
	//	std::cout << e.v1 << ", " << e.v2 << " | " << e.page << ", max: " << max  << std::endl;
	//for (auto e : minCrossingsEdges)
	//	std::cout << e.v1 << ", " << e.v2 << " | " << e.page << ", min: " << min << std::endl;

	currentPage = 0;
	currentMinIdx = 0;
	currentMaxIdx = 0;
	currentFlipped = true;

	firstIteration = true;

	// Reinitialze Random Number Generator
	distribution = uniform_int_distribution<uint>(0, newSolution->getNumVertices() * newSolution->getNumVertices());
}

shared_ptr<Neighborhood> MinMaxCrossingOrderingNeighborhood::clone() {
	return shared_ptr<Neighborhood>(new MinMaxCrossingOrderingNeighborhood(*this));
}
