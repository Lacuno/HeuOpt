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
	GreedyConstruction gc;

	for (char i = 1; i <= 10; i++) {
		std::string instanceName("instances/automatic-" + std::to_string(i) + ".txt");

		const auto& sol = gc.construct(instanceName);


		// write solution
		std::cout << "Writing solution..." << std::endl;

		KPMPSolutionWriter solutionWriter(sol->getK());
		solutionWriter.setSpineOrder(sol->getOrdering());

		for (unsigned int p = 0; p < sol->getK(); p++) {
			const auto& edges = sol->getEdgesFromPage(p);

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
