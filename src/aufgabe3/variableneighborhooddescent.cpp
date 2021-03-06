#include "variableneighborhooddescent.h"
#include <iostream>

using namespace std;

VariableNeighborhoodDescent::VariableNeighborhoodDescent(shared_ptr<KPMPSolution> bestSolutionSoFar) : 
	bestSolutionFound(bestSolutionSoFar) {
}

shared_ptr<KPMPSolution> VariableNeighborhoodDescent::improve(vector<LocalSearchBundle> localSearchBundles) {
	uint i = 0;

	while(i < localSearchBundles.size()) {
		cout << "VND ITERATION using neighborhood " << i << endl;
		
		shared_ptr<LocalSearch> chosenLocalSearch = localSearchBundles[i].localSearch;
		localSearchBundles[i].neighborhood->setCurrentSolution(bestSolutionFound);
		shared_ptr<KPMPSolution> betterSolution = chosenLocalSearch->improve(bestSolutionFound, localSearchBundles[i].neighborhood, localSearchBundles[i].stepFunction);

		if(betterSolution->getCrossings() < bestSolutionFound->getCrossings()) {
			bestSolutionFound = betterSolution;
			i = 0;
		} else {
			i++;
		}
	}

	return bestSolutionFound;
}
