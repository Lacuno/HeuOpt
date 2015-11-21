#include "edgeshiftneighborhood.h"
#include <iostream>
#include <cassert>

using namespace std;

EdgeShiftNeighborhood::EdgeShiftNeighborhood() :
	Neighborhood() {

}
	
shared_ptr<KPMPSolution> EdgeShiftNeighborhood::randomNeighbor() {

	uint v1 = distribution(rng);	
	uint v2 = distribution(rng);

	uint page = currentSolution->getPageForEdge(v1, v2);
	while(page == -1) {
		v1 = distribution(rng);
		v2 = distribution(rng);
		page = currentSolution->getPageForEdge(v1, v2);
	}

	uint shiftToPage = distribution(rng) % currentSolution->getK();
	while(page == shiftToPage) {
		shiftToPage = distribution(rng) % currentSolution->getK();
	}

	Edge e = {v1, v2, page};
	shared_ptr<KPMPSolution> neighbor = generateNewNeighbor(shiftToPage, e);
	return neighbor;
}

bool EdgeShiftNeighborhood::hasNextNeighbor() {

	uint numVertices = currentSolution->getNumVertices();
	uint k = currentSolution->getK();
	assert(currentEdgeV1 < numVertices);
	assert(currentEdgeV2 < numVertices);
	const auto& matrix = currentSolution->getAdjacencyMatrix();
	while(currentPage < k) {
		if(matrix[currentEdgeV1][currentEdgeV2] == currentPage) {
			return true;
		} else {
			currentEdgeV2++;
			if(currentEdgeV2 >= numVertices) {
				currentEdgeV1++;
				if(currentEdgeV1 >= numVertices-1) {
					currentPage++;
					currentEdgeV1 = 0;
				}
				currentEdgeV2 = currentEdgeV1 + 1;
			}

			currentPage == 0 ? shiftToPage = 1 : shiftToPage = 0;
		}
	}

	return false;
}

shared_ptr<KPMPSolution> EdgeShiftNeighborhood::nextNeighbor() {

	Edge e = {currentEdgeV1, currentEdgeV2, currentPage};
	shared_ptr<KPMPSolution> neighbor = generateNewNeighbor(shiftToPage, e);	

	// Next neighbor
	// uint pageSize= currentSolution.getSizeOfPage(currentPage); 
	uint k = currentSolution->getK();
	uint numVertices = currentSolution->getNumVertices();

	shiftToPage++;
	if(shiftToPage == currentPage) {
		shiftToPage++;
	}

	if(shiftToPage >= k) {
		shiftToPage = 0;
		currentEdgeV2++;
		if(currentEdgeV2 >= numVertices) {
			currentEdgeV1++;
			if(currentEdgeV1 >= numVertices-1) {
				currentPage++;
				currentEdgeV1 = 0;
			}
			currentEdgeV2 = currentEdgeV1 + 1;
		}

	}

	return neighbor;
}

void EdgeShiftNeighborhood::setCurrentSolution(shared_ptr<KPMPSolution> newSolution) {
	
	Neighborhood::setCurrentSolution(newSolution);
	currentPage = 0;
	currentEdgeV1 = 0;
	currentEdgeV2 = 1;
	shiftToPage = 1;	

	// Reinitialze Random Number Generator
	distribution = uniform_int_distribution<uint>(0, newSolution->getNumVertices()-1);
}

shared_ptr<KPMPSolution> EdgeShiftNeighborhood::generateNewNeighbor(uint shiftToPage, Edge& edge) {

	shared_ptr<KPMPSolution> neighbor = shared_ptr<KPMPSolution>(new KPMPSolution(currentSolution));
	neighbor->removeEdge(edge);
	edge.page = shiftToPage;
	neighbor->addEdge(edge);	

	return neighbor;
}

shared_ptr<Neighborhood> EdgeShiftNeighborhood::clone() {
	return shared_ptr<Neighborhood>(new EdgeShiftNeighborhood(*this));
}
