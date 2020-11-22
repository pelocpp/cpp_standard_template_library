#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <deque>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <tuple>
#include <optional>
#include <functional>
#include <utility>
#include <cassert>

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../Include/Globals.h"
#include "../Include/Node.h"
#include "../Include/NodeDetails.h"
#include "../Include/Edge.h"
#include "../Include/EdgeDetails.h"

#include "../Include/GraphInterface.h"
#include "../Include/GraphAdjList.h"
#include "../Include/GraphAdjMat.h"

#include "Solver_NearestNeighbour.h"

// Nearest Neighbour test functions
//
void test_01_NearestNeighbour_NFE();
void test_01_NearestNeighbour_Fuenf_Staedte();
void test_01_NearestNeighbour_TSP(std::string filename);

// Example from Uni Heidelberg
const std::string tspFileName01 = "Danztig.tsp";

// Example from
// https://www.sanfoundry.com/java-program-implement-traveling-salesman-problem-using-nearest-neighbour-algorithm/
const std::string tspFileName02 = "SanFoundry.tsp";

int main() {

    test_01_NearestNeighbour_NFE();
    test_01_NearestNeighbour_Fuenf_Staedte();
    test_01_NearestNeighbour_TSP(tspFileName01);
    return 0;
}
