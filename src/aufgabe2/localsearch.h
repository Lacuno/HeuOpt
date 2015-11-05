#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <memory>
#include "kpmp_solution.h"
#include "neighborhood.h"

enum StepFunction { FIRST_IMPROVEMENT, BEST_IMPROVEMENT, RANDOM };

class LocalSearch {
    public:
	LocalSearch(uint timeLimitMin, uint timeLimitSec);
	std::shared_ptr<KPMPSolution> improve(std::shared_ptr<KPMPSolution>, std::shared_ptr<Neighborhood>, StepFunction stepFunction);

    private:
	uint timeLimitMin;
	uint timeLimitSec;
};

#endif /* LOCAL_SEARCH_H */
