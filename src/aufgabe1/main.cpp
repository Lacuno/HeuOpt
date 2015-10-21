#include <iostream>
#include <memory>
#include "kpmp_instance.h"
#include "kpmp_solution.h"
#include "utils.h"

int main()
{	
	std::cout << "Reading instance" << std::endl;
	Utils::startTimeMeasurement();
	const auto instance = std::unique_ptr<KPMPInstance>(KPMPInstance::readInstance("instances/automatic-9.txt"));
	double secondsneeded = Utils::endTimeMeasurement();
	std::cout << "Reading complete in " << secondsneeded << " seconds" << std::endl;

	const auto adjacencyMatrix = instance->getAdjacencyMatrix();
	const unsigned int numVertices = instance->getNumVertices();
	const unsigned int k = instance->getK();

    KPMPSolution sol(k, numVertices);
    
    	std::cout << "Filling solution with data" << std::endl;
	Utils::startTimeMeasurement();
	for (unsigned int i = 0; i < numVertices; i++) {
		for (unsigned int j = i; j < numVertices; j++) {
			if(adjacencyMatrix[i][j]) {
				sol.addEdge(0, { i, j });
			}
		}
	}
	secondsneeded = Utils::endTimeMeasurement();
	std::cout << "Filling solution with data complete in " << secondsneeded << " seconds" << std::endl;
   
	Utils::startTimeMeasurement();
    std::cout << "computing crossings..." << std::endl; 
    std::cout << sol.computeCrossings() << std::endl;
	secondsneeded = Utils::endTimeMeasurement();
	std::cout << "Done: " << secondsneeded << " seconds needed" << std::endl;

    

    return 0; 
}
