#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include <memory>
#include "kpmp_solution.h"

class LocalSearch {
    public:
	virtual ~LocalSearch() { }
	virtual std::shared_ptr<KPMPSolution> improve(std::shared_ptr<KPMPSolution>) = 0;
};

#endif /* LOCAL_SEARCH_H */
