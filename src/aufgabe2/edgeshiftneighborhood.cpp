#include "edgeshiftneighborhood.h"

using namespace std;

EdgeShiftNeighborhood::EdgeShiftNeighborhood() :
	Neighborhood() {

}
	
shared_ptr<KPMPSolution> EdgeShiftNeighborhood::randomNeighbor() {
	// TODO: Implement
	return currentSolution;
}

bool EdgeShiftNeighborhood::hasNextNeighbor() {

	uint k = currentSolution->getK();
	return currentPage < k;
}

shared_ptr<KPMPSolution> EdgeShiftNeighborhood::nextNeighbor() {

	shared_ptr<KPMPSolution> neighbor = generateNewNeighbor(currentPos, shiftTo);	

	// Next neighbor
	uint orderingSize = currentSolution->getNumVertices(); 
	shiftTo++;
	if(shiftTo == currentPos) {
		shiftTo++;
	}
	currentPos += shiftTo / orderingSize;
	shiftTo %= orderingSize;

	return neighbor;


	return currentSolution;
}
