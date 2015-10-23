#ifndef GREEDY_CONSTRUCTION_H_
#define GREEDY_CONSTRUCTION_H_

#include "constructionheuristic.h"
#include "kpmp_instance.h"

class GreedyConstruction : public ConstructionHeuristic {
    public:
//<<<<<<< HEAD
//	virtual std::shared_ptr<KPMPSolution> construct(KPMPInstance &instance);
//=======
	virtual std::shared_ptr<KPMPSolution> construct(std::string instanceName);
};

#endif /* GREEDY_CONSTRUCTION_H_ */
