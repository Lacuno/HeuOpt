#include <iostream>
#include <memory>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
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
#include "variableneighborhooddescent.h"
#include "variableneighborhoodsearch.h"
#include "utils.h"

void usage() {
	std::cout << "Usage: ./heuOpt -c {g | o} [-r] {-l {sho | moe | map | mmc} -s {f | b | r}}* -i <instance-name>" << std::endl;
	std::cout << "-c: Build with construction heuristic " << std::endl;
	std::cout << "    option g: Greedy construction heuristic" << std::endl;
	std::cout << "    option o: Ordering construction heuristic (Randomization is not supported yet)" << std::endl;
	std::cout << "-r: Randomize construction heuristic" << std::endl;
	std::cout << "-l: Improve with local search. Can be specified multiple times to perform a vnd search" << std::endl;
	std::cout << "    option sho: Shift ordering neighborhood" << std::endl;
	std::cout << "    option moe: move edge to other page neighborhood" << std::endl;
	std::cout << "    option map: move max crossing edges to other pages" << std::endl;
	std::cout << "    option mmc: shift max crossing vertices to min crossing vertices" << std::endl;
	std::cout << "-s: Step function for local search" << std::endl;
	std::cout << "    option f: First improvement strategy" << std::endl;
	std::cout << "    option b: Best improvement strategy" << std::endl;
	std::cout << "    option f: Random strategy" << std::endl;
	std::cout << "-i: Specify the instance you want the algorithm to run on" << std::endl;
	std::cout << "    Default is automatic-6" << std::endl;
	std::cout << "-v: If -l was chosen multiple times, perform a VNS instead of a VND" << std::endl;
}

bool is_file_exist(const char *fileName)
{
	return boost::filesystem::exists(fileName);
}

std::string getFilename(const std::string& str)
{
  std::size_t found = str.find_last_of("/\\");
  return str.substr(found+1);
}  

int main(int argc, char** argv)
{	
	// Parse arguments
	namespace po = boost::program_options;	

	po::options_description desc("Arguments");
	std::vector<std::string> neighborhoods;
	std::vector<char> stepFunctions;
	desc.add_options()
		("help,h", "Usage")
		(",c", po::value<char>(), "Build with construction heuristic")
		(",r", "Randomize construction heuristic")
		(",l", po::value<std::vector<string>>(&neighborhoods), "Improve with local search")
		(",s", po::value<std::vector<char>>(&stepFunctions), "Defines the step function for the local search")
		(",i", po::value<std::string>(), "Defines the instance that will be used")
		(",v", "Tags the search as VNS search");
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
//	std::string typeOfLocalSearch = vm.count("-l") ? vm["-l"].as<std::string>() : "";
//	char typeOfStepFunction = vm.count("-s") ? vm["-s"].as<char>() : ' ';
	std::string instanceName = vm.count("-i") ? vm["-i"].as<std::string>() : "instances/automatic-6.txt";
	bool vns = vm.count("-v");

	if(neighborhoods.size() == 0) {
		usage();
		return -1;
	}

	std::shared_ptr<ConstructionHeuristic> constructor;
	switch (typeOfConstructionHeuristic) {
	case 'g': constructor = std::shared_ptr<ConstructionHeuristic>(new GreedyConstruction(randomize));
		break;
	case 'o': constructor = std::shared_ptr<ConstructionHeuristic>(new OrderingConstruction(randomize));
		break;
	default: 
		  cout << typeOfConstructionHeuristic << " aaaaaaa" << endl;
		cout << "Test" << endl;
		  usage();
		return -1;
	}

	std::vector<LocalSearchBundle> localSearches;
	for(uint i = 0; i < neighborhoods.size(); i++) {
		std::shared_ptr<LocalSearch> localSearch = std::shared_ptr<LocalSearch>(new LocalSearch(14, 0));	
		std::shared_ptr<Neighborhood> neighborhood;

		std::string neighborhoodParam = neighborhoods[i];
		if(neighborhoodParam == "sho") {
			neighborhood = std::shared_ptr<Neighborhood>(new OrderingShiftNeighborhood());
		} else if(neighborhoodParam == "moe") {
			neighborhood = std::shared_ptr<Neighborhood>(new EdgeShiftNeighborhood());
		} else if (neighborhoodParam == "map") {
			neighborhood = std::shared_ptr<Neighborhood>(new MaxCrossingPageNeighborhood());
		} else if (neighborhoodParam == "mmc") {
			neighborhood = std::shared_ptr<Neighborhood>(new MinMaxCrossingOrderingNeighborhood());
		} else {
			usage();
			return -1;
		}

		StepFunction stepFunction;
		switch(stepFunctions[i]) {
			case 'f': stepFunction = FIRST_IMPROVEMENT;
				  break;
			case 'b': stepFunction = BEST_IMPROVEMENT;
				  break;
			case 'r': stepFunction = RANDOM;
				  break;
			default:  usage();
				  return -1;
		}

		LocalSearchBundle lsb;
		lsb.localSearch = localSearch;
		lsb.neighborhood= neighborhood;
		lsb.stepFunction= stepFunction;
		localSearches.push_back(lsb);
	}

	// Algorithm
	const auto& sol = constructor->construct(instanceName);
	for(LocalSearchBundle lsb : localSearches) {
		lsb.neighborhood->setCurrentSolution(sol);
	}

	std::shared_ptr<KPMPSolution> newsol;
	if(localSearches.size() == 1) {
		std::cout << "Using Local Search for improvement!" << std::endl;
		newsol = localSearches[0].localSearch->improve(sol, localSearches[0].neighborhood, localSearches[0].stepFunction);
	} else if(!vns) {
		std::cout << "Using VND for improvement!" << std::endl;
		VariableNeighborhoodDescent vnd(sol);
		newsol = vnd.improve(localSearches);
	} else {
		std::cout << "Using VNS for improvement!" << std::endl;
		VariableNeighborhoodSearch vns(sol);
		newsol = vns.improve(localSearches);
	}

	std::cout << "Num Crossings: " << newsol->getCrossings() << std::endl;

	// write solution                                             
	KPMPSolutionWriter solutionWriter(newsol->getK());
	std::cout << "Writing solution..." << std::endl;

	solutionWriter.setSpineOrder(newsol->getOrdering());
	const auto& edges = newsol->getEdges();
	for (const auto& edge : edges) {
		solutionWriter.addEdgeOnPage(edge.v1, edge.v2, edge.page);
	}
	std::string path = "instances/result/" + getFilename(instanceName);
	solutionWriter.write(path);
	std::cout << "Done!" << std::endl;

	std::cout << std::endl;

	return 0; 
}
