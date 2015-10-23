#include <iostream>
#include <deque>
#include "utils.h"
#include "greedyconstruction.h"

using namespace std;

shared_ptr<KPMPSolution> GreedyConstruction::construct(std::string instanceName) {
	std::cout << ">>>> Reading instance: " << instanceName << std::endl;
	Utils::startTimeMeasurement();
	const auto instance = std::unique_ptr<KPMPInstance>(KPMPInstance::readInstance(instanceName));
	double secondsneeded = Utils::endTimeMeasurement();
	std::cout << "Reading complete in " << secondsneeded << " seconds" << std::endl;

	const auto adjacencyMatrix = instance->getAdjacencyMatrix();
	const unsigned int numVertices = instance->getNumVertices();
	const unsigned int k = instance->getK();

	shared_ptr<KPMPSolution> solution(new KPMPSolution(k, numVertices));

	std::cout << "Constructing..." << std::endl;
	Utils::startTimeMeasurement();

	// create the ordering
	std::vector<unsigned int> ordering;

	// add all vertices to a deque
	std::deque<unsigned int> vertices;
	for (int i = 0; i < numVertices; i++) {
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
		for (unsigned int i = 0; i < vertices.size(); i++) {
			if (adjacencyMatrix[v1][vertices[i]]) {
				ind = i;
				break;
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

	// add all edges to the solution
	for (unsigned int i = 0; i < numVertices; i++) {
		for (unsigned int j = i; j < numVertices; j++) {
			if (adjacencyMatrix[i][j]) {
				solution->addEdge({ i, j, 0 }, true);
			}
		}
	}

	std::cout << "Crossings without ordering: " << solution->getCrossings() << std::endl;
	solution->setOrdering(ordering);
	std::cout << "Crossings with ordering: " << solution->getCrossings() << std::endl;
	
	secondsneeded = Utils::endTimeMeasurement();
	std::cout << "Done in " << secondsneeded << " seconds" << std::endl;

	
	return solution;
}
//#include <tuple>
//#include <queue>
//#include <vector>
//#include <deque>
//#include "utils.h"
//#include "greedyconstruction.h"
//
//
//using namespace std;
//
////shared_ptr<KPMPSolution> GreedyConstruction::construct(KPMPInstance &instance) {
////	shared_ptr<KPMPSolution> solution(new KPMPSolution(instance.getK(), instance.getNumVertices()));
////	
////	bool** adjacencyMatrix = instance.getAdjacencyMatrix();
////   	const vector<vector<uint>> &adjacencyList = instance.getAdjacencyList();
////
//////	vector<bool> visited;
//////	for(uint i = 0; i < instance.getNumVertices(); i++) {
//////		visited.push_back(false);
//////	}
//////
//////	vector<uint> ordering; 
//////	vector<uint> vertexToOrdering;
//// 	vector<tuple<uint, uint, uint>> triples;
////
////	// Triangle search
////	for(uint i = 0; i < instance.getNumVertices(); i++) {
////		for(uint j = i; j < instance.getNumVertices(); j++) {
////			if(adjacencyMatrix[i][j]) {
////				for(uint k = j; k < instance.getNumVertices(); k++) {
////					if(adjacencyMatrix[j][k] && adjacencyMatrix[k][i]) {
////						// Triangle found
////						tuple<uint, uint, uint> triple {i, j, k};
////						triples.push_back(triple);
////					}
////				}
////			}
////		}
////	}
////
////	vector<uint> ordering;
////	vector<uint> containedInOrdering;
////	for(uint i = 0; i < instance.getNumVertices(); i++) {
////		containedInOrdering.push_back(false);
////	}
////
////	// Find neighbor triples
////	auto insertToOrdering = [&](uint toInsert, uint beforeElement, bool before) {
////		if(!containedInOrdering[toInsert]) {
////			auto pos = find(ordering.begin(), ordering.end(), beforeElement);
////
////			if(before) {
////				ordering.insert(pos, toInsert);	
////			} else {
////				ordering.insert(pos+1, toInsert);
////			}
////			containedInOrdering[toInsert] = true;
////		}
////	};
////
////	auto compareTuples = [&](tuple<uint, uint, uint> &t1, tuple<uint, uint, uint> &t2) {
////		if(get<0>(t1) == get<0>(t2)) {
////			// Ordering: t2(1), t2(2), t1(0), t1(1), t1(2)
////			insertToOrdering(get<1>(t2), get<2>(t2), true);
////			insertToOrdering(get<2>(t2), get<0>(t1), true);
////			insertToOrdering(get<0>(t1), get<1>(t1), true);
////			insertToOrdering(get<1>(t1), get<2>(t1), true);
////			insertToOrdering(get<2>(t1), get<1>(t1), false);
////			return;
////		}
////		// TODO
////		if(get<1>(t1) == get<0>(t2)) {
////			// Ordering: t1(0), t1(2), t1(1), t2(1), t2(2)
////			insertToOrdering(get<0>(t1), get<2>(t1), true);
////			insertToOrdering(get<2>(t1), get<1>(t1), true);
////			insertToOrdering(get<1>(t1), get<1>(t2), true);
////			insertToOrdering(get<1>(t2), get<2>(t2), true);
////			insertToOrdering(get<2>(t2), get<1>(t2), false);
////			return;
////		}
////		if(get<2>(t1) == get<0>(t2)) {
////			// Ordering: t1(0), t1(1), t1(2), t2(1), t1(2)
////			insertToOrdering(get<1>(t2), get<2>(t2), true);
////			insertToOrdering(get<2>(t2), get<0>(t1), true);
////			insertToOrdering(get<0>(t1), get<1>(t2), true);
////			insertToOrdering(get<1>(t1), get<2>(t2), true);
////			insertToOrdering(get<2>(t1), get<1>(t2), false);
////		}
////	};
////
////
////	for(uint i = 0; i < triples.size(); i++) {
////		for(uint j = i+1; j < triples.size(); j++) {
////			tuple<uint, uint, uint> &t1 = triples[i];
////			tuple<uint, uint, uint> &t2 = triples[j];
////		}
////	}
////
//////
//////
//////
//////		queue<uint> q;
//////		q.push(i);
//////
//////		while(!q.empty()) {
//////			uint neighbor = q.front();
//////			q.pop();
//////			if(visited[neighbor]) {
//////				// Cycle found
//////				ordering
//////
//////
//////				continue;
//////			}
//////			visited[neighbor] = true;
//////
//////			for(uint nextNeighbor = i; i < instance.getNumVertices(); i++) {
//////				if(adjacencyMatrix[neighbor][nextNeighbor] {
//////					q.push(nextNeighbor); 
//////				}
//////			 }
//////		}
//////	}
//
//
//
//
//
//
//
//
//	
//	return solution;
//}
