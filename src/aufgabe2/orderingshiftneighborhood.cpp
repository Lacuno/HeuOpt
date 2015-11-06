#include <vector>
#include "orderingshiftneighborhood.h"

using namespace std;

OrderingShiftNeighborhood::OrderingShiftNeighborhood() 
	: Neighborhood()
{
}
	
shared_ptr<KPMPSolution> OrderingShiftNeighborhood::randomNeighbor() {
	
	// TODO: Implement
	return currentSolution;
}

bool OrderingShiftNeighborhood::hasNextNeighbor() {
	
	uint orderingSize = currentSolution->getOrdering().size(); // TODO: make sure getOrdering returns a const reference
	return currentPos < orderingSize-1;
}

shared_ptr<KPMPSolution> OrderingShiftNeighborhood::nextNeighbor() {

	// Generate new neighbor
	shared_ptr<KPMPSolution> neighbor = shared_ptr<KPMPSolution>(new KPMPSolution(*currentSolution));
	vector<uint> newOrdering = currentSolution->getOrdering();

	uint elementToMove = newOrdering[currentPos];
	newOrdering.erase(newOrdering.begin() + currentPos);
	newOrdering.insert(newOrdering.begin() + shiftTo, elementToMove);
	neighbor->setOrdering(newOrdering);

	// Next neighbor
	uint orderingSize = currentSolution->getOrdering().size(); // TODO: make sure getOrdering returns a const reference
	shiftTo++;
	currentPos += shiftTo / orderingSize;
	shiftTo %= orderingSize;

	return neighbor;
}

void OrderingShiftNeighborhood::setCurrentSolution(shared_ptr<KPMPSolution> newSolution) {
	Neighborhood::setCurrentSolution(newSolution);
	currentPos = 0;
	shiftTo = 1;
}
