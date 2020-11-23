# STL (Standard Template Library)

## Einf�hrung

  * Teil der C++ Standard Library
  * eine Auswahl grundlegender Algorithmen, Datenstrukturen und verwandter Komponenten
  * Starke Verwendung von Templates (Schablonen), um Abstraktheit ohne Effizienzverlust zu erreichen
  * basierend auf generischer Programmierung

## Geschichte

  * 1979: erste Formulierung der Idee der generischen Programmierung (Alex Stepanov)
  * 1987: Entwicklung der Ada-Bibliothek (Alex Stepanov und Dave Musser)
  * 1994: C++ - Bibliothek (Alex Stepanov, Dave Musser und Meng Lee)
  * 1998: Entstehung von Teilen der C++ Standard Library

## Warum STL?

  * enth�lt viele n�tzliche Algorithmen und Datenstrukturen
  * Teil der C++ Standard Library
      * f�r fast jeden C++ - Programmierer verf�gbar
      * ... auch in Zukunft
      * viele Dokumentationen, Anleitungen, Beispiele usw. vorhanden
      * etablierte Programmiertechniken, Redewendungen und Stile
      * F�r C++ - Programmierer gut lesbar
      * sehr gut getestet
      * stark optimiert (es werden Optimierungen verwendet, die normalen Programmierern nicht zur Verf�gung stehen)
  * generische Programmierung
      * hochgradig anpassbar ohne Effizienzverlust
      * Modell f�r viele andere Algorithmus Bibliotheken
      * nah an der Implementierung eines abstrakten Algorithmus
  * Kritikpunkte
      * begrenzte Auswahl an Algorithmen und Datenstrukturen
      * Lernkurve
      * hohe Kompilierungszeit
      * manchmal schwer verst�ndliche Ausdr�cke
      * lange Fehlermeldungen
      * eingeschr�nkte Unterst�tzung f�r �ltere Compiler
      * Standard kann nicht ge�ndert werden

## Generische Programmierung

Das der STL zugrunde liegende Programmierparadigma wird als generische Programmierung bezeichnet. Hier ist eine Definition:

"Generische Programmierung ist eine Unterdisziplin der Informatik, die sich mit der Suche nach abstrakten Darstellungen effizienter Algorithmen,
Datenstrukturen und anderer Softwarekonzepte sowie mit ihrer systematischen Strukturierung befasst.
Ziel der generischen Programmierung ist es, Algorithmen und Datenstrukturen in einer leicht anpassbaren und
interoperablen Form auszudr�cken, um ihre direkte Verwendung
bei der Softwareentwicklung zu erm�glichen. Zu den wichtigsten Ideen geh�ren:

  * Formulierung von Algorithmen mit minimalen Annahmen �ber Datenabstraktionen, um sie so interoperabel wie m�glich zu machen.
  * Anhebung eines konkreten Algorithmus auf ein m�glichst allgemeines Niveau ohne Effizienzverlust, d.h. die abstrakteste Form, bei der das Ergebnis, wenn man sich auf den konkreten Fall spezialisiert, genauso effizient ist wie der urspr�ngliche Algorithmus.
  * Bereitstellung von mehr als einem generischen Algorithmus f�r denselben Zweck und auf derselben Abstraktionsebene, wenn keiner die anderen hinsichtlich der Effizienz f�r alle Eingaben dominiert. Dies f�hrt zur Notwendigkeit, ausreichend genaue Charakterisierungen der Dom�ne bereitzustellen, f�r die jeder Algorithmus am effizientesten ist."

## Hauptbestandteile

### Beh�lter

  * Datenstrukturen, die eine homogene Sammlung von Objekten enthalten
  * Klassenvorlagen, die nach Elementtyp parametrisiert sind
  * Beispiele:
      * `std::vector`
      * `std::list`
      * `std::set`
      * `std::map`

### Algorithmen

  * Funktionsvorlagen, die nach Argumenttyp parametrisiert sind
  * Beispiele:
      * `std::sort`
      * `std::find`
      * `std::copy`
      * `std::binary_search`
      * `std::for_each`

### Iteratoren

  * verallgemeinerte Zeiger
  * stellen Positionen in Containern dar
  * werden als Eingabe f�r Algorithmen verwendet
  * Abstraktionsschicht zwischen Algorithmen und Daten

<img src="stl_iterators.png" width="400">

Abbildung 1: STL-Iteratoren als Bindeglied der Container und Algorithmen.

## Ein einfaches Beispiel

Simulation des UNIX-Befehls `sort` in Grundform:

  1. Lesen Sie mehrere Zeilen von der Standardeingabe,
  2. sortiere diese und
  3. schreibe diese in die Standardausgabe:

```cpp
int main () {
    std::vector<std::string> vec;
    std::string tmp;

    while (std::getline(std::cin, tmp))
        vec.push_back(tmp);

    std::sort(std::begin(vec), std::end(vec));

    std::copy(
        std::begin(vec), 
        std::end(vec), 
        std::ostream_iterator<std::string>(std::cout, "\n")
    );
}
```

Das Beispiel zeigt bereits die Hauptkomponenten.

  * Container: `std::vector`
  * Algorithmen: `std::sort` und `std::copy`
  * Iteratoren: `std::begin`, `std::end` und `std::ostream_iterator<std::string>`

Die letzte Anweisung ist besonders bemerkenswert: Der Algorithmus `std::copy` kopiert
Elemente von einem Beh�lter in einen anderen. Das Ziel ist der Standardausgabestream `std::cout`, der
wie ein Container bestehend aus Zeichenfolgen aussieht.

---

[Zur�ck](Readme.md)

---

