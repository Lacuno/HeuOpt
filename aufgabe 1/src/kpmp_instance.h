
#ifndef INSTANCE_READER_H_
#define INSTANCE_READER_H_

#include <string>
#include <vector>


class KPMPInstance {
private: 
	unsigned int K;
	unsigned int numVertices;
	std::vector<std::vector<unsigned int> > adjacencyList;
	bool **adjacencyMatrix;

	KPMPInstance(){}

public:
	static KPMPInstance* readInstance(std::string filename);

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

	std::vector<std::vector<unsigned int> > getAdjacencyList() const {
		return adjacencyList;
	}

	bool** getAdjacencyMatrix() const {
		return adjacencyMatrix;
	}
};

#endif /* INSTANCE_READER_H_ */
