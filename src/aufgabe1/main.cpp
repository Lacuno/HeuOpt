#include <iostream>
#include <memory>
#include "kpmp_instance.h"
#include "kpmp_solution.h"

int main()
{
	const auto instance = std::unique_ptr<KPMPInstance>(KPMPInstance::readInstance("instances/manual-1.txt"));
	const auto adjacencyMatrix = instance->getAdjacencyMatrix();
	const unsigned int numVertices = instance->getNumVertices();
	const unsigned int k = instance->getK();

    KPMPSolution sol(k, numVertices);
    
	for (unsigned int i = 0; i < numVertices; i++) {
		for (unsigned int j = 0; j < numVertices; j++) {
			if(adjacencyMatrix[i][j]) {
				sol.addEdge(0, { i, j });
			}
		}
	}
   
    std::cout << "computing crossings..." << std::endl; 
    std::cout << sol.computeCrossings() << std::endl;
    

    return 0; 
}
