#ifndef VARIABLE_NEIGHBORHOOD_SEARCH_H 
#define VARIABLE_NEIGHBORHOOD_SEARCH_H

#include <memory>
#include <vector>
#include "kpmp_solution.h"
#include "localsearch.h"

class VariableNeighborhoodSearch {
    public:
	VariableNeighborhoodSearch(std::shared_ptr<KPMPSolution> bestSolutionSoFar);
	std::shared_ptr<KPMPSolution> improve(std::vector<LocalSearchBundle> localSearches);

    private:
	std::shared_ptr<KPMPSolution> bestSolutionFound;
};

#endif /* VARIABLE_NEIGHBORHOOD_SEARCH_H */
