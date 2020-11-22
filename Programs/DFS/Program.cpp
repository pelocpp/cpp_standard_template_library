

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

#include "Solver_DFS.h"

// DFS test functions
//
void test_DFS_01();
void test_DFS_02();

int main() {

    test_DFS_01();
    test_DFS_02();
    return 0;
}
