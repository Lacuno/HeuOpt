#include <vector>
#include "orderingshiftneighborhood.h"

using namespace std;

OrderingShiftNeighborhood::OrderingShiftNeighborhood() 
	: Neighborhood()
{
}
	
shared_ptr<KPMPSolution> OrderingShiftNeighborhood::randomNeighbor() {
	
	uint randomElem = distribution(rng);
	uint shift = distribution(rng);

	while(shiftTo == randomElem) {
		shift = distribution(rng);
	}

	shared_ptr<KPMPSolution> neighbor = generateNewNeighbor(randomElem, shift);	
	return neighbor;
}

bool OrderingShiftNeighborhood::hasNextNeighbor() {
	
	uint orderingSize = currentSolution->getNumVertices();
	return currentPos < orderingSize-1;
}

shared_ptr<KPMPSolution> OrderingShiftNeighborhood::nextNeighbor() {

	shared_ptr<KPMPSolution> neighbor = generateNewNeighbor(currentPos, shiftTo);	

	// Next neighbor
	uint orderingSize = currentSolution->getNumVertices(); 
	shiftTo++;
	currentPos += shiftTo / orderingSize;
	shiftTo %= orderingSize;

	return neighbor;
}

void OrderingShiftNeighborhood::setCurrentSolution(shared_ptr<KPMPSolution> newSolution) {
	
	Neighborhood::setCurrentSolution(newSolution);
	currentPos = 0;
	shiftTo = 1;
	
	// Reinitialze Random Number Generator
	distribution = uniform_int_distribution<uint>(0, newSolution->getOrdering().size()-1);
}

shared_ptr<KPMPSolution> OrderingShiftNeighborhood::generateNewNeighbor(uint elem, uint shift) {

	shared_ptr<KPMPSolution> neighbor = shared_ptr<KPMPSolution>(new KPMPSolution(*currentSolution));
	vector<uint> newOrdering = currentSolution->getOrdering();

	uint elementToMove = newOrdering[elem];
	newOrdering.erase(newOrdering.begin() + elem);
	newOrdering.insert(newOrdering.begin() + shift, elementToMove);
	neighbor->setOrdering(newOrdering);

	return neighbor;
}
