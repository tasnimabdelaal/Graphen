#include "graph.h"
#include <fstream>
#include <sstream>
#include <iostream>

int getOrAddStation(const std::string& name, Graph& graph) {
    // Station bereits bekannt?
    if (graph.nameToId.find(name) != graph.nameToId.end()) {
        return graph.nameToId[name];
    }
    // Neue Station anlegen
    int id = graph.idToName.size();
    graph.nameToId[name] = id;
    graph.idToName.push_back(name);
    graph.adj.push_back({});
    return id;
}

bool loadGraph(const std::string& filename, Graph& graph) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Fehler: Datei '" << filename << "' konnte nicht geoeffnet werden.\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Linienname: alles vor dem ersten ':'
        int colonPos = line.find(':');
        if (colonPos == (int)std::string::npos) continue;
        std::string lineName = line.substr(0, colonPos);

        // Rest der Zeile parsen
        std::istringstream ss(line.substr(colonPos + 1));
        std::vector<std::string> stations;
        std::vector<int> costs;

        std::string token;
        while (ss >> token) {
            if (token[0] == '"') {

                std::string stationName = token.substr(1);
                while (!stationName.empty() && stationName.back() != '"') {
                    std::string part;
                    if (!(ss >> part)) break;
                    stationName += " " + part;
                }
                
                if (!stationName.empty() && stationName.back() == '"')
                    stationName.pop_back();
                stations.push_back(stationName);
            } else {
                // Zahl = Fahrzeit zur naechsten Station
                try {
                    costs.push_back(std::stoi(token));
                } catch (...) {
                    
                }
            }
        }

        // Kanten einfuegen: zwischen je zwei aufeinanderfolgenden Stationen
        // costs[i] ist die Zeit zwischen stations[i] und stations[i+1]
        for (int i = 0; i < (int)costs.size() && i + 1 < (int)stations.size(); i++) {
            int u = getOrAddStation(stations[i],     graph);
            int v = getOrAddStation(stations[i + 1], graph);

            // Bidirektional: man kann in beide Richtungen fahren
            graph.adj[u].push_back({v, costs[i], lineName});
            graph.adj[v].push_back({u, costs[i], lineName});
        }
    }

    return true;
}
