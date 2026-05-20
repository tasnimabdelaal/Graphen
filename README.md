# find_path – Shortest Path im Wiener Verkehrsnetz

## Kompilieren (g++)
```
g++ -std=c++17 -o find_path src/main.cpp src/graph.cpp src/dijkstra.cpp
```

## Verwendung
```
find_path <graphdatei> <startstation> <zielstation>
```

## Beispiele
```
find_path data/wien.txt "Stephansplatz" "Praterstern"
find_path data/wien.txt "Heiligenstadt" "Reumannplatz"
find_path data/wien.txt "Floridsdorf" "Karlsplatz"
```

## Projektstruktur
```
find_path/
├── src/
│   ├── main.cpp        – Einstiegspunkt, Ausgabe
│   ├── graph.h/.cpp    – Graph einlesen, Datenstruktur
│   └── dijkstra.h/.cpp – Dijkstra Algorithmus
└── data/
    └── wien.txt        – Wiener Verkehrsnetz
```

## Algorithmus
Dijkstra mit einer Min-Priority-Queue (std::priority_queue mit greater<>).
Laufzeit: O((V + E) * log V)
