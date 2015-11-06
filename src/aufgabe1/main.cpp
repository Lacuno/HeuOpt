#include <iostream>
#include <memory>
//#include <boost/program_options.hpp>
#include "kpmp_instance.h"
#include "kpmp_solution.h"
#include "kpmp_solution_writer.h"
#include "constructionheuristic.h"
#include "greedyconstruction.h"
#include "orderingconstruction.h"
#include "utils.h"

int main(int argc, char** argv)
{	
	// Parse arguments
	/*
	namespace po = boost::program_options;	

	po::options_description desc("Arguments");
	desc.add_options()
		("help,h", "Usage: ./heuOpt -c {g | o} [-r]")
		("c", po::value<char>(), "Build with construction heuristic: "
								 "option g : Greedy construction heuristic"
								 "option o : Ordering construction heuristic(Randomization is not supported yet)")
		("r", "Randomize construction heuristic");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}

	bool randomize = vm.count("r");
	char typeOfConstructionHeuristic = vm.count("c") ? vm["c"].as<char>() : ' ';
	*/
	bool randomize = false;
	char typeOfConstructionHeuristic = 'g';

	std::shared_ptr<ConstructionHeuristic> constructor;
	if(typeOfConstructionHeuristic == 'g') {
		constructor = std::shared_ptr<ConstructionHeuristic>(new GreedyConstruction(randomize));
	} else if(typeOfConstructionHeuristic == 'o') {
		constructor = std::shared_ptr<ConstructionHeuristic>(new OrderingConstruction(randomize));
	} else {
		//cout << desc << "\n";
		return -1;
	}

	for (char i = 1; i <= 10; i++) {
		std::string instanceName("instances/automatic-" + std::to_string(i) + ".txt");

		const auto& sol = constructor->construct(instanceName);


		// write solution
		std::cout << "Writing solution..." << std::endl;

		KPMPSolutionWriter solutionWriter(sol->getK());
		solutionWriter.setSpineOrder(sol->getOrdering());

		const auto& edges = sol->getEdges();
		for (const auto& edge : edges) {
			solutionWriter.addEdgeOnPage(edge.v1, edge.v2, edge.page);
		}

		solutionWriter.write("instances/result-" + std::to_string(i) + ".txt");
		std::cout << "Done!" << std::endl;

		std::cout << std::endl;
	}

	return 0; 
}
