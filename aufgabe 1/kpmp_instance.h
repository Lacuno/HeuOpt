
#ifndef INSTANCE_READER_H_
#define INSTANCE_READER_H_

#include <string>
#include <vector>

using namespace std;

class KPMPInstance {
private: 
	unsigned int K;
	unsigned int numVertices;
	vector<vector<unsigned int> > adjacencyList;
	bool **adjacencyMatrix;

	KPMPInstance(){}

public:
	static KPMPInstance* readInstance(string filename);

	~KPMPInstance() {
		for(unsigned i = 0; i < numVertices; i++)
			delete[] adjacencyMatrix[i];
		delete[] adjacencyMatrix;
	}

	unsigned int getK() const {
		return K;
	}

	unsigned int getNumVertices() const {
		return numVertices;
	}

	vector<vector<unsigned int> > getAdjacencyList() const {
		return adjacencyList;
	}

	bool** getAdjacencyMatrix() const {
		return adjacencyMatrix;
	}
};

#endif /* INSTANCE_READER_H_ */
