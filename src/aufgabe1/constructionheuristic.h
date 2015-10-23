#ifndef CONSTRUCTION_HEURISTIC_H
#define CONSTRUCTION_HEURISTIC_H

#include <memory>
#include "kpmp_solution.h"

class ConstructionHeuristic {
    public:
	virtual ~ConstructionHeuristic() { }
	virtual std::shared_ptr<KPMPSolution> construct() = 0;
};

#endif /* CONSTRUCTION_HEURISTIC_H */
