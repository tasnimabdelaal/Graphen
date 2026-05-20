#pragma once
#include "graph.h"
#include <string>
#include <vector>

// Speichert einen Schritt auf dem gefundenen Pfad
struct PathStep {
    std::string from;  // Abfahrtsstation
    std::string to;    // Ankunftsstation
    std::string line;  // Verwendete Linie
    int cost;          // Kosten dieses Schritts
};

// Ergebnis der Pfadsuche
struct PathResult {
    bool found;                   // Wurde ein Pfad gefunden?
    int totalCost;                // Gesamtfahrzeit
    std::vector<PathStep> steps;  // Einzelne Schritte des Pfades
};

// Findet den kuerzesten Pfad von 'startName' nach 'goalName' im Graphen
// Verwendet Dijkstra's Algorithmus
PathResult dijkstra(const Graph& graph,
                    const std::string& startName,
                    const std::string& goalName);
