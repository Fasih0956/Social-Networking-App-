#pragma once
#include <string>
#include "Graphviz.h"
#include "Graph.h"

// Simple wrapper functions for graph visualization
// These match the proposal requirements

void createGraph(Graph& g, int id1, const std::string& outputFile = "graph.dot")
{
    Graphviz::createGraph(g, id1, outputFile);
    Graphviz::createImage(outputFile);
}

void createShortestPath(Graph& g, int id1, int id2, const std::string& outputFile = "graph.dot")
{
    Graphviz::createShortestPath(g, id1, id2, outputFile);
    Graphviz::createImage(outputFile);
}

void mutualConnectionGraph(Graph& g, int id1, int id2, const std::string& outputFile = "graph.dot")
{
    Graphviz::mutualConnectionGraph(g, id1, id2, outputFile);
    Graphviz::createImage(outputFile);
}

std::string generateStatistics(Graph& g, int id1)
{
    if (g.users.find(id1) == g.users.end()) {
        return "User not found";
    }
    
    int deg = g.degree(id1);
    double clustering = g.clusteringCoefficient(id1);
    int influence = g.influenceScore(id1);
    
    return "Degree: " + std::to_string(deg) + 
           " Clustering: " + std::to_string(clustering) + 
           " Influence: " + std::to_string(influence);
}
