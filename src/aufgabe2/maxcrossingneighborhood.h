#ifndef MAXCROSSING_NEIGHBORHOOD_H
#define MAXCROSSING_NEIGHBORHOOD_H

#include <memory>
#include "neighborhood.h"
#include "kpmp_solution.h"

class MaxCrossingNeighborhood : public Neighborhood {
    public:
		MaxCrossingNeighborhood();
	virtual ~MaxCrossingNeighborhood() { }
	virtual std::shared_ptr<KPMPSolution> randomNeighbor();
	virtual void setCurrentSolution(std::shared_ptr<KPMPSolution> newSolution);

    protected:
	virtual bool hasNextNeighbor();
	virtual std::shared_ptr<KPMPSolution> nextNeighbor();

    private:
		Edge maxCrossingsEdge;
	
};

#endif /* NEIGHBORHOOD_H */
