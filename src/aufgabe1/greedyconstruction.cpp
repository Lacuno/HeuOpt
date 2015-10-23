#include "greedyconstruction.h"

using namespace std;

shared_ptr<KPMPSolution> GreedyConstruction::construct() {
	shared_ptr<KPMPSolution> p(new KPMPSolution(1,1));
	return p;
}


