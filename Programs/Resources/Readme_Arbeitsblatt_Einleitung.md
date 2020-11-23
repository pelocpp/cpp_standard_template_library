## Graphentheorie im Zusammenspiel mit der C++ Standard Template Library (STL)

In der Graphentheorie ist ein *Graph* eine Menge von Punkten (man nennt diese dann auch Knoten (engl. *node*)
oder Ecken (engl. *vertex*, plural *vertices*),
die eventuell durch Linien, so genannte Kanten (engl. *edge*) miteinander verbunden sind.
Die Form der Punkte und Linien spielt in der Graphentheorie keine Rolle.

<img src="graphs_01_nodes_and_edges.png" width="300">

Abbildung 1: Darstellung eines gerichteten Graphen mit Knoten und unbeschrifteten Kanten.

Viele Algorithmen aus dem Bereich der Graphentheorie lassen sich in C++ - zusammen mit der Standard Template Library - vergleichsweise
elegant und einfach lösen. Für die Verwaltung der Knoten und Kanten eines Graphen bieten sich STL-Container an (z.B. `std::vector`).
Graphentheoretische Algorithmen wiederum sind mit STL-Iteratoren und -Algorithmen realisierbar.
Auf einige der bekanntesten graphentheoretischen Algorithmen gehen wir im Folgenden näher ein.

## Zwei Klassen `Edge` und `Graph`

Entwickeln Sie zwei Klassen `Edge` und `Graph`, um einen Graphen
in einem C++-Programm darstellen zu können. Zur internen Repräsentation der Kanten eines Graph-Objekts gibt es
die so genannte *"Adjacency List"* Darstellung:

<img src="graphs_02_adjacency_list.png" width="600">

Abbildung 2: *"Adjacency List"*: Darstellung eines gerichteten Graphen.

Diese Darstellung verwaltet die Knoten und Kanten eines Graphen mit mehreren listenartigen Datenstrukturen.
Das Gegenstück zu dieser Darstellungsart sind so genannte *"Adjazenzmatrizen"*. Hierbei handelt es sich
um zweidimensionale, quadratische Matrizen der Größe *N*x*N*, wobei *N* die Anzahl der Eckpunkte des Graphen ist.

Weitere Aspekte, die Sie in der Entwicklung der beiden Klassen berücksichtigen:

  * Setzen Sie, soweit möglich, STL-Container, -Iteratoren und -Algorithmen in Ihrer Realisierung ein. 

  * Kanten können gerichtet oder ungerichtet sein. Man könnte dies mit einem Attribut `isDirected` an der Klasse `Graph` umsetzen.

  * Ein Graph hat immer eine feste Anzahl von Knoten. Wie kann man dies in C++ mit *Value Templates* umsetzen?

  * Kanten können gewichtet oder ungewichtet sein. Das läuft im Prinzip zunächst einmal auf verschiedene Ausprägungen
der Klasse `Edge` hinaus, aber: Wie könnte man einen konkreten Graphen mit gewichteten oder ungewichteten Kanten instanziieren?
<br/><br/>*Hilfestellung*:<br/>`template <typename EDGE> class Graph {}`

Für das Hinzufügen einer Kante zu einem Graphen gibt es in C++ viele Möglichkeiten.
Nachfolgend finden Sie einige Anregungen vor:

```cpp
void addEdge(int source, int target);
void addEdge(int source, int target, int weight);
void addEdges(std::initializer_list<EDGE> list);
void addEdges(const std::vector<EDGE>& edges);
```

*Bemerkung*: Wenn Sie Zeit haben, können Sie die Klasse `Graph` in zwei Ausprägungen realisieren, einmal mit Adjazenzlisten
und zum Zweiten mit Adjazenzmatrizen. Welche Beobachtungen können Sie bzgl. Speicherplatzverbrauch und Laufzeit machen?

***Bemerkung***: Die Knoten eines Graphen können optional eine Beschriftung haben (Name einer Stadt, etc.). Überlegen Sie,
wie sich diese Anforderung umsetzen lässt. Für eine Zuordnung
Knotennummer <=> Knotenbeschriftung bieten sich in der Implementierung fast idealerweise `std::map`-Container an. Die Ids der
Knoten eines Graphen müssen immer eindeutig sein, sie könnten als Schlüssel für ein `std::map`-Objekt fungieren.

---

[Zurück](Readme.md)

---
