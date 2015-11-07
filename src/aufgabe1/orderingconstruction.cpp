#include <iostream>
#include <algorithm>
#include "utils.h"
#include "orderingconstruction.h"

using namespace std;

OrderingConstruction::OrderingConstruction(bool randomized) : 
	randomized(randomized), randomEngine((std::random_device())()), rng(0, std::numeric_limits<uint>::max()) 
{
}

shared_ptr<KPMPSolution> OrderingConstruction::construct(std::string instanceName) {
	std::cout << ">>>> Reading instance: " << instanceName << std::endl;
	Utils::startTimeMeasurement();
	const auto instance = std::unique_ptr<KPMPInstance>(KPMPInstance::readInstance(instanceName));
	double secondsneeded = Utils::endTimeMeasurement();
	std::cout << "Reading complete in " << secondsneeded << " seconds" << std::endl;

	const auto adjacencyMatrix = instance->getAdjacencyMatrix();
	const unsigned int numVertices = instance->getNumVertices();

	shared_ptr<KPMPSolution> solution(new KPMPSolution(instance->getK(), numVertices));

	std::cout << "Constructing..." << std::endl;
	Utils::startTimeMeasurement();

	// create the ordering
	std::vector<unsigned int> ordering;

	std::vector<bool> alreadyInOrdering;
	for (int i = 0; i < numVertices; i++) {
		alreadyInOrdering.push_back(false);
	}

	vector<uint> degrees;
	for (uint i = 0; i < numVertices; i++) {
		degrees.push_back(instance->getAdjacencyList()[i].size());
	}


	// do while there are vertices left
	while(ordering.size() != numVertices) {
		int maxdegree = -1;
		int vertexChosen = -1;
		for(uint i = 0; i < alreadyInOrdering.size(); i++) {
			if(!alreadyInOrdering[i]) {
				int degree = degrees[i];
				if(maxdegree < degree) {
					maxdegree = degree;
					vertexChosen = i;
				}
			}
		}
		ordering.push_back(vertexChosen);
		alreadyInOrdering[vertexChosen] = true;
		
		vector<pair<uint, uint>> neighborsWithDegrees; // tuple<degree, neighbor>
		for(uint i = 0; i < numVertices; i++) {
			if(!alreadyInOrdering[i] && adjacencyMatrix[vertexChosen][i]) {
				neighborsWithDegrees.push_back({degrees[i], i});
			}
		}	

		std::sort(neighborsWithDegrees.begin(), neighborsWithDegrees.end());
	
		for(pair<uint, uint> toInsert : neighborsWithDegrees) {
			ordering.push_back(toInsert.second);
			alreadyInOrdering[toInsert.second] = true;
		}
	}

	// set ordering
	solution->setOrdering(ordering);

	// add all edges to the solution
	for (unsigned int i = 0; i < numVertices; i++) {
		for (unsigned int j = i; j < numVertices; j++) {
			if (adjacencyMatrix[i][j]) {
				// search for a page where we can add the edge without crossings
				unsigned int minCrossing = numVertices * numVertices;
				unsigned int minPage = 0;

				for (unsigned int p = 0; p < instance->getK(); p++) {
					unsigned int crossings = solution->getEdgeCrossings({ i, j, p });

					if (crossings == 0) {
						minPage = p;
						break;
					}
					else if (crossings < minCrossing) {
						minPage = p;
					}
				}
				
				// add it on the min page (if it was not found add in on the first)
				solution->addEdge({ i, j, minPage });
			}
		}
	}

	std::cout << "Crossings : " << solution->getCrossings() << std::endl;
	
	secondsneeded = Utils::endTimeMeasurement();
	std::cout << "Done in " << secondsneeded << " seconds" << std::endl;

	
	return solution;
}
