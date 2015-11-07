#include <vector>
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
	
	return true;
}

shared_ptr<KPMPSolution> MaxCrossingNeighborhood::nextNeighbor() {

	shared_ptr<KPMPSolution> neighbor;

	return neighbor;
}

void MaxCrossingNeighborhood::setCurrentSolution(shared_ptr<KPMPSolution> newSolution) {
	Neighborhood::setCurrentSolution(newSolution);
}