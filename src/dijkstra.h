#pragma once
#include "graph.h"
#include <string>
#include <vector>


struct PathStep {
    std::string from; 
    std::string to;
    std::string line; 
    int cost;          
};


struct PathResult {
    bool found;
    int totalCost;
    std::vector<PathStep> steps;
};


PathResult dijkstra(const Graph& graph,
                    const std::string& startName,
                    const std::string& goalName);
