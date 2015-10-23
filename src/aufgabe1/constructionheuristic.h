#ifndef CONSTRUCTION_HEURISTIC_H
#define CONSTRUCTION_HEURISTIC_H

#include <memory>
#include "kpmp_solution.h"
#include "kpmp_instance.h"

class ConstructionHeuristic {
    public:
	virtual ~ConstructionHeuristic() { }
//<<<<<<< HEAD
//	virtual std::shared_ptr<KPMPSolution> construct(KPMPInstance &instance) = 0;
//=======
	virtual std::shared_ptr<KPMPSolution> construct(std::string instanceName) = 0;
//>>>>>>> 90a5b93bdf24d47142e006fe87a0052dea1d2d16
};

#endif /* CONSTRUCTION_HEURISTIC_H */
