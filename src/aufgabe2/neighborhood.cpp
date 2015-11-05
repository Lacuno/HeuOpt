#include "neighborhood.h"

using namespace std;

Neighborhood::Neighborhood(std::shared_ptr<KPMPSolution> currentSolution) :
	currentSolution(currentSolution) {

}

shared_ptr<KPMPSolution> Neighborhood::firstImprovement() {
	return this->improve(false);
}

shared_ptr<KPMPSolution> Neighborhood::bestImprovement() {
	return this->improve(true);
}

shared_ptr<KPMPSolution> Neighborhood::improve(bool isBestImprovement) {
	shared_ptr<KPMPSolution> bestFoundSolution = currentSolution;

	while(hasNextNeighbor()) {
		shared_ptr<KPMPSolution> newSolution = nextNeighbor();
		if(newSolution->getCrossings() < bestFoundSolution->getCrossings()) {
			bestFoundSolution = newSolution;
			if(!isBestImprovement) {
				break;
			}
		}
	}

	if(bestFoundSolution == currentSolution) {
		// = nullptr
		return shared_ptr<KPMPSolution>();
	} else {
		currentSolution = bestFoundSolution;
		return bestFoundSolution;
	}
}
