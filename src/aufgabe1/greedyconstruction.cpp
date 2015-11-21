#include <iostream>
#include <deque>
#include "utils.h"
#include "greedyconstruction.h"

using namespace std;

GreedyConstruction::GreedyConstruction(bool randomized) : 
	randomized(randomized), randomEngine((std::random_device())()), rng(0, std::numeric_limits<uint>::max()) 
{
}

shared_ptr<KPMPSolution> GreedyConstruction::construct(std::string instanceName) {
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

	// add all vertices to a deque
	std::deque<unsigned int> vertices;
	for (unsigned int i = 0; i < numVertices; i++) {
		vertices.push_back(i);
	}

	// add the first vertex into the ordering
	ordering.push_back(vertices.front());
	vertices.pop_front();

	// do while there are vertices left
	while(!vertices.empty()) {
		unsigned int v1 = ordering.back();
		int ind = -1;

		// 1. pick a vertex v that is connected to the last vertex v_l (iterate ascending / random)
		if(randomized) {
			std::vector<uint> possibleExtensions;
			for (unsigned int i = 0; i < vertices.size(); i++) {
				if (adjacencyMatrix[v1][vertices[i]]) {
					possibleExtensions.push_back(i);
				}
			}
			if(possibleExtensions.size() != 0) {
				uint randomi = rng(randomEngine) % possibleExtensions.size();	
				ind = possibleExtensions[randomi];
			}
		} else {
			for (unsigned int i = 0; i < vertices.size(); i++) {
				if (adjacencyMatrix[v1][vertices[i]]) {
					ind = i;
					break;
				}
			}
		}

		// v does not exist - place the next free vertex (or random?)
		if (ind == -1) {
			ordering.push_back(vertices.back());
			vertices.pop_back();
		}
		else {
			// v exists - place it after v_l
			ordering.push_back(vertices[ind]);
			vertices.erase(vertices.begin() + ind);
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
						minCrossing = crossings;
						minPage = p;
					}
				}
				
				// add it on the min page (if it was not found add in on the first)
				solution->addEdge({ i, j, minPage });
			}
		}
	}

	std::cout << "Crossings: " << solution->getCrossings() << std::endl;
	
	secondsneeded = Utils::endTimeMeasurement();
	//std::cout << "Done in " << secondsneeded << " seconds" << std::endl;

	
	return solution;
}
