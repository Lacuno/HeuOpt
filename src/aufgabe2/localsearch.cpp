#include "localsearch.h"
#include "utils.h"

using namespace std;

LocalSearch::LocalSearch(uint timeLimitMin, uint timeLimitSec) 
	: timeLimitMin(timeLimitMin), timeLimitSec(timeLimitSec) {

}


shared_ptr<KPMPSolution> LocalSearch::improve(shared_ptr<KPMPSolution> currentSolution, shared_ptr<Neighborhood> neighborHood, StepFunction stepFunction) {
	shared_ptr<KPMPSolution> bestSolutionFound = currentSolution;
	double currentTime = 0; // Seconds
	uint timeLimit = timeLimitMin * 60 + timeLimitSec; // Seconds

	while(currentTime < timeLimit) {
	 	Utils::startTimeMeasurement();	

		shared_ptr<KPMPSolution> newSolution;
		switch(stepFunction) {
			case FIRST_IMPROVEMENT: newSolution = neighborHood->firstImprovement();
						break;
			case BEST_IMPROVEMENT:  newSolution = neighborHood->bestImprovement();
						break;
			case RANDOM:		newSolution = neighborHood->randomNeighbor();
						break;
		}

		if(!newSolution) {
			// newSolution is null (no better solution in neighborhood found)
			break;
		}

		if(newSolution->getCrossings() < bestSolutionFound->getCrossings()) {
			bestSolutionFound = newSolution;	
		}

		double timeForThisIteration = Utils::endTimeMeasurement();
		currentTime += timeForThisIteration;	
	}

	return bestSolutionFound;
}
