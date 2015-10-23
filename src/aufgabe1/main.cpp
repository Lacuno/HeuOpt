#include <iostream>
#include <memory>
#include "kpmp_instance.h"
#include "kpmp_solution.h"
#include "kpmp_solution_writer.h"
#include "constructionheuristic.h"
#include "greedyconstruction.h"
#include "utils.h"

int main()
{	
	for (char i = 1; i <= 1; i++) {
		std::string instanceName("instances/automatic-" + std::to_string(i) + ".txt");

		std::cout << ">>>> Reading instance: " << instanceName << std::endl;
		Utils::startTimeMeasurement();
		const auto instance = std::unique_ptr<KPMPInstance>(KPMPInstance::readInstance(instanceName));
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
				if (adjacencyMatrix[i][j]) {
					sol.addEdge({ i, j, 0 });
					edgeNum++;
				}
			}
		}
		secondsneeded = Utils::endTimeMeasurement();
		std::cout << "Filling solution with data complete in " << secondsneeded << " seconds" << std::endl;

		// TODO process

		//sol.setOrdering({9,8,7,6,5,4,3,2,1,0});


		// write solution
		std::cout << "Writing solution..." << std::endl;

		KPMPSolutionWriter solutionWriter(k);
		solutionWriter.setSpineOrder(sol.getOrdering());

		for (unsigned int p = 0; p < k; p++) {
			const auto& edges = sol.getEdgesFromPage(p);

			for (const auto& edge : edges) {
				solutionWriter.addEdgeOnPage(edge.v1, edge.v2, p);
			}
		}

		solutionWriter.write("instances/result-" + std::to_string(i) + ".txt");
		std::cout << "Done!" << std::endl;

		std::cout << std::endl;
	}

	return 0; 
}
