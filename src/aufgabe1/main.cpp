#include <iostream>
#include <memory>
#include <unistd.h> // Getopt from C Library
#include "kpmp_instance.h"
#include "kpmp_solution.h"
#include "kpmp_solution_writer.h"
#include "constructionheuristic.h"
#include "greedyconstruction.h"
#include "utils.h"

void usage() {
	std::cout << "Usage: ./heuOpt -c {g | r} [-r]" << std::endl;
	std::cout << "-c: Build with construction heuristic " << std::endl;
	std::cout << "    option g: Greedy construction heuristic" << std::endl;
	std::cout << "    option r: Rating construction heuristic" << std::endl;
	std::cout << "-r: Randomize construction heuristic" << std::endl;
}

int main(int argc, char** argv)
{	
	// Parse arguments
	int opt;
	int opterr;
	bool doConstructionHeuristic = false;
	bool randomize = false;
	char typeOfConstructionHeuristic;

	while((opt = getopt(argc, argv, "c:r")) != -1) {
		switch(opt) {
			case 'c':
				doConstructionHeuristic = true;
				typeOfConstructionHeuristic = optarg[0];
				break;
			case 'r':
				randomize = true;
				break;
			default:
				usage();
				return -1;
		}		
	}

	if(!doConstructionHeuristic) {
		usage();
		return -1;
	}
	
	std::shared_ptr<ConstructionHeuristic> constructor;
	if(typeOfConstructionHeuristic == 'g') {
		constructor = std::shared_ptr<ConstructionHeuristic>(new GreedyConstruction(randomize));
	} else if(typeOfConstructionHeuristic == 'r') {
		//TODO: Build in rating construction
	} else {
		usage();
		return -1;
	}

	for (char i = 1; i <= 10; i++) {
		std::string instanceName("instances/automatic-" + std::to_string(i) + ".txt");

		const auto& sol = constructor->construct(instanceName);


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
