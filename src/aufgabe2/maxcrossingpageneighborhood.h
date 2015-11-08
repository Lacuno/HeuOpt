#ifndef MAXCROSSINPAGE_NEIGHBORHOOD_H
#define MAXCROSSINPAGE_NEIGHBORHOOD_H

#include <memory>
#include "neighborhood.h"
#include "kpmp_solution.h"

class MaxCrossingPageNeighborhood : public Neighborhood {
    public:
		MaxCrossingPageNeighborhood();
	virtual ~MaxCrossingPageNeighborhood() { }
	virtual std::shared_ptr<KPMPSolution> randomNeighbor();
	virtual void setCurrentSolution(std::shared_ptr<KPMPSolution> newSolution);

    protected:
	virtual bool hasNextNeighbor();
	virtual std::shared_ptr<KPMPSolution> nextNeighbor();

    private:

		std::vector<Edge> maxCrossingsEdges;

		uint currentMaxIdx;
		uint currentPage;

		bool firstIteration;

	
};

#endif /* NEIGHBORHOOD_H */
