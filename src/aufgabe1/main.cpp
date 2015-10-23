#include <iostream>
#include <memory>
#include "kpmp_instance.h"
#include "kpmp_solution.h"
#include "constructionheuristic.h"
#include "greedyconstruction.h"
#include "utils.h"

int main()
{	
	std::cout << "Reading instance" << std::endl;
	Utils::startTimeMeasurement();
	const auto instance = std::unique_ptr<KPMPInstance>(KPMPInstance::readInstance("instances/manual-ordering.txt"));
	double secondsneeded = Utils::endTimeMeasurement();
	std::cout << "Reading complete in " << secondsneeded << " seconds" << std::endl;
	GreedyConstruction gc;


	const auto adjacencyMatrix = instance->getAdjacencyMatrix();
	const unsigned int numVertices = instance->getNumVertices();
	const unsigned int k = instance->getK();

	KPMPSolution sol(k, numVertices);
	std::cout << "Filling solution with data" << std::endl;
	Utils::startTimeMeasurement();

	unsigned int edgeNum = 0;

	for (unsigned int i = 0; i < numVertices; i++) {
		for (unsigned int j = i; j < numVertices; j++) {
			if(adjacencyMatrix[i][j]) {
				sol.addEdge({ i, j, 0 });
				edgeNum++;
			}
		}
	}

	secondsneeded = Utils::endTimeMeasurement();
	std::cout << "Filling solution with data complete in " << secondsneeded << " seconds" << std::endl;
   
	std::cout << sol.getCrossings() << " crossings!" << std::endl;

	return 0; 
}
