#ifndef MINMAXCROSSINGORDERING_NEIGHBORHOOD_H
#define MINMAXCROSSINGORDERING_NEIGHBORHOOD_H

#include <memory>
#include "neighborhood.h"
#include "kpmp_solution.h"

class MinMaxCrossingOrderingNeighborhood : public Neighborhood {
    public:
		MinMaxCrossingOrderingNeighborhood();
	virtual ~MinMaxCrossingOrderingNeighborhood() { }
	virtual std::shared_ptr<KPMPSolution> randomNeighbor();
	virtual void setCurrentSolution(std::shared_ptr<KPMPSolution> newSolution);

    protected:
	virtual bool hasNextNeighbor();
	virtual std::shared_ptr<KPMPSolution> nextNeighbor();

    private:

		std::vector<Edge> minCrossingsEdges;
		std::vector<Edge> maxCrossingsEdges;

		uint currentMinIdx;
		uint currentMaxIdx;
		uint currentPage;		
		bool currentFlipped; // ordering is taken from a min edge and applied to a max edge. flipped defines the correspondence (x1 -> y1 or x1 -> y2)

		bool firstIteration;

	
};

#endif /* NEIGHBORHOOD_H */
