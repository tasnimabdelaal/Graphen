#include "dijkstra.h"
#include <queue>
#include <vector>
#include <climits>
#include <iostream>

PathResult dijkstra(const Graph& graph,
                    const std::string& startName,
                    const std::string& goalName) {

    PathResult result;
    result.found = false;
    result.totalCost = 0;

    // Stationen im Graphen suchen
    auto startIt = graph.nameToId.find(startName);
    auto goalIt  = graph.nameToId.find(goalName);

    if (startIt == graph.nameToId.end()) {
        std::cerr << "Fehler: Startstation '" << startName << "' nicht gefunden.\n";
        return result;
    }
    if (goalIt == graph.nameToId.end()) {
        std::cerr << "Fehler: Zielstation '" << goalName << "' nicht gefunden.\n";
        return result;
    }

    int start = startIt->second;
    int goal  = goalIt->second;
    int n     = graph.idToName.size();

    // Distanzen: am Anfang alle unendlich
    std::vector<int> dist(n, INT_MAX);
    // Vorgaenger: von welchem Knoten kamen wir?
    std::vector<int> prev(n, -1);
    // Welche Linie haben wir verwendet um zu diesem Knoten zu kommen?
    std::vector<std::string> prevLine(n, "");

    dist[start] = 0;

    // Priority Queue: (Distanz, KnotenID) - kleinste Distanz zuerst
    // Mit pair<int,int> sortiert C++ automatisch nach dem ersten Element
    std::priority_queue<std::pair<int,int>,
                        std::vector<std::pair<int,int>>,
                        std::greater<std::pair<int,int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        // Veralteten Eintrag in der Queue ignorieren
        if (currentDist > dist[u]) continue;

        // Ziel erreicht - fertig!
        if (u == goal) break;

        // Alle Nachbarn von u pruefen
        for (const Edge& edge : graph.adj[u]) {
            int newDist = dist[u] + edge.cost;

            // Besserer Weg gefunden?
            if (newDist < dist[edge.to]) {
                dist[edge.to] = newDist;
                prev[edge.to] = u;
                prevLine[edge.to] = edge.line;
                pq.push({newDist, edge.to});
            }
        }
    }

    // Kein Pfad gefunden
    if (dist[goal] == INT_MAX) {
        return result;
    }

    // Pfad rekonstruieren: rueckwaerts vom Ziel zum Start
    std::vector<PathStep> reversedSteps;
    int current = goal;
    while (current != start) {
        int p = prev[current];
        PathStep step;
        step.from = graph.idToName[p];
        step.to   = graph.idToName[current];
        step.line = prevLine[current];
        // Kantenkosten herausfinden
        step.cost = 0;
        for (const Edge& e : graph.adj[p]) {
            if (e.to == current && e.line == prevLine[current]) {
                step.cost = e.cost;
                break;
            }
        }
        reversedSteps.push_back(step);
        current = p;
    }

    // Umkehren damit der Pfad von Start nach Ziel geht
    result.steps = std::vector<PathStep>(reversedSteps.rbegin(), reversedSteps.rend());
    result.found = true;
    result.totalCost = dist[goal];
    return result;
}
