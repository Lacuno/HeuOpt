#ifndef ORDERING_CONSTRUCTION_H_
#define RDERING_CONSTRUCTION_H_

#include <random>
#include "constructionheuristic.h"
#include "kpmp_instance.h"

class OrderingConstruction : public ConstructionHeuristic {
    private:
	bool randomized;
	std::default_random_engine randomEngine;
	std::uniform_int_distribution<uint> rng;
	
    public:
	OrderingConstruction(bool randomized);
	virtual std::shared_ptr<KPMPSolution> construct(std::string instanceName);
};

#endif /* ORDERING_CONSTRUCTION_H_ */
