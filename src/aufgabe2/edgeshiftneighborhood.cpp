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
	// TODO: Implement
	return false;
}

shared_ptr<KPMPSolution> EdgeShiftNeighborhood::nextNeighbor() {
	// TODO: Implement
	return currentSolution;
}
