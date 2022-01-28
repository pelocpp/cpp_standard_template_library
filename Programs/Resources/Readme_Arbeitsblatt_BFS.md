## Breadth-First Search (BFS) Algorithmus

Der BFS-Algorithmus kommt vor allem zum Einsatz bei der Suche nach dem *k�rzesten* Pfad in einem 
ungewichteten (gerichteten oder ungerichteten) Graphen.

Der BFS-Algorithmus findet die k�rzeste Entfernung aufgrund seines radialen Suchmusters,
das Knoten in der Reihenfolge ihrer Entfernung vom Startpunkt ber�cksichtigt


Eine (empfehlenswerte) Beschreibung gibt Willial Fiset in

https://www.youtube.com/watch?v=oDqjPvD54Ss (7 Minuten).

Implementieren Sie den BFS-Algorithmus in einer Klasse `BFSGraph`. Verwenden Sie geeignet in dieser Klasse
die Vorarbeiten der beiden Klassen `Edge` und `Graph`.


##### Bezug zur STL:

##### Das ist aller zu �berarbeiten !!!

Folgende Elemente der STL k�nnen Anwendung finden:

###### Container:

`std::vector<>`, `std::deque<>`, `std::initializer_list`

###### Iteratoren:

`std::vector<int>::iterator`, `std::vector<int>::reverse_iterator`, `std::back_inserter`

###### Algorithmen:

`std::for_each`, `std::reverse`, `std::fill`, `std::generate`, `std::begin`, `std::end`, `std::tuple_size`


## Test der Realisierung:

In *Abbildung* 1 finden Sie eine Landkarte mit Flugverbindungen innerhalb von Nordamerika vor. Sie k�nnen unschwer erkennen,
dass es mehrere M�glichkeiten gibt, von New York nach Los Angeles zu fliegen. Berechnen Sie mit Hilfe des BFS-Algorithmus
eine Verbindung, bei der Sie am wenigsten Umsteigen m�ssen.

<img src="FlightMap.png" width="400">

*Abbildung* 1: Flugverbindungen in Nordamerika.

*Bemerkung*: Die Frage nach der k�rzesten Flugstrecke (also m�glicherweise der �konomischsten Flugverbindung) 
betrachten wir sp�ter.

Beim Studium von *Abbildung* 1 k�nnen Sie folgende St�dte erkennen:

  * New York
  * Toronto
  * Chicago
  * Urbana
  * Houston
  * Denver
  * Calgary
  * Los Angeles

Dabei besteht zwischen folgenden St�dten eine Flugverbindung:

| Von | Nach |
| :-- | --|
| New York | Toronto |
| New York | Chicago |
| New York | Denver |
| Toronto | Chicago |
| Toronto | Calgary |
| Toronto | Los Angeles |
| Chicago | Denver |
| Houston | Los Angeles |
| Denver | Urbana |
| Denver | Houston |
| Denver | Los Angeles |

*Tabelle* 1. Flugverbindungen

#### 1. Aufgabe

Wir wollen annehmen, dass die Flugverbindungen aus *Tabelle* 2 f�r beide Richtungen gelten,
wir legen also einen ungerichteten Graphen zu Grunde.
Damit stellen wir die Frage: Wie kann man von New York nach Urbana fliegen,
ohne am wenigsten Umsteigen zu m�ssen?

#### 2. Aufgabe

Wir wollen annehmen, dass die Flugverbindungen aus *Tabelle* 2 nun nur f�r eine Richtung gelten:
Man kann also von New York nach Toronto fliegen, aber nicht von Toronto nach New York,
der zu Grunde liegende Graph muss gerichtet sein.
Damit stellen wir die Frage: Wie kann man von New York nach Urbana fliegen,
ohne am wenigsten Umsteigen zu m�ssen?

---

[Zur�ck](../../Readme.md)

---

