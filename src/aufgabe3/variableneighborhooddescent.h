#ifndef VARIABLE_NEIGHBORHOOD_DESCENT_H 
#define VARIABLE_NEIGHBORHOOD_DESCENT_H

#include <memory>
#include <vector>
#include "kpmp_solution.h"
#include "localsearch.h"

class VariableNeighborhoodDescent {
    public:
	VariableNeighborhoodDescent(std::shared_ptr<KPMPSolution> bestSolutionSoFar);
	std::shared_ptr<KPMPSolution> improve(std::vector<LocalSearchBundle> neighborhoods);

    private:
	std::shared_ptr<KPMPSolution> bestSolutionFound;
};

#endif /* VARIABLE_NEIGHBORHOOD_DESCENT_H */
