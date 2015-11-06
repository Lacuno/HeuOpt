#ifndef NEIGHBORHOOD_H 
#define NEIGHBORHOOD_H

#include <memory>
#include "kpmp_solution.h"

class Neighborhood {
    public:
	Neighborhood();
	virtual ~Neighborhood() { }

	virtual std::shared_ptr<KPMPSolution> firstImprovement();
	virtual std::shared_ptr<KPMPSolution> bestImprovement();
	virtual void setCurrentSolution(std::shared_ptr<KPMPSolution>);
	virtual std::shared_ptr<KPMPSolution> randomNeighbor() = 0;

    protected:
	std::shared_ptr<KPMPSolution> currentSolution;

	virtual bool hasNextNeighbor() = 0;
	virtual std::shared_ptr<KPMPSolution> nextNeighbor() = 0;

    private:
	// true.. bestImprovement
	// false.. firstImprovement
	std::shared_ptr<KPMPSolution> improve(bool isBestImprovement);
};

#endif /* NEIGHBORHOOD_H */
