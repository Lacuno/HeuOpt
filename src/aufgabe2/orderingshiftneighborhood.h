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

    protected:
	virtual bool hasNextNeighbor();
	virtual std::shared_ptr<KPMPSolution> nextNeighbor();

    private:
	uint currentPos;  	// Current position in Ordering
	uint shiftTo;		// Position to shift to

	std::shared_ptr<KPMPSolution> generateNewNeighbor(uint elem, uint shift);
};

#endif /* NEIGHBORHOOD_H */
