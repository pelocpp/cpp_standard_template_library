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

#include "../Include/NodeEx.h"
#include "../Include/EdgeEx.h"

#include "../Include/GraphInterfaceEx.h"
#include "../Include/GraphAdjListEx.h"
#include "../Include/GraphAdjMatEx.h"

#include "Solver_Dijkstra.h"
#include "Solver_Dijkstra_Ex.h"

// Dijkstra test functions
//

void test_01_Dijkstra_LMU_Muenchen_Abstract_Ex();
void test_02_Dijkstra_Bleeptrack_Youtube_Tutorial_Ex();
void test_03_Dijkstra_TUM_Europa_Ex();

int main()
{
    test_01_Dijkstra_LMU_Muenchen_Abstract_Ex();
    test_02_Dijkstra_Bleeptrack_Youtube_Tutorial_Ex();
    test_03_Dijkstra_TUM_Europa_Ex();
    return 0;
}


// =====================================================================================
// End-of-File
// =====================================================================================
