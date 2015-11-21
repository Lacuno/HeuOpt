#ifndef EDGE_SHIFT_NEIGHBORHOOD_H 
#define EDGE_SHIFT_NEIGHBORHOOD_H

#include "neighborhood.h"
#include <memory>
#include "kpmp_solution.h"

class EdgeShiftNeighborhood : public Neighborhood {
    public:
	EdgeShiftNeighborhood();
	virtual ~EdgeShiftNeighborhood() { }
	virtual std::shared_ptr<KPMPSolution> randomNeighbor();
	virtual void setCurrentSolution(std::shared_ptr<KPMPSolution> newSolution);

	virtual std::shared_ptr<Neighborhood> clone();

    protected:
	virtual bool hasNextNeighbor();
	virtual std::shared_ptr<KPMPSolution> nextNeighbor();

    private:
	uint currentPage;
	uint shiftToPage;
	uint currentEdgeV1;
	uint currentEdgeV2;

	std::shared_ptr<KPMPSolution> generateNewNeighbor(uint shiftToPage, Edge& edge);
};

#endif /* EDGE_SHIFT_NEIGHBORHOOD_H*/
