#ifndef GREEDY_CONSTRUCTION_H_
#define GREEDY_CONSTRUCTION_H_

#include "constructionheuristic.h"

class GreedyConstruction : public ConstructionHeuristic {
    public:
	virtual std::shared_ptr<KPMPSolution> construct();
};

#endif /* GREEDY_CONSTRUCTION_H_ */
