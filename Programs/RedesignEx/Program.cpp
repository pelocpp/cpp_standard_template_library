// =====================================================================================
// Graph Theory Redesign
// =====================================================================================

// TEST


// =====================================================================================

// FRAGE:

// Der Iterator von Marc Gregoire kann nicht funktionieren:

// Es werden Iteratoren (map / set) von verschiedenen Containern verglichen

// =====================================================================================

// WEITERARBEIT:

// Es werden 2 Iteratoren an der Klasse Graph ben�tigt:

// F�r Tracks und f�r Edges

// Das kann man �ber 2 setter abfahren (so in etwa):

// for ( const& auto track : my_graph.tracks() )

// Ist in StackOverflow hier beschrieben:

// https://blog.cppse.nl/cpp-multiple-iterators-with-traits

// oder

// https://stackoverflow.com/questions/25105730/range-based-for-loops-and-multiple-iterators

// oder

// https://stackoverflow.com/questions/25105730/range-based-for-loops-and-multiple-iterators

// Fr�here Suche zum Thema 2 Iteratoren:

// TODO: Hier ist beschrieben, wie man in einer Klasse ZWEI ITeratoren unterbekommt:
// https://blog.cppse.nl/cpp-multiple-iterators-with-traits

// TODO:
// Man sollte die Klassen auch mit C++ Iteratoren ausstatten
// Dazu ben�tigt man das Thema "c++ implementing iterator as nested class"  ( Google Search ) !!!


// =====================================================================================

// Prim Algorithmus

// =====================================================================================

// const vs non-const

// Versuche das jetzt korrekt zu machen
// https://stackoverflow.com/questions/856542/elegant-solution-to-duplicate-const-and-non-const-getters

// Besser: https://stackoverflow.com/questions/123758/how-do-i-remove-code-duplication-between-similar-const-and-non-const-member-func

// Noch besser: ES.50: Don�t cast away const

// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines


// =====================================================================================

// TODO: Kl�ren, ob das geht: das mit std::nullopt
// bool addEdge(const T& fromValue, const T& toValue, const W& weight = std::nullopt) {
// Dann ist das nur noch eine Methode !!!!!!!!!!!!!!!!!!!!

// bool addEdge(const T& fromValue, const T& toValue, const W& weight);

// =====================================================================================

// Generell alle Namen der kanten:  from, to   // source, Target // EINHEITLICH !!!!!!!

// size_t source, size_t target

// -----------------------------------------------------------------------

// TODO:
// [[ nodiscard ]]

// Hmmm, die k�nnte man massenhaft einbauen .. sieht halt dann nicht mehr so gut aus ...

// -----------------------------------------------------------------------

// Die Methode findNode ist die einzige, die mit einem Iterator Objekt hantiert:

// Vielleicht kann man, da diese Methode private ist, sie irgendwo verstecken ...
// sie wird doch nicht so h�ufig aufgerufen, oder ?????????????


// -----------------------------------------------------------------------


// Klasse Graph mit begin und end ausstatten ===> dann kann man mit for_each iterieren ...

// andere Algorithmen wie
// std::find_if,
// std::accumulate, etc.
// std::copy_if
// ausprobieren und anwenden ...

// -----------------------------------------------------------------------


// TODO: Kl�ren, ob das geht: das mit std::nullopt
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
// =====================================================================================

// von der anderen Datei ....

// TODO: final, override ... Vor allem final einsetzen, wenn man eine Methode nicht mehr �berschreiben sollte

// =====================================================================================

// // TODO:
// ACHTUNG: Habe jetzt �berall size_t verwendet - da geht aber -1 nicht !!!!!!!!!!!!!!!!!!!!

// TODO:
// Es sind derzeit keinerlei Fehlerberpr�fungen drin: doppelte Kanten ... wieso wird da eigenlich nicht mehr eine std::set verwendet ????


// =====================================================================================

// TWO PHASE LOOKUP !!!!
// https://www.modernescpp.com/index.php/surprise-included-inheritance-and-member-functions-of-class-templates
// HIER GEHT ES UM DAS using inmitten des Quellcode !!!!


// =====================================================================================

// TODO:
// oss << "[" << std::setw(12) << std::left << description << "] ";
// Hier k�nnte man die maximale Feldbreite tats�chlich berechnen -- sieht dann doch besser aus ....
// ODer gleich mit std::format von C++ 20 arbeiten !!!!

// =====================================================================================

// TODO:
// Viele Methoden k�nnen mit const qualifiziert werden

// =====================================================================================

// TODO:
// Iteratoren f�r die "benachbarten" Konten schreiben !!!
// Im Beispiel findet man das hier:
// Mein Scratch - Projekt - Datei Source17_Graphs_Another_Approach.cpp
// Oder hier:
// https://blog.cppse.nl/cpp-multiple-iterators-with-traits
// 
// =====================================================================================

extern void test_graph_nodes();
extern void test_graphs();
extern void test_graph_iterators();
extern void test_dfs();
extern void test_dfs_connected_components();
extern void test_bfs();
extern void test_dijkstra();
extern void test_kruskal();

int main()
{
    //test_graph_nodes();
    //test_graphs();
    test_graph_iterators();
    //test_dfs();
    //test_dfs_connected_components();
    //test_bfs();
    //test_dijkstra();
    //test_kruskal();

    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================
