## Weiterarbeit / Offene Punkte

#### Alternative Realisierung für die Methode `getNeighbouringNodes`

Alternativ zur Methode `getNeighbouringNodes`
könnte man auch eine Iterator-Implementierung bereitstellen - also ganz im Sinne des STL-Konzepts.

```cpp
template<typename T>
class INodeIterator
{
public:
    // virtual ~INodeIterator() = 0;

    virtual T operator*() = 0;

    virtual void operator++() = 0;
    virtual void operator--() = 0;
};

template< typename Container> struct NodeIterator;
```

---

#### Realisierung weiterer graphentheoretischer Algorithmen

Im C++ - Lehrbuch von Kaiser / Guddat ("*C/C++ - Das umfassende Lehrbuch*" von Ulrich Kaiser, Martin Guddat,
1220 Seiten, 5., aktualisierte und überarbeitete Auflage 2014, Galileo Computing, ISBN 978-3-8362-2757-5)
finden sich sich eine Reihe von Algorithmen aus der Graphentheorie in C-Notation erläutert.

Wer üben möchte, kann versuchen, die dort vorgestellten Algorithmen auf den C++/STL-Framework dieser 
Fallstudie umzuschreiben.

---

#### Funktionsschablone `getWeight`

Die Funktionsschablone `getWeight` 
wird in den beiden Klassen `GraphAdjList` und `GraphAdjMatrix` jeweils für den Template Parameter `W` mit dem Argument
`int` verwendet. Dies müsste man auf der Basis von Member Template Functions verallgemeinern: 

```cpp
template<typename E, typename W>
W getWeight(const E& edge) {
    return std::get<2>(edge);
}
```

*Hinweis*: Da Member Template Functions nicht virtual deklarierbar sind, zieht dies weitere Änderungen nach sich.

---

#### Kleinigkeiten

  * Es sollten die vier Varianten (Graph gerichtet, ungerichtet als auch gewichtet, ungewichtet) mit der Methode `toString` getestet sein.
  * Nicht alle Beispiele aus den Beschreibungen sind implementiert (*Reise des Odysseus*, *Entfernungstabelle Deutschland*).

---

#### Erster Ansätze zur Ergänzung des Iterator-Konzepts

Unterstützung in der Ergänzung des Iterator-Konzepts findet man unter

https://stackoverflow.com/questions/470835/a-c-iterator-adapter-which-wraps-and-hides-an-inner-iterator-and-converts-the

https://stackoverflow.com/questions/20966749/nested-iterator-class-begin-and-end-sentinel-issues

https://stackoverflow.com/questions/3582608/how-to-correctly-implement-custom-iterators-and-const-iterators


```cpp
class NodeIteratorImpl : public INodeIterator<IndexType>
{
public:
NodeIteratorImpl() = default;
IndexType operator*() override { return 1; }
//   const T& operator*() override const {}

void operator++() override { return; }
void operator--() override { return; }
};

class NodeIteratorImpl;
using item_iterator = GraphAdjList< NODE, EDGE>::NodeIteratorImpl;


NodeIteratorImpl m_impl;
INodeIterator<int>& getNodeIteratorImpl() /* override */  { return m_impl; }

//  item_iterator& getNodeIteratorImpl() override  { return m_impl; }
public:

NodeIterator<NodeIteratorImpl> begin2() { return NodeIteratorImpl(); }
NodeIterator<NodeIteratorImpl> end2() { return NodeIteratorImpl(); }

//typedef GraphAdjList::NodeIteratorImpl node_iterator;
//node_iterator begin2()  { return NodeIteratorImpl(); }
//node_iterator end2()   { return NodeIteratorImpl(); }

//  item_iterator& getNodeIteratorImpllll()  { return m_impl; }

// ===================================================================
 
class AdjacencyIterator;
friend class AdjacencyIterator;

class AdjacencyIterator
{
public:
typedef AdjacencyIterator self_type;
typedef IndexType value_type;
typedef IndexType& reference;
typedef IndexType* pointer;

private:
IndexType       m_index;
GraphAdjList& m_outerGraph;

//   std::list<EDGE>::iterator m_iter;

public:
AdjacencyIterator(GraphAdjList& graph) : m_outerGraph(graph), m_index(0) {}
AdjacencyIterator(GraphAdjList& graph, bool) : m_outerGraph(graph), m_index(999) {}

bool operator!=(const AdjacencyIterator& rv) const
{
return m_index != rv.m_index;
}

bool operator==(const AdjacencyIterator& rv) const
{
return m_index == rv.m_index;
}

EDGE operator*()
{
return m_outerGraph.m_adjacencyList[m_index][0];  // TODO: Das geht nicht .. weil es ein INDEX IST
}

EDGE operator++()
{
// return s.m_element[++i_index];
return {1,2};
}
};

AdjacencyIterator begin() const  { return AdjacencyIterator(*this); }
AdjacencyIterator end()  const  { return AdjacencyIterator(*this, true); }
```

---

[Zurück](Readme.md)

---
