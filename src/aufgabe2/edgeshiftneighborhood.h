#ifndef EDGE_SHIFT_NEIGHBORHOOD_H 
#define EDGE_SHIFT_NEIGHBORHOOD_H

#include <memory>
#include <random>
#include "kpmp_solution.h"

class EdgeShiftNeighborhood {
    public:
	EdgeShiftNeighborhood();
	virtual ~EdgeShiftNeighborhood() { }
	virtual std::shared_ptr<KPMPSolution> randomNeighbor();

    protected:
	virtual bool hasNextNeighbor();
	virtual std::shared_ptr<KPMPSolution> nextNeighbor();

    private:
	uint currentPage;
	uint currentEdge;
};

#endif /* EDGE_SHIFT_NEIGHBORHOOD_H*/
