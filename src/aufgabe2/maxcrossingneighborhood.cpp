#include <vector>
#include <iostream>
#include "maxcrossingneighborhood.h"

using namespace std;

MaxCrossingNeighborhood::MaxCrossingNeighborhood()
	: Neighborhood()
{
}
	
shared_ptr<KPMPSolution> MaxCrossingNeighborhood::randomNeighbor() {
	shared_ptr<KPMPSolution> neighbor;

	return neighbor;
}

bool MaxCrossingNeighborhood::hasNextNeighbor() {
	
	// the first iteration is special: we actually dont change anything with the iterating variables.
	if (firstIteration) {
		return true;
	}

	
	// no edge left
	if (currentIdx + 1 >= maxCrossingsEdges.size()) {

		// no page left
		if (currentPage + 1 >= currentSolution->getK()) {

			// no v2 shift left
			if (currentShiftV2 + 1 >= currentSolution->getNumVertices()) {

				// no v1 shift left
				if (currentShiftV1 + 2 >= currentSolution->getNumVertices()) {
					return false;
				}
			}
		}
	}

	return true;
}

shared_ptr<KPMPSolution> MaxCrossingNeighborhood::nextNeighbor() {

	shared_ptr<KPMPSolution> neighbor = shared_ptr<KPMPSolution>(new KPMPSolution(currentSolution));
	//shared_ptr<KPMPSolution> neighbor = currentSolution;

	if (!firstIteration) {

		if (currentIdx + 1 < maxCrossingsEdges.size()) {
			currentIdx++;

		} else if (currentPage + 1 < currentSolution->getK()) {
			currentIdx = 0;
			currentPage++;

			//std::cout << "currentPage: " << currentPage << "/" << currentSolution->getK() << std::endl;

		} else if (currentShiftV2 + 1 < currentSolution->getNumVertices()) {
			currentPage = 0;
			currentShiftV2++;

			std::cout << "currentShiftV2: " << currentShiftV2 << "/" << currentSolution->getNumVertices() << std::endl;

		} else {
			currentShiftV2 = 0;
			currentShiftV1++;

			std::cout << "currentShiftV1: " << currentShiftV1 << "/" << currentSolution->getNumVertices() << std::endl;
		}
	}
	else {
		firstIteration = false;
	}

	const Edge& edge = maxCrossingsEdges[currentIdx];

	// add the edge on a new page
	if (edge.page != currentPage) {
		//std::cout << "moving edge " << edge.v1 << ", " << edge.v2 << " from page " << edge.page << " to " << currentPage << std::endl;
		neighbor->removeEdge(edge);
		neighbor->addEdge({ edge.v1, edge.v2, currentPage });
	}

	// ordering shift
	//std::cout << "shifting v1 " << edge.v1 << " to " << currentShiftV1 << " and v2 " << edge.v2 << " to " << currentShiftV2 << std::endl;
	neighbor->shiftOrdering(edge.v1, currentShiftV1);
	neighbor->shiftOrdering(edge.v2, currentShiftV2);

	return neighbor;
}

void MaxCrossingNeighborhood::setCurrentSolution(shared_ptr<KPMPSolution> newSolution) {
	Neighborhood::setCurrentSolution(newSolution);

	const auto& crossingMatrix = newSolution->getCrossingMatrix();
	
	uint max = 0;
	for (uint x = 0; x < newSolution->getNumVertices(); x++) {
		for (uint y = x + 1; y < newSolution->getNumVertices(); y++) {
			if (crossingMatrix[x][y] > max) {
				maxCrossingsEdges.clear();
				max = crossingMatrix[x][y];
			}

			if (crossingMatrix[x][y] >= max) {
				maxCrossingsEdges.push_back({ x, y, (uint)newSolution->getPageForEdge(x, y) });
			}
		}
	}
	currentPage = 0;
	currentIdx = 0;
	currentShiftV1 = 0;
	currentShiftV2 = 1;
	firstIteration = true;
}