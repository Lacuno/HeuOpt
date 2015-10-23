#ifndef GREEDY_CONSTRUCTION_H_
#define GREEDY_CONSTRUCTION_H_

#include <random>
#include "constructionheuristic.h"
#include "kpmp_instance.h"

class GreedyConstruction : public ConstructionHeuristic {
    private:
	bool randomized;
	std::default_random_engine randomEngine;
	std::uniform_int_distribution<uint> rng;
	
    public:
	GreedyConstruction(bool randomized);
	virtual std::shared_ptr<KPMPSolution> construct(std::string instanceName);
};

#endif /* GREEDY_CONSTRUCTION_H_ */
