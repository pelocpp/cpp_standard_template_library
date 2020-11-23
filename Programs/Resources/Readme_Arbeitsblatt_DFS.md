## Depth-First Search (DFS) Algorithmus

Der DFS-Algorithmus (engl. *depth-first search*) ist wie der BFS-Algorithmus ein Verfahren zum Suchen 
von Knoten in einem Graphen. Im Gegensatz zur Breitensuche wird bei der Tiefensuche zunächst ein Pfad vollständig in die Tiefe beschritten, bevor abzweigende Pfade beschritten werden.
Dabei sollen alle erreichbaren Knoten des Graphen besucht werden.

Eine der Stärken des *Depth-First Search* Algorithmus ist die Lösung des folgenden Problems:

  * Suchen Sie in einem Graphen einen Pfad zwischen zwei vorgegebenen Knoten.

Damit ist auch verbunden die Antwort auf die Fragestellung, ob es zwischen zwei Knoten überhaupt eine Verbindung gibt.

Eine - wiederum empfehlenswerte - Beschreibung des DFS-Algorithmus, die auch auf das soeben skizzierte Problem eingeht,
gibt Willial Fiset in

https://www.youtube.com/watch?v=7fujbpJ0LB4  (10 Minuten).

Implementieren Sie in diesem Abschnitt eine Klasse `DFSGraph`. Wie können Sie wiederum auf die Vorarbeiten
der beiden Klassen `Edge` und `Graph` zurückgreifen?

Eine Pseudocode-Darstellung des Algorithmus finden Sie nachstehend. Die nicht deklarierten Variablen
sollten bzgl. der Festlegung eines Typs (STL-Container) selbsterklärend sein.
Ihre Definition könnte in der umgebenden Klasse residieren, es bieten sich also Instanzvariablen
der Klasse `DFSGraph` an:

```cpp
bool findAny(int source, int target, vector path) {    

    // mark current node as discovered: 
    discovered[source] = true;

    // include current node into possible result path
    path.push (source);

    // if destination vertex is found, we're done (path describes result)
    if (source == target) {
        return true;
    }

    for all neighbours n of source {
        //  n is not discovered
        if (discovered[n] == false) { 
            // return true if destination is found recursively
            if (findAny (n, target, path))
                return true;
        }
    }

    // backtrack: remove current node from possible result path
    path.pop();

    // destination vertex is not reachable from source node
    return false;
}
```

Zum Testen ihrer Realisierung legen Sie bitte den Graphen aus der folgenden Abbildung zugrunde:

<img src="graphs_03_DFS_Testgraph.png" width="300">

Abbildung 5: Graph zum Testen des *Depth-First Search* Algorithmus.

Wir erkennen in Abbildung 5, dass es vom Knoten 0 zum Knoten 7 zwei Pfade gibt: 

0 => 3  => 4  => 6  => 7

und

0  => 3 => 5  => 6  => 7

Welchen der beiden Pfade erhalten Sie bei Ihrer Realisierung als Ergebnis?


### Weiterarbeit: 

Der *Depth-First Search* Algorithmus lässt ohne großen Aufwand so erweitern, dass er nicht nur einen, 
sondern alle Pfade zwischen zwei vorgegebenen Knoten ermittelt. Modifizieren Sie Ihre Realisierung entsprechend ab.

Eine Hilfestellung gibt folgende Pseudocode-Darstellung:

```cpp
bool findAll (int source, int target) {   

    // clear all flags in 'discovered'

    vector currentPath;

    currentPath.push (source);

    findAllHelper (source, target, currentPath);
}
```

und

```cpp
bool findAllHelper (int source, int target, vector path) {    

    // mark current node as discovered: 
    discovered[source] = true;

    // if destination vertex is found, we're done (path describes result)
    if (source == target) {
        
        // store found solution aside
        all_solutions.push(path);
        return;
    }

    for all neighbours n of source {
        //  n is not discovered
        if (discovered[n] == false) { 
            path.push (source);
            findAllHelper (n, target, path))
            path.pop();
        }
    }

    // unmark current node as discovered
    discovered[source] = false;
}
```

Wählen Sie wiederum den Graphen aus Abbildung 5 zum Testen. Wieviel Pfade gibt es zwischen den Knoten 1 und 6?

*Antwort*:

```cpp
Found 4 solutions:
1 -> 0 -> 3 -> 4 -> 6
1 -> 0 -> 3 -> 5 -> 6
1 -> 4 -> 3 -> 5 -> 6
1 -> 4 -> 6
```

### Eingabe aus Datei

Graphen können anstatt im Quellcode "hart codiert" auch flexibler in einer separaten Datei beschrieben werden.
Ändert man diese Datei, muss man das Programm nicht neu übersetzen.
Das Format könnte bei dem bisherigen Beispiel so aussehen:

```cpp
8       # number of nodes
11      # number of edges
0  3    # list of edges (source, target)
1  0
1  2
1  4
2  7
3  4
3  5
4  3
4  6
5  6 
6  7
```
Ergänzen Sie Ihre Implementierung um eine Eingabe des Graphgen aus Dateien dieses Formats.


##### Bezug zur STL:

Folgende Elemente der STL können Anwendung finden:

###### Container:

`std::vector<>`, `std::deque<>`, `std::list<>`, `std::initializer_list`

###### Iteratoren:

`std::vector<int>::iterator`, `std::vector<int>::reverse_iterator`, `std::back_inserter`

###### Algorithmen:

`std::for_each`, `std::reverse`, `std::fill`, `std::generate`, `std::begin`, `std::end`, `std::tuple_size`

---

[Zurück](Readme.md)

---

