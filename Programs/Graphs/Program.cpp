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

// Dijkstra test functions
//
void test_01_Dijkstra_LMU_Muenchen_Abstract();
void test_02_Dijkstra_Bleeptrack_Youtube_Tutorial();
void test_03_Dijkstra_TUM_Europa();

int main()
{
    test_01_Dijkstra_LMU_Muenchen_Abstract();
    test_02_Dijkstra_Bleeptrack_Youtube_Tutorial();
    test_03_Dijkstra_TUM_Europa();
    return 0;
}


// =====================================================================================
// End-of-File
// =====================================================================================
