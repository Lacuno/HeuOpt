#include <iostream>
#include <memory>
#include <boost/program_options.hpp>
#include "kpmp_instance.h"
#include "kpmp_solution.h"
#include "kpmp_solution_writer.h"
#include "constructionheuristic.h"
#include "greedyconstruction.h"
#include "orderingconstruction.h"
#include "utils.h"

void usage() {
	std::cout << "Usage: ./heuOpt -c {g | o} [-r]" << std::endl;
	std::cout << "-c: Build with construction heuristic " << std::endl;
	std::cout << "    option g: Greedy construction heuristic" << std::endl;
	std::cout << "    option o: Ordering construction heuristic (Randomization is not supported yet)" << std::endl;
	std::cout << "-r: Randomize construction heuristic" << std::endl;
}

int main(int argc, char** argv)
{	
	// Parse arguments
	namespace po = boost::program_options;	

	po::options_description desc("Arguments");
	desc.add_options()
		("help,h", "Usage: ./heuOpt -c {g | o} [-r]")
		(",c", po::value<char>(), "Build with construction heuristic: "
								 "option g : Greedy construction heuristic"
								 "option o : Ordering construction heuristic(Randomization is not supported yet)")
		(",r", "Randomize construction heuristic");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}

	bool randomize = vm.count("-r");
	char typeOfConstructionHeuristic = vm.count("-c") ? vm["-c"].as<char>() : ' ';
	
	std::shared_ptr<ConstructionHeuristic> constructor;
	switch(typeOfConstructionHeuristic) {
		case 'g': constructor = std::shared_ptr<ConstructionHeuristic>(new GreedyConstruction(randomize));
			  break;
		case 'o': constructor = std::shared_ptr<ConstructionHeuristic>(new OrderingConstruction(randomize));
			  break;
		default:  usage();
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
