// =====================================================================================
// Globals.h
// =====================================================================================

using IndexType = size_t;   // PeLo     size_t ausprobieren !!!!!!!!!!!!!!!!

// PeLo: Alle std::get  durchforsten ....
constexpr int IndexSource = 0;
constexpr int IndexTarget = 1;
constexpr int IndexWeight = 2;

constexpr int IndexNodeId = 0;

enum class Direction { directed, undirected };
//
//template <>
//
//using true_type = logical_constant<true>;
//using false_type = logical_constant<false>;

constexpr bool Directed = true;
constexpr bool NotDirected = false;

constexpr bool Weighted = true;
constexpr bool NotWeighted = false;


// =====================================================================================
// End-of-File
// =====================================================================================
