#include <iostream>
#include "kpmp_instance.h"
#include "kpmp_solution.h"

int main()
{
//    KPMPInstance::readInstance("bla");
    KPMPSolution sol(3, 100);
    
    //sol.addEdge(0, {10, 11});
    //sol.removeEdge({10, 11});
    
    sol.addEdge(0, {0, 2});
    sol.addEdge(0, {1, 3});
    
    sol.addEdge(0, {5, 6});
    sol.addEdge(0, {6, 7});
   
    std::cout << "computing crossings..." << std::endl; 
    std::cout << sol.computeCrossings() << std::endl;
    

    std::cout << "hello world!" << std::endl;
    return 0; 
}
