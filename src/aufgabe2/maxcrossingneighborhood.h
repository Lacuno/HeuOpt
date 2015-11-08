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
		// we iterate:
		//   for all v1 shifts
		//     for all v2 shifts
		//       for all pages
		//         for all max edges

		// the offset is the position of the max edges vertices in the ordering - we want to iterate over all possible combinations:
		// ++----
		// +-+---
		// +--+--
		// +---+-
		// +----+
		// -++---
		// -+-+--
		// etc

		std::vector<Edge> maxCrossingsEdges;
		uint currentIdx;
		uint currentPage;
		uint currentShiftV1;
		uint currentShiftV2;
		

		bool firstIteration;

	
};

#endif /* NEIGHBORHOOD_H */
