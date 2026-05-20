#pragma once
#include <string>
#include <vector>
#include <unordered_map>

// Eine Kante im Graphen
struct Edge {
    int to;           // ID der Zielstation
    int cost;         // Fahrzeit in Minuten
    std::string line; // Linienname (z.B. "U1", "13A")
};

// Der Graph mit allen Stationen und Verbindungen
struct Graph {
    std::vector<std::vector<Edge>> adj;          // Adjazenzliste
    std::unordered_map<std::string, int> nameToId; // Stationsname -> ID
    std::vector<std::string> idToName;             // ID -> Stationsname
};

// Gibt die ID einer Station zurueck, legt sie neu an falls noch nicht vorhanden
int getOrAddStation(const std::string& name, Graph& graph);

// Liest die Graphdatei ein und befuellt den Graphen
// Gibt false zurueck wenn die Datei nicht geoeffnet werden konnte
bool loadGraph(const std::string& filename, Graph& graph);
