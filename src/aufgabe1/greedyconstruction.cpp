#include <tuple>
#include <queue>
#include <vector>
#include "greedyconstruction.h"


using namespace std;

shared_ptr<KPMPSolution> GreedyConstruction::construct(KPMPInstance &instance) {
	shared_ptr<KPMPSolution> solution(new KPMPSolution(instance.getK(), instance.getNumVertices()));
	
	bool** adjacencyMatrix = instance.getAdjacencyMatrix();
   	const vector<vector<uint>> &adjacencyList = instance.getAdjacencyList();

//	vector<bool> visited;
//	for(uint i = 0; i < instance.getNumVertices(); i++) {
//		visited.push_back(false);
//	}
//
//	vector<uint> ordering; 
//	vector<uint> vertexToOrdering;
 	vector<tuple<uint, uint, uint>> triples;

	// Triangle search
	for(uint i = 0; i < instance.getNumVertices(); i++) {
		for(uint j = i; j < instance.getNumVertices(); j++) {
			if(adjacencyMatrix[i][j]) {
				for(uint k = j; k < instance.getNumVertices(); k++) {
					if(adjacencyMatrix[j][k] && adjacencyMatrix[k][i]) {
						// Triangle found
						tuple<uint, uint, uint> triple {i, j, k};
						triples.push_back(triple);
					}
				}
			}
		}
	}

	vector<uint> ordering;
	vector<uint> containedInOrdering;
	for(uint i = 0; i < instance.getNumVertices(); i++) {
		containedInOrdering.push_back(false);
	}

	// Find neighbor triples
	auto insertToOrdering = [&](uint toInsert, uint beforeElement, bool before) {
		if(!containedInOrdering[toInsert]) {
			auto pos = find(ordering.begin(), ordering.end(), beforeElement);

			if(before) {
				ordering.insert(pos, toInsert);	
			} else {
				ordering.insert(pos+1, toInsert);
			}
			containedInOrdering[toInsert] = true;
		}
	};

	auto compareTuples = [&](tuple<uint, uint, uint> &t1, tuple<uint, uint, uint> &t2) {
		if(get<0>(t1) == get<0>(t2)) {
			// Ordering: t2(1), t2(2), t1(0), t1(1), t1(2)
			insertToOrdering(get<1>(t2), get<2>(t2), true);
			insertToOrdering(get<2>(t2), get<0>(t1), true);
			insertToOrdering(get<0>(t1), get<1>(t1), true);
			insertToOrdering(get<1>(t1), get<2>(t1), true);
			insertToOrdering(get<2>(t1), get<1>(t1), false);
			return;
		}
		// TODO
		if(get<1>(t1) == get<0>(t2)) {
			// Ordering: t1(0), t1(2), t1(1), t2(1), t2(2)
			insertToOrdering(get<0>(t1), get<2>(t1), true);
			insertToOrdering(get<2>(t1), get<1>(t1), true);
			insertToOrdering(get<1>(t1), get<1>(t2), true);
			insertToOrdering(get<1>(t2), get<2>(t2), true);
			insertToOrdering(get<2>(t2), get<1>(t2), false);
			return;
		}
		if(get<2>(t1) == get<0>(t2)) {
			// Ordering: t1(0), t1(1), t1(2), t2(1), t1(2)
			insertToOrdering(get<1>(t2), get<2>(t2), true);
			insertToOrdering(get<2>(t2), get<0>(t1), true);
			insertToOrdering(get<0>(t1), get<1>(t2), true);
			insertToOrdering(get<1>(t1), get<2>(t2), true);
			insertToOrdering(get<2>(t1), get<1>(t2), false);
		}
	};


	for(uint i = 0; i < triples.size(); i++) {
		for(uint j = i+1; j < triples.size(); j++) {
			tuple<uint, uint, uint> &t1 = triples[i];
			tuple<uint, uint, uint> &t2 = triples[j];
		}
	}

//
//
//
//		queue<uint> q;
//		q.push(i);
//
//		while(!q.empty()) {
//			uint neighbor = q.front();
//			q.pop();
//			if(visited[neighbor]) {
//				// Cycle found
//				ordering
//
//
//				continue;
//			}
//			visited[neighbor] = true;
//
//			for(uint nextNeighbor = i; i < instance.getNumVertices(); i++) {
//				if(adjacencyMatrix[neighbor][nextNeighbor] {
//					q.push(nextNeighbor); 
//				}
//			 }
//		}
//	}








	
	return solution;
}
