#ifndef ORDERINGSHIFT_NEIGHBORHOOD_H
#define ORDERINGSHIFT_NEIGHBORHOOD_H

#include <memory>
#include "neighborhood.h"
#include "kpmp_solution.h"

class OrderingShiftNeighborhood : public Neighborhood {
    public:
	OrderingShiftNeighborhood();
	virtual ~OrderingShiftNeighborhood() { }
	virtual std::shared_ptr<KPMPSolution> randomNeighbor();
	virtual void setCurrentSolution(std::shared_ptr<KPMPSolution> newSolution);

	virtual std::shared_ptr<Neighborhood> clone();

    protected:
	virtual bool hasNextNeighbor();
	virtual std::shared_ptr<KPMPSolution> nextNeighbor();

    private:
	uint currentPos;  	// Current position in Ordering
	uint shiftTo;		// Position to shift to
};

#endif /* NEIGHBORHOOD_H */
