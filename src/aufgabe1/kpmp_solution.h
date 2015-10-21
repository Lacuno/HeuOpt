#ifndef INSTANCE_SOLUTION_H_
#define INSTANCE_SOLUTION_H_

#include <vector>
#include <tuple>
#include <unordered_map>

typedef unsigned int uint;
typedef std::pair<uint, uint> Edge;

struct key_hash : public std::unary_function<Edge, std::size_t>
{
 std::size_t operator()(const Edge& k) const
 {
   return 10000 * std::get<0>(k) + std::get<1>(k);
 }
};

class KPMPSolution {
    private:
    	uint k;
        std::unordered_map<uint, uint> ordering; // Vertex to Ordering
	std::unordered_map<uint, std::vector<Edge>> pageToEdges;
	std::unordered_map<Edge, uint, key_hash> edgeToPage;

    public:
	KPMPSolution(uint k, uint numVertices);
        
	uint getPage(Edge e); 
	std::vector<Edge> getEdgesFromPage(uint p);
	void addEdge(uint p, Edge e);
	void removeEdge(Edge e);
	void setOrdering(std::unordered_map<uint, uint> &newOrdering);
	uint computeCrossings(); 
};

#endif /* INSTANCE_SOLUTION_H_ */
