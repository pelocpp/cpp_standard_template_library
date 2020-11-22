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

#include "Globals.h"
#include "Node.h"
#include "NodeDetails.h"
#include "Edge.h"
#include "EdgeDetails.h"

#include "GraphInterface.h"
#include "GraphAdjList.h"
#include "GraphAdjMat.h"

#include "Solver_BFS.h"
#include "Solver_DFS.h"
#include "Solver_Kruskal.h"
#include "Solver_Dijkstra.h"
#include "Solver_NearestNeighbour.h"

// BFS test functions
//
void test_BFS_NordAmerika();
void test_BFS_SchaumsOutline();

// DFS test functions
//
void test_DFS_01();
void test_DFS_02();

// Dijkstra test functions
//
void test_01_Dijkstra_LMU_Muenchen_Abstract();
void test_02_Dijkstra_Bleeptrack_Youtube_Tutorial();
void test_03_Dijkstra_TUM_Europa();

// Kruskal test functions
//
void testPeLo01_Kruskal_Programiz();

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
    return 0;
}
