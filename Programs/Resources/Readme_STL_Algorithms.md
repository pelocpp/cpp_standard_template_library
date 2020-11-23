# STL ALgorithmen

Die Mächtigkeit der STL beruht in erster Linie auf ihren Algorithmen, die mit Hilfe von Iteratoren
vielfältige Datenstrukturen (STL-Container) bearbeiten können.

Innerhalb der Menge der Algorithmen lassen sich gewisse Untergruppierungen vornehmen:

  * Nichtmodifizierende Algorithmen
  * Modifizierende Algorithmen
  * Partitionierung
  * Sortieren
  * Binäres Suchen
  * Mischalgorithmen
  * Mengenalgorithmen
  * Heap Algorithmen
  * Minimum und Maximum

Der aktuelle Stand der Algorithmen kann unter <https://en.cppreference.com/w/cpp/algorithm> nachgelesen werden.

Um einen gewissen Eindruck vom Umfang und von der Funktionalität der STL-Algorithmen
zu vermitteln, finden Sie in der nachfolgenden Tabelle eine Aufstellung
aller *nichtmodifizierenden* Algorithmen vor:

| Algorithmus | Beschreibung |
|:-------------- |:------------|
| `all_of`</br>`any_of`</br>`none_of`</br> | Prüft, ob ein Prädikat für alle, einige oder keine der Elemente in einem Bereich wahr ist. |
| `for_each` | Wendet eine Funktion auf eine Reihe von Elementen an. |
| `for_each_n` | Wendet eine Funktion auf die ersten *n* Elemente einer Sequenz an. |
| `count`</br>`count_if`</br> | Gibt die Anzahl der Elemente zurück, die bestimmte Kriterien erfüllen. |
| `mismatch` | Findet die erste Position, an der sich zwei Bereiche unterscheiden. |
|  `find`</br>`find_if`</br>`find_if_not`</br> | Findet das erste Element, das bestimmte Kriterien erfüllt. |
| `find_end` | Findet die letzte Folge von Elementen in einem bestimmten Bereich. |
| `find_first_of` | Sucht nach einem Element aus einer Reihe von Elementen. |
| `adjacent_find` | Findet die ersten beiden benachbarten Elemente, die gleich sind (oder ein bestimmtes Prädikat erfüllen). |
| `search` | Sucht nach einer Reihe von Elementen. |
| `search_n` | Durchsucht einen Bereich nach mehreren aufeinanderfolgenden Kopien eines Elements. |

Tabelle 1. Nichtmodifizierende Algorithmen.

---

[Zurück](Readme.md)

---

