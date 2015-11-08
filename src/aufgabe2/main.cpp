#include <iostream>
#include <memory>
#include <boost/program_options.hpp>
#include "kpmp_instance.h"
#include "kpmp_solution.h"
#include "kpmp_solution_writer.h"
#include "constructionheuristic.h"
#include "greedyconstruction.h"
#include "orderingconstruction.h"
#include "localsearch.h"
#include "neighborhood.h"
#include "orderingshiftneighborhood.h"
#include "edgeshiftneighborhood.h"
#include "maxcrossingpageneighborhood.h"
#include "minmaxcrossingorderingneighborhood.h"
#include "utils.h"

void usage() {
	std::cout << "Usage: ./heuOpt -c {g | o} [-r] -l {sho | moe} -s {f | b | r}" << std::endl;
	std::cout << "-c: Build with construction heuristic " << std::endl;
	std::cout << "    option g: Greedy construction heuristic" << std::endl;
	std::cout << "    option o: Ordering construction heuristic (Randomization is not supported yet)" << std::endl;
	std::cout << "-r: Randomize construction heuristic" << std::endl;
	std::cout << "-l: Improve with local search" << std::endl;
	std::cout << "    option sho: Shift ordering neighborhood" << std::endl;
	std::cout << "    option moe: move edge to other page neighborhood" << std::endl;
	std::cout << "    option map: move max crossing edges to other pages" << std::endl;
	std::cout << "    option mmc: shift max crossing vertices to min crossing vertices" << std::endl;
	std::cout << "-s: Step function for local search" << std::endl;
	std::cout << "    option f: First improvement strategy" << std::endl;
	std::cout << "    option b: Best improvement strategy" << std::endl;
	std::cout << "    option f: Random strategy" << std::endl;
}

int main(int argc, char** argv)
{	
	// Parse arguments
	namespace po = boost::program_options;	

	po::options_description desc("Arguments");
	desc.add_options()
		("help,h", "Usage: ./heuOpt -c {g | o} [-r] -l {sho}")
		(",c", po::value<char>(), "Build with construction heuristic: "
								 "option g : Greedy construction heuristic"
								 "option o : Ordering construction heuristic(Randomization is not supported yet)")
		(",r", "Randomize construction heuristic")
		(",l", po::value<std::string>(), "Improve with local search"
		      				"option sho: Shift ordering neighborhood")
		(",s", po::value<char>());
	po::variables_map vm;
	try {
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);
	} catch(boost::exception &e) {
		usage();
		return -1;
	}

	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}

	bool randomize = vm.count("-r");
	char typeOfConstructionHeuristic = vm.count("-c") ? vm["-c"].as<char>() : ' ';
	std::string typeOfLocalSearch = vm.count("-l") ? vm["-l"].as<std::string>() : "";
	char typeOfStepFunction = vm.count("-s") ? vm["-s"].as<char>() : ' ';


	std::shared_ptr<ConstructionHeuristic> constructor;
	switch (typeOfConstructionHeuristic) {
	case 'g': constructor = std::shared_ptr<ConstructionHeuristic>(new GreedyConstruction(randomize));
		break;
	case 'o': constructor = std::shared_ptr<ConstructionHeuristic>(new OrderingConstruction(randomize));
		break;
	default:  usage();
		return -1;
	}

	std::shared_ptr<LocalSearch> improver = std::shared_ptr<LocalSearch>(new LocalSearch(1, 0));	
	std::shared_ptr<Neighborhood> neighborhood;
	if(typeOfLocalSearch == "sho") {
		neighborhood = std::shared_ptr<Neighborhood>(new OrderingShiftNeighborhood());
	} else if(typeOfLocalSearch == "moe") {
		neighborhood = std::shared_ptr<Neighborhood>(new EdgeShiftNeighborhood());
	} else if (typeOfLocalSearch == "map") {
		neighborhood = std::shared_ptr<Neighborhood>(new MaxCrossingPageNeighborhood());
	} else if (typeOfLocalSearch == "mmc") {
		neighborhood = std::shared_ptr<Neighborhood>(new MinMaxCrossingOrderingNeighborhood());
	} else {
		usage();
		return -1;
	}

	StepFunction stepFunction;
	switch(typeOfStepFunction) {
		case 'f': stepFunction = FIRST_IMPROVEMENT;
			  break;
		case 'b': stepFunction = BEST_IMPROVEMENT;
			  break;
		case 'r': stepFunction = RANDOM;
			  break;
		default:  usage();
			  return -1;
	}

	std::shared_ptr<Neighborhood> neighborhood2 = std::shared_ptr<Neighborhood>(new OrderingShiftNeighborhood());;
	for (char i = 6; i <= 6; i++) {
		std::string instanceName("instances/automatic-" + std::to_string(i) + ".txt");

		const auto& sol = constructor->construct(instanceName);
		std::cout << sol->getCrossings() << std::endl;

		neighborhood->setCurrentSolution(sol);
		auto newsol = improver->improve(sol, neighborhood, stepFunction);
		
		newsol->recomputeCrossings();
		std::cout << newsol->getCrossings() << std::endl;

		//newsol->printCrossingMatrix(); 

		// write solution                                             
		KPMPSolutionWriter solutionWriter(newsol->getK());
		std::cout << "Writing solution..." << std::endl;

		solutionWriter.setSpineOrder(newsol->getOrdering());
		const auto& edges = newsol->getEdges();
		for (const auto& edge : edges) {
			solutionWriter.addEdgeOnPage(edge.v1, edge.v2, edge.page);
		}
		solutionWriter.write("instances/result-" + std::to_string(i) + ".txt");
		std::cout << "Done!" << std::endl;

		std::cout << std::endl;
	}

	return 0; 
}
