# STL ALgorithmen

Die M�chtigkeit der STL beruht in erster Linie auf ihren Algorithmen, die mit Hilfe von Iteratoren
vielf�ltige Datenstrukturen (STL-Container) bearbeiten k�nnen.

Innerhalb der Menge der Algorithmen lassen sich gewisse Untergruppierungen vornehmen:

  * Nichtmodifizierende Algorithmen
  * Modifizierende Algorithmen
  * Partitionierung
  * Sortieren
  * Bin�res Suchen
  * Mischalgorithmen
  * Mengenalgorithmen
  * Heap Algorithmen
  * Minimum und Maximum

Der aktuelle Stand der Algorithmen kann unter <https://en.cppreference.com/w/cpp/algorithm> nachgelesen werden.

Um einen gewissen Eindruck vom Umfang und von der Funktionalit�t der STL-Algorithmen
zu vermitteln, finden Sie in der nachfolgenden Tabelle eine Aufstellung
aller *nichtmodifizierenden* Algorithmen vor:

| Algorithmus | Beschreibung |
|:-------------- |:------------|
| `all_of`</br>`any_of`</br>`none_of`</br> | Pr�ft, ob ein Pr�dikat f�r alle, einige oder keine der Elemente in einem Bereich wahr ist. |
| `for_each` | Wendet eine Funktion auf eine Reihe von Elementen an. |
| `for_each_n` | Wendet eine Funktion auf die ersten *n* Elemente einer Sequenz an. |
| `count`</br>`count_if`</br> | Gibt die Anzahl der Elemente zur�ck, die bestimmte Kriterien erf�llen. |
| `mismatch` | Findet die erste Position, an der sich zwei Bereiche unterscheiden. |
|  `find`</br>`find_if`</br>`find_if_not`</br> | Findet das erste Element, das bestimmte Kriterien erf�llt. |
| `find_end` | Findet die letzte Folge von Elementen in einem bestimmten Bereich. |
| `find_first_of` | Sucht nach einem Element aus einer Reihe von Elementen. |
| `adjacent_find` | Findet die ersten beiden benachbarten Elemente, die gleich sind (oder ein bestimmtes Pr�dikat erf�llen). |
| `search` | Sucht nach einer Reihe von Elementen. |
| `search_n` | Durchsucht einen Bereich nach mehreren aufeinanderfolgenden Kopien eines Elements. |

Tabelle 1. Nichtmodifizierende Algorithmen.

---

[Zur�ck](Readme.md)

---

