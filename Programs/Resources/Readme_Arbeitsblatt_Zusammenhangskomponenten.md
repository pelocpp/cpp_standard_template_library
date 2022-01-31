## Zusammenhangskomponenten eines Graphen

Eine Anwendung des *Depth-First Search* Algorithmus (DFS) ist die Bestimmung der Zusammenhangskomponenten eines Graphen.
Dazu benötigen wir zunächst einige Begriffe:

**Definition**: Ein (ungerichteter) Graph heißt *zusammenhängend*, wenn es von jedem Knoten
*n*<sub>1</sub> zu jedem anderen Knoten *n*<sub>2</sub> mindestens einen Pfad gibt.

Und noch eine zweite Definition:

**Definition**: Ein maximal zusammenhängender Zeilgraph eines (ungerichteten) Graphen heißt
*Zusammenhangskomponente* des Graphen.

Am besten betrachten wir in *Abbildung* 1 und *Abbildung* 2 zwei Graphen, um den Unterschied zwischen einem *zusammenhängenden* und nicht *zusammenhängenden*
besser zu verstehen. In *Abbildung* 1 erkennen Sie einen nicht-zusammenhängenden Graphen:

<img src="graphs_20_connected_components_01.svg" width="300">

*Abbildung* 1: Beispiel eines nicht-zusammenhängenden Graphen.

Das Gegenstück eines zusammenhängenden Graphen finden Sie in *Abbildung* 2 vor:

<img src="graphs_20_connected_components_02.svg" width="300">

*Abbildung* 2: Beispiel eines nicht-zusammenhängenden Graphen.

Der DFS-Algorithmus (engl. *depth-first search*) eignet sich ideal zum Suchen aller
Zusammenhangskomponenten eines Graphen. 

Eine Beschreibung befindet sich im selben Video, das den *Depth-First Search* Algorithmus erläutert:

https://www.youtube.com/watch?v=7fujbpJ0LB4  (10 Minuten).


Zum Testen ihrer Realisierung legen Sie bitte den Graphen aus der folgenden *Abbildung* 3 zugrunde:

<img src="graphs_20_connected_components_03_example.svg" width="550">

*Abbildung* 3: Graph zum Testen des *Depth-First Search* Algorithmus.

Welchen Zusammenhangskomponenten können Sie rechnerisch bestimmen?


*Antwort*:

```
```


##### Bezug zur STL:

Folgende Elemente der STL können Anwendung finden:

###### Container:

`std::vector<>`, `std::deque<>`, `std::list<>`, `std::initializer_list`

###### Iteratoren:

`std::vector<int>::iterator`, `std::vector<int>::reverse_iterator`, `std::back_inserter`

###### Algorithmen:

`std::for_each`, `std::reverse`, `std::fill`, `std::generate`, `std::begin`, `std::end`, `std::tuple_size`

---

[Zurück](../../Readme.md)

---

