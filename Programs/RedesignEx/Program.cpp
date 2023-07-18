// =====================================================================================

        // TODO: Klären, ob ein Konstruktor mit der Knotenanzahl Sinn ergibt
        //  Graph<std::string> graph{ 4 };

// TODO:
// [[ nodiscard ]]


// Hmmm, die könnte man massenhaft einbauen .. sieht halt dann nicht mehr so gut aus ...


// AdjacencyListType<EmptyType>&neighbours = ....
// Warum geht dieser Default Template Parameter nicht, also
// AdjacencyListType&neighbours = ....
// bzw. bin  jetzt bei AdjacencyListType<> angekommen !


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


namespace Graph_Theory_Graphs
{
    extern void test_graphs();
}

namespace Graph_Theory_DFS
{
    extern void test_20();
    extern void test_22();
}

int main()
{
    Graph_Theory_Graphs::test_graphs();

    // Graph_Theory_DFS::test_20();
    //Graph_Theory_DFS::test_22();

    return 1;
}

