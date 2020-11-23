# STL Container

## Grundlagen

Ein STL-Container ist eine Sammlung von Objekten desselben Typs (die Elemente).

  * Ein Container *besitzt* die Elemente.
      * Erzeugung und Zerst�rung werden vom Container gesteuert.

Man unterscheidet zwei grundlegende Arten von Beh�ltern:

  * Sequenzielle Container
      * Der Benutzer steuert die Reihenfolge der Elemente
      * `std::vector`, `std::list`, `std::deque`
  * Assoziative Container
      * Der Container steuert die Position der darin enthaltenen Elemente
      * Auf die Elemente kann nur mit einem *Schl�ssel* zugegriffen werden
      * `std::set`, `std::multiset`, `std::map`, `std::multimap`

<img src="stl_container_sequence_vs_associative.png" width="300">

Abbildung 1: Sequenzielle und assoziative Container.


## Allgemeine Container Konzepte

Folgende programmiersprachlichen Merkmale werden von allen Containern unterst�tzt:

  * Standard-Konstruktor

  * Kopier-Konstruktor und Wertzuweisung: *deep copy* Strategie

  * `swap`
      * `a.swap(b)` und `std::swap(a, b)`

  * ==, !=
      * Es wird der *Inhalt* verglichen.  Dabei m�ssen die Elemente im Container in derselben Reihenfolge vorliegen.

  * Vergleich der Reihenfolge

      * So genannte *lexikographische Reihenfolge*: Das erste ungleiche Element entscheidet die Reihenfolge.

         ```cpp
        std::vector<int> a{ 1, 2, 3 };
        std::vector<int> b{ 1, 3, 2 };
        assert(a < b);
         ```

  * `begin()`, `end()`

  * `size()`, `empty()`, `max_size()`

  * Instanzvariablen

      * `value_type`
      * `reference` (in Bezug auf `value_type`)
      * `const_reference`
      * `iterator`
      * `const_iterator`
      * `difference_type` (bezieht sich auf Iteratoren)
      * `size_type` (in der Regel `size_t`)

Ein reversibler Container hat zus�tzlich folgende Eigenschaften:

  * `rbegin()`, `rend()`

  * Instanzvariablen

      * `reverse_iterator`
      * `const_reverse_iterator`

## Allgemeine Konzepte eines sequenziellen Containers

Gemeinsame Eigenschaften aller sequenziellen Container:

  * Konstruktoren
      * Konstruktor `Container(n, val)` f�llt den Container mit `n` Kopien von `val`.
      * *Standardf�llkonstruktor* `Container(n)` f�llt den Container mit `n` Defaultwerten.
      * Bereichskonstruktor `Container(i,j)` f�llt Beh�lter mit dem Inhalt des Iterators im Bereich `[i, j)`.

  * `assign`
      * Zuweisung `(n, val)` - f�llt den Container mit `n` Werten des Wert `val`.
      * Bereichszuweisung `(i, j)` - `i` und `j` stehen f�r Iteratoren und beschreiben einen Bereich, der zugewiesen wird.
      * alte Elemente werden zugewiesen bzw. zerst�rt

  * `insert`
      * `insert(pos, val)` f�gt `val` unmittelbar vor der Position ein, auf die der Iterator `pos` zeigt .
      * `insert(pos, n, val)` f�gt `n` Kopien ein.
      * `insert(pos, i, j)` f�gt den Inhalt des Bereichs `[i, j)` ein.

  * `erase`
      * `erase(p)` l�scht das Element, auf das der Iterator `p` zeigt.
      * `erase(p, q)` l�scht den Bereich `[p, q)`

  * `clear`
      *  l�scht alle Elemente im Container.


## Allgemeine Konzepte eines assoziativen Containers

Die assoziativen STL-Standardcontainer (`std::set` , `std::multiset` , `std::map` , `std::multimap`) erm�glichen
den Zugriff auf Elemente mit Hilfe eines Schl�ssels:

  * F�r `std::set` und `std::multiset` ist das Element ein eigener Schl�ssel.

  * F�r `std::map` und `std::multimap` sind die Elemente vom Typ `std::pair<const Key, T>`.

  * `std::pair` ist eine Standard-Templateklasse, sie ist definiert als:

    ```cpp
    template <class T, class U>
    struct pair {
      T first;
      U second;
    
      // some constructors
    };
     ```

  * `std::set` und `std::map` enthalten h�chstens ein Element zu einem Schl�ssel.

  * `std::multiset` und `std::multimap` k�nnen mehrere Elemente desselben Schl�ssels enthalten.

  * Die zugrunde liegende Datenstruktur ist ein ausgewogener Suchbaum (*balanced search tree*):

    * logarithmische Zugriffszeit
    * Iteration erfolgt in der Reihenfolge der Schl�sselwerte


## �berblick �ber alle STL-Container

### Sequenzielle Container

| STL-Container | Beschreibung |
|:-------------- |:-----------------------------------------|
| `std::array` | statisches zusammenh�ngendes Array |
| `std::vector` | dynamisches zusammenh�ngendes Array |
| `std::deque` | *double-ended queue* (Warteschlange)  |
| `std::forward_list` | einfach verkn�pfte lineare Liste |
| `std::list` | doppelt verkn�pfte lineare Liste |

Tabelle 1. Sequenzielle Container.


### Assoziative Container

| STL-Container | Beschreibung |
|:-------------- |:-----------------------------------------|
| `std::map` | Sammlung von Paaren von Schl�sseln und Werten |
| `std::set` | Sammlung von Schl�sseln (Werten), Menge |
| `std::multimap` | Wie `std::map`, derselbe Schl�ssel kann mehrmals vorhanden sein |
| `std::multiset` | Wie `std::set`, Schl�ssel k�nnen mehrfach vorkommen |

Tabelle 2. Assoziative Container.

*Bemerkung*: Die Container aus Tabelle 2 speichern ihre Elemente intern in einem ausgeglichenen BST (*"binary search tree"*).
Man kann folglich sagen, dass die Elemente sortiert (Schl�ssel) gespeichert sind.


### Ungeordnete assoziative Container

| STL-Container | Beschreibung |
|:-------------- |:-----------------------------------------|
| `std::unordered_map` | Wie `std::map`, nur eben unsortiert |
| `std::unordered_set` | Wie `std::set`, nur eben unsortiert |
| `std::unordered_multimap` | Wie `std::multimap`, nur eben unsortiert |
| `std::unordered_multiset` | Wie `std::multiset`, nur eben unsortiert |

Tabelle 3. Ungeordnete assoziative Container.

*Bemerkung*: Die Container aus Tabelle 3 speichern ihre Elemente intern in einer Hash-Tabelle.
Man kann folglich sagen, dass die Elemente nicht in sortierter Reihenfolge vorliegen, sondern in einer beliebigen
Reihenfolge abgelegt sind.


### Containeradapter

| STL-Container | Beschreibung |
|:-------------- |:-----------------------------------------|
| `std::stack` | LIFO Datenstruktur (*"last in - first out"*) |
| `std::queue` | FIFO Datenstruktur (*"fast in - first out"*) |
| `std::priority_queue` | Passt einen `std::queue`-Container an die Prinzipien einer Priorit�tswarteschlange an |

Tabelle 4. Containeradapter.

*Bemerkung*: Ein Containeradapter definiert - basierend auf einer vorhandenen Containerschnittstelle - eine neue
Schnittstelle, die gegen�ber dem zugrunde liegenden Container stark eingeschr�nkt ist. Insbesondere besitzen
Containeradapter *keine* Iteratoren. Der Zugriff auf seine Elemente ist deshalb nur �ber Methoden des
Adapterobjekts m�glich.

*Bemerkung*: Ein `std::priority_queue`-Objekt verh�lt sich �hnlich wie ein `std::queue`-Objekt, allerdings
mit dem Unterschied, dass die eingef�gten Elemente gem�� ihrer Priorit�t an die Spitze der Warteschlange
gelangen, wo sie dann beim n�chsten Zugriff entfernt werden. Es wird also immer das Element entfernt,
das die jeweils h�chste Priorit�t besitzt. Elemente mit gleicher Priorit�t werden in der Reihenfolge entfernt,
in der sie eingef�gt wurden.

### `std::span`

| STL-Container | Beschreibung |
|:-------------- |:-----------------------------------------|
| `std::span` | Ein `std::span`-Objekt ist eine Ansicht (*View*) �ber eine zusammenh�ngende Folge von Objekten, deren Speicher einem anderen Objekt geh�rt. |

Tabelle 5. Erweiterungen in C++ 20.


## C++ Cheat Sheet

Zu STL Containern findet sich im Internet ein Cheat Sheet, dass ich Ihnen an dieser Stelle nicht vorenthalten m�chte:

<img src="cpp_cheat_sheet.png" width="700">

Abbildung 2: Ein Cheat Sheet zu STL Containern.

---

[Zur�ck](Readme.md)

---

