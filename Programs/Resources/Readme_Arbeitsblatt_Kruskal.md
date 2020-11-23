## Kruskal's Algorithmus

### Einleitung

Der Kruskal-Algorithmus f�llt in die Kategorie der "*Minimum-Spanning-Tree*"-Algorithmen.

Die Eingabe des Algorithmus ist ein Graph. Ermittelt wird eine Teilmenge derjenigen Kanten des Graphen, die
n�tig ist, um alle Knoten m�glichst kosteng�nstig miteinander zu verbinden.

Grob in Worte gefasst kann man den Ablauf wie folgt skizzieren:

Um den minimalen Spannbaum zu ermitteln, sortiert der Algorithmus zuerst alle Kanten aufsteigend
nach ihren Kantengewichten.

Dann wird ein neuer Graph erstellt, der alle Knoten des alten Graphen, jedoch noch keine Kanten enth�lt.
Nach und nach werden jetzt die aufsteigend sortierten Kanten hinzugef�gt.
Somit wird Kanten f�r Kanten zum Graphen erg�nzt.
Da hierbei immer die Kante, die aktuell am k�rzesten ist, hinzugef�gt wird,
geh�rt der Kruskal Algorithmus zu den Greedy-Algorithmen.

Eine Bedingung gilt es noch zu beachten: Der Algorithmus f�gt nur Kanten hinzu, solange dadurch 
keine Kreise im Graphen entstehen.

### Der Algorithmus

Der Algorithmus von Kruskal besteht eigentlich aus zwei Algorithmen:
Dem Algorithmus selbst und einem weiteren Algorithmus, der unter der Bezeichnung "Union-Find"-Algorithmus
firmiert. Dieser verhindert, dass beim Suchen des minimalen Spannbaums Zyklen (Kreise) entstehen,
die f�r eine L�sung nicht in Betracht kommen k�nnen.

Ein sehr leicht verst�ndliches Tutorial von *Bleeptrack* alias Sabine Wieluch finden wir
in Youtube unter

https://www.youtube.com/watch?v=GJ17vvqY6aE (4 Minuten)

vor. Dieses Tutorial dient mehr dem Verst�ndnis des Algorithmus. F�r eine programmiersprachliche Umsetzung
schauen wir wieder bei William Fiset vorbei. *Hinweis*: Auf Grund der Architektur des Algorithmus
sind es dieses Mal zwei Tutorials:

*Kruskal's Algorithm*:<br/>
https://www.youtube.com/watch?v=JZBQLXgSGfs&t=304s    (6 Minuten)

*Union Find Operations*:<br/>
https://www.youtube.com/watch?v=0jNmHPfA_yE&t=476s    (11 Minuten)

### Test der Implementierung:

Auf der Homepage der Technischen Universit�t M�nchen kann man den Algorithmus
interaktiv testen:

https://www-m9.ma.tum.de/graph-algorithms/mst-kruskal/index_de.html

Unter der Lasche "*Forschungsaufgabe*" findet man ein gr��eres Beispiel vor, dass sich
gut zum Testen eignet. 


##### Bezug zur STL:

Folgende Elemente der STL k�nnen Anwendung finden:

###### Container:

`std::vector<>`, `std::list<>`, `std::initializer_list`

###### Iteratoren:

`std::vector<int>::iterator`, `std::vector<int>::reverse_iterator`, `std::back_inserter`

###### Algorithmen:

`std::for_each`, `std::reverse`, `std::fill`, `std::generate`, `std::begin`, `std::end`, `std::tuple_size`

---

[Zur�ck](Readme.md)

---

