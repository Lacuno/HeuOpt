#include "variableneighborhoodsearch.h"
#include "variableneighborhooddescent.h"

using namespace std;

VariableNeighborhoodSearch::VariableNeighborhoodSearch(shared_ptr<KPMPSolution> bestSolutionSoFar) :
	bestSolutionFound(bestSolutionSoFar) {
}

shared_ptr<KPMPSolution> VariableNeighborhoodSearch::improve(vector<LocalSearchBundle> localSearches) {
	// Neighborhoods will me modified during local search procedure
	// --> Clone them to perform shaking
	vector<shared_ptr<Neighborhood>> shakingNeighborhoods;
	for(LocalSearchBundle lsb : localSearches) {
		shared_ptr<Neighborhood> unmodifiedNeighborhood = lsb.neighborhood->clone();
		unmodifiedNeighborhood->setCurrentSolution(bestSolutionFound);
		shakingNeighborhoods.push_back(unmodifiedNeighborhood);
	}

	// TODO: Define better stopping criteria
	for(uint stoppingCriteria = 0; stoppingCriteria < 100; stoppingCriteria++) {
		uint k = 0; 	// Neighborhood used for shaking
		while(k < localSearches.size()) {
			// Shaking
			shared_ptr<KPMPSolution> shakeNeighbor = shakingNeighborhoods[k]->randomNeighbor();

			// Improve shaking solution with VND
			VariableNeighborhoodDescent vnd(shakeNeighbor);	
			shared_ptr<KPMPSolution> improvedShakeNeighbor = vnd.improve(localSearches);

			if(improvedShakeNeighbor->getCrossings() < bestSolutionFound->getCrossings()) {
				bestSolutionFound = improvedShakeNeighbor;
				k = 0;
			} else {
				k++;
			}
		}	
	}

	return bestSolutionFound;
}
