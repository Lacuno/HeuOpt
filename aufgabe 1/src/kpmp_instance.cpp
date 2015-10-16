#include <iostream>
#include <fstream>
#include <limits>
#include "kpmp_instance.h"
#include "kpmp_solution_writer.h"

using namespace std;

KPMPInstance* KPMPInstance::readInstance(string filename) {
	// read in instance
	KPMPInstance* instance = new KPMPInstance();
	ifstream instFile (filename);
	string tmp;
	if (instFile.is_open()) {
		while(instFile.peek() == '#') 
			instFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// skip comments	
		instFile >> instance->numVertices;
		instFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// skip remainder of line
		cout << "instance->numVertices: " << instance->numVertices << endl;	// DEBUG

		while(instFile.peek() == '#') 
			getline(instFile, tmp);	// skip comments			
		instFile >> instance->K;
		instFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// skip remainder of line
		cout << "instance->K: " << instance->K << endl;	// DEBUG

		while(instFile.peek() == '#') 
			instFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// skip comments
		instance->adjacencyMatrix = new bool*[instance->numVertices];
		for (unsigned int i=0; i < instance->numVertices; i++) {
			instFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// skip vertices
			instance->adjacencyList.push_back(vector<unsigned int>());

			instance->adjacencyMatrix[i] = new bool[instance->numVertices];
			for (unsigned int j=0; j < instance->numVertices; j++)
				instance->adjacencyMatrix[i][j] = false;
		}

		while(true) {  
			if(instFile.peek() == '#')
				instFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// skip comments
			else {
				unsigned int a, b;
				instFile >> a >> b;
				if(instFile.eof())
					break;				
				instFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// skip remainder of line (page number)
				instance->adjacencyList[a].push_back(b);
				instance->adjacencyList[b].push_back(a);
				instance->adjacencyMatrix[a][b] = true;
				instance->adjacencyMatrix[b][a] = true;
			}
		}

		instFile.close();
	}
	else {
		cerr << "Unable to open file"; 
		return NULL;
	}

	return instance;
}
