// =====================================================================================
// Program
// =====================================================================================

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

#include "Solver_BFS.h"

//using namespace NodeDetailsNumbered;
//using namespace Solver_BFS;

// BFS test functions
//
void test_BFS_NordAmerika();
void test_BFS_SchaumsOutline();

int main() {


   test_BFS_NordAmerika();
    // test_BFS_SchaumsOutline();
    return 0;
}


// =====================================================================================
// End-of-File
// =====================================================================================
