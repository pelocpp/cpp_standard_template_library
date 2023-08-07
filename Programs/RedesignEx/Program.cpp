// =====================================================================================
// Graph Theory Redesign
// =====================================================================================


// =====================================================================================

// Generell alle NAmen der kanten:  from, to   // source, Target // EINHEITLICH !!!!!!!

// size_t source, size_t target

// -----------------------------------------------------------------------

// TODO:
// [[ nodiscard ]]


// Hmmm, die könnte man massenhaft einbauen .. sieht halt dann nicht mehr so gut aus ...

// -----------------------------------------------------------------------

// Die Methode findNode ist die einzige, die mit einem Iterator Objekt hantiert:

// Vielleicht kann man, da diese Methode private ist, sie irgendwo verstecken ...
// sie wird doch nicht so häufig aufgerufen, oder ?????????????


// -----------------------------------------------------------------------


// Klasse Graph mit begin und end ausstatten ===> dann kann man mit for_each iterieren ...

// andere Algorithmen wie std::find_if,  std::accumulate etc. ausprobieren und anwenden ...

// -----------------------------------------------------------------------


        // TODO: Klären, ob das geht: das mit std::nullopt
        // bool addEdge(const T& fromNode, const T& toNode, const W& weight = std::nullopt) {
        // Dann ist das nur noch eine Methode !!!!!!!!!!!!!!!!!!!!


// -----------------------------------------------------------------------



// AdjacencyListType<EmptyType>&neighbours = ....
// Warum geht dieser Default Template Parameter nicht, also
// AdjacencyListType&neighbours = ....
// bzw. bin  jetzt bei AdjacencyListType<> angekommen !

// Hmmm -- dies kann man so vermeiden:
// https://probablydance.com/2014/01/16/alias-templates-with-partial-specialization-sfinae-and-everything/


// -----------------------------------------------------------------------

// Allgemein; Wir haben nun eine Mehtode format
// 
// 
// ss << std::format("{} -> {}", node_value, node) << std::endl;   // TODO: Vielleicht auf format umsteigen ...
// 

// =====================================================================================

// von der anderen Datei ....

// TODO: final, override ... Vor allem final einsetzen, wenn man eine Methode nicht mehr überschreiben sollte

// TODO: Hier ist beschrieben, wie man in einer Klasse ZWEI ITeratoren unterbekommt:
// https://blog.cppse.nl/cpp-multiple-iterators-with-traits

// TODO:
// Man sollte die Klassen auch mit C++ Iteratoren ausstatten
// Dazu benötigt man das Thema "c++ implementing iterator as nested class"  ( Google Search ) !!!

// // TODO:
// ACHTUNG: Habe jetzt überall size_t verwendet - da geht aber -1 nicht !!!!!!!!!!!!!!!!!!!!

// TODO:
// Es sind derzeit keinerlei Fehlerberprüfungen drin: doppelte Kanten ... wieso wird da eigenlich nicht mehr eine std::set verwendet ????

// TWO PHASE LOOKUP !!!!
// https://www.modernescpp.com/index.php/surprise-included-inheritance-and-member-functions-of-class-templates
// HIER GEHT ES UM DAS using inmitten des Quellcode !!!!

// TODO: 
//// Die beiden Methoden 
//virtual void setNodeDescription(size_t index, const NodeDescription& description) = 0;
//virtual void setNodeDescriptions(const std::initializer_list<NodeDescription> list) = 0;
// sind derzeit doppelt implementiert ... das sollte man doch vermeiden
// 

// TODO:
// oss << "[" << std::setw(12) << std::left << description << "] ";
// Hier könnte man die maximale Feldbreite tatsächlich berechnen -- sieht dann doch besser aus ....
// ODer gleich mit std::format von C++ 20 arbeiten !!!!

// TODO:
// Viele Methoden können mit const qualifiziert werden


// TODO:
// Iteratoren für die "benachbarten" Konten schreiben !!!
// Im Beispiel findet man das hier:
// Mein Scratch - Projekt - Datei Source17_Graphs_Another_Approach.cpp
// Oder hier:
// https://blog.cppse.nl/cpp-multiple-iterators-with-traits
// 
// =====================================================================================

extern void test_graph_nodes();
extern void test_graphs();
extern void test_dfs();
extern void test_dfs_connected_components();
extern void test_bfs();
extern void test_dijkstra();
extern void test_kruskal();

int main()
{
    //test_graph_nodes();
   //test_graphs();
  //  test_dfs();
    //test_dfs_connected_components();
    //test_bfs();
   test_dijkstra();
    //test_kruskal();

    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================
