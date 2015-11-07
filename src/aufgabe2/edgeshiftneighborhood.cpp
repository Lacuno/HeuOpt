#include "edgeshiftneighborhood.h"
#include <iostream>
#include <cassert>

using namespace std;

EdgeShiftNeighborhood::EdgeShiftNeighborhood() :
	Neighborhood() {

}
	
shared_ptr<KPMPSolution> EdgeShiftNeighborhood::randomNeighbor() {
	// TODO: Implement
	return currentSolution;
}

bool EdgeShiftNeighborhood::hasNextNeighbor() {

	uint numVertices = currentSolution->getNumVertices();
	uint k = currentSolution->getK();
	assert(currentEdgeV1 < numVertices);
	assert(currentEdgeV2 < numVertices);
	const auto& matrices = currentSolution->getAdjacencyMatrices();
	while(currentPage < k) {
		if(matrices[currentPage][currentEdgeV1][currentEdgeV2]) {
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
	distribution = uniform_int_distribution<uint>(0, newSolution->getOrdering().size()-1);
}

shared_ptr<KPMPSolution> EdgeShiftNeighborhood::generateNewNeighbor(uint shiftToPage, Edge& edge) {

//	cout << "Move edge " << edge.v1 << " " << edge.v2 << " from page " << edge.page << " to page " << shiftToPage << endl;
	shared_ptr<KPMPSolution> neighbor = shared_ptr<KPMPSolution>(new KPMPSolution(currentSolution));
	neighbor->removeEdge(edge);
	edge.page = shiftToPage;
	neighbor->addEdge(edge);	

	return neighbor;
}

