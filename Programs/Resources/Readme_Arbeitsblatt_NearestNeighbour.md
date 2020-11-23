## Nearest-Neighbour Algorithmus

### Einleitung

Der Nearest-Neighbour Algorithmus (�N�chster-Nachbar Algorithmus�) ist ein heuristisches Verfahren
aus der Graphentheorie und wird unter anderem zur Approximation einer L�sung des Problems des Handlungsreisenden verwendet.

### Beschreibung

Zun�chst wird ein Knoten als Startknoten bestimmt ("Startpunkt der Reise"). Anschlie�end wird in jedem
Iterationsschritt aus der Menge aller benachbarten Knoten der mit dem k�rzesten Abstand bestimmt,
sofern dieser zuvor noch nicht besucht wurde.
Dieser Knoten wird als N�chstes in den gesuchten Weg aufgenommen.
Der Algorithmus ist beendet, sobald alle Knoten besucht wurden. Insbesondere m�ssen am Ende des Algorithmus der letzte bestimmte Knoten
und der Startknoten noch miteinander verbunden werden - unabh�ngig von deren Entfernung.

### Bewertung

Der Nearest-Neighbour Algorithmus ist eine sehr intuitive Herangehensweise an das Problem des Handlungsreisenden. Leider liefert dieser Greedy-Algorithmus nicht immer - oder genauer gesagt: nur selten - die beste L�sung.
Dies liegt haupts�chlich daran, dass der Startknoten und der Endknoten zu keinem Zeitpunkt ber�cksichtigt werden
und folglich eine m�gliche gro�e Distanz zwischen ihnen in Kauf genommen wird. 

### Implementierung

Realisieren Sie an Hand der Beschreibung des Nearest-Neighbour Algorithmus eine Methode `tsp` zur
Berechnung eines m�glichen Weges zur L�sung des Handlungsreisendenproblems.

Testen Sie Ihre Implementierung an einem einfachen, selbst-erstellten Beispiel mit 3, 4 oder 5 St�dten.

Beachten Sie bei der Erstellung des Graphen: Prinzipiell sollte der Reisende von einer Stadt *A* zu **allen**
anderen St�dten *B* des Graphen fahren k�nnen. Dies hei�t in anderen Worten:
Es m�ssen *alle* Knoten des Graphen miteinander verbunden sein.

Sollte das Problem sich mit "Entfernungen" besch�ftigen, dann sind in der Regel die Entfernungen von
*A* nach *B* und von *B* nach *A* dieselben. Wir sprechen in diesem Fall von einem *symmetrischen TSP*.
Ein symmetrisches TSP wird �blicherweise mit Hilfe eines *ungerichteten* Graphen dargestellt.
Es gen�gt pro Knotenpaar eine Kante mit der dazugeh�rigen Entfernung.

Es w�re aber auch denkbar, dass zwei Knoten in Hin- und R�ckrichtung ein unterschiedliches
Gewicht haben. In der Praxis w�rde das bedeuten, dass die verkehrstechnische Verbindung
zweier St�dte davon abh�ngt, in welche Richtung man f�hrt.
In diesem Fall bildet man das Problem auf einen *gerichteten* Graphen ab.

### Umfangreicher Test

Interessanter ist der Algorithmus erst bei der Betrachtung von Beispielen aus dem "*t�glichen Umfeld*". Unter

http://www.auslandversicherungen.de/entfernungstabelle.html

findet man eine Entfernungstabelle f�r 40 gr��ere St�dte Deutschlands vor:

<img src="Entfernungs_Tabelle_Deutschland.png" width="700">

Abbildung 1: Entfernungstabelle von Deutschland.

Hinweis: Mit etwas "Geschick" und Copy-Paste kann man die Daten aus der Web-Seite in ein C++-Programm �bernehmen -
man muss die Tabelle also nicht abtippen.

Testen Sie Ihre Realisierung am Beispiel der Entfernungstabelle von Deutschland.

---

[Zur�ck](Readme.md)

---

