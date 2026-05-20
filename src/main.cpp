#include <chrono>
#include <iostream>
#include <string>
#include "graph.h"
#include "dijkstra.h"

// Gibt den gefundenen Pfad uebersichtlich aus
void printResult(const PathResult& result) {
    if (!result.found) {
        std::cout << "Kein Pfad gefunden!\n";
        return;
    }

    std::cout << "\n========================================\n";
    std::cout << "  Kuerzester Pfad gefunden\n";
    std::cout << "========================================\n\n";

    std::string currentLine = "";
    for (int i = 0; i < (int)result.steps.size(); i++) {
        const PathStep& step = result.steps[i];

        // Linienwechsel = Umstieg
        if (step.line != currentLine) {
            if (!currentLine.empty()) {
                std::cout << "  >>> Umstieg auf Linie " << step.line << " <<<\n";
            } else {
                std::cout << "  Einsteigen: Linie " << step.line << "\n";
            }
            currentLine = step.line;
        }

        std::cout << "  [" << step.line << "] "
                  << step.from << " -> " << step.to
                  << " (" << step.cost << " min)\n";
    }

    std::cout << "\n----------------------------------------\n";
    std::cout << "  Gesamtfahrzeit: " << result.totalCost << " Minuten\n";
    std::cout << "========================================\n\n";
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Verwendung: find_path <graphdatei> <start> <ziel>\n";
        std::cerr << "Beispiel:   find_path wien.txt \"Stephansplatz\" \"Praterstern\"\n";
        return 1;
    }

    std::string filename = argv[1];
    std::string start    = argv[2];
    std::string goal     = argv[3];

    // Graph einlesen
    Graph graph;
    std::cout << "Lade Netzwerk aus '" << filename << "'...\n";
    if (!loadGraph(filename, graph)) {
        return 1;
    }
    std::cout << "Netzwerk geladen: " << graph.idToName.size() << " Stationen.\n";

    // Kuerzesten Pfad suchen
    std::cout << "\nSuche kuerzesten Weg von '" << start << "' nach '" << goal << "'...\n";

    // Zeitmessung starten
    auto startTime = std::chrono::high_resolution_clock::now();

    PathResult result = dijkstra(graph, start, goal);

    // Zeitmessung stoppen
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    std::cout << "Laufzeit: " << duration.count() << " Mikrosekunden\n";

    // Ergebnis ausgeben
    printResult(result);

    return 0;
}