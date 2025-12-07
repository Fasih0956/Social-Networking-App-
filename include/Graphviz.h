#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include "Graph.h"
#include "User.h"
using namespace std;

class Graphviz
{
public:
    // Generate DOT file for graph with up to 2 traversals from a starting user
    static void createGraph(Graph& g, int startId, const string& outputFile = "assets/graph2t.dot")
    {
        ofstream file(outputFile);
        if (!file) {
            cerr << "Error: Cannot create " << outputFile << endl;
            return;
        }

        // Graph header
        file << "graph G {\n";
        file << "    size=\"10,10!\";\n";
        file << "    nodesep=0.1;\n";
        file << "    ranksep=0.2;\n";
        file << "    node [shape=box, style=filled, fontname=\"Arial\", fontsize=8];\n\n";

        if (g.users.find(startId) == g.users.end()) {
            file << "}\n";
            file.close();
            return;
        }

        // BFS to get nodes within 2 traversals
        set<int> nodesToInclude;
        map<int, int> distance;
        queue<int> q;
        
        nodesToInclude.insert(startId);
        distance[startId] = 0;
        q.push(startId);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (distance[u] >= 2) continue; // Stop at 2 traversals

            for (int v : g.users[u].friends) {
                if (distance.find(v) == distance.end()) {
                    distance[v] = distance[u] + 1;
                    nodesToInclude.insert(v);
                    if (distance[v] < 2) {
                        q.push(v);
                    }
                }
            }
        }

        // Generate node definitions
        vector<string> colors = {"lightblue", "lightgreen", "lightpink", "yellow", 
                                 "orange", "violet", "cyan", "gold", "magenta", "lightgray"};
        int colorIndex = 0;

        for (int id : nodesToInclude) {
            if (g.users.find(id) == g.users.end()) continue;
            
            User& u = g.users[id];
            string color = colors[colorIndex % colors.size()];
            colorIndex++;

            file << "    \"User_" << id << "\" [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" ";
            file << "CELLSPACING=\"0\" CELLPADDING=\"2\" BGCOLOR=\"" << color << "\">";
            file << "<TR><TD>" << u.name << "</TD></TR>";
            if (!u.city.empty()) {
                file << "<TR><TD>" << u.city << "</TD></TR>";
            }
            file << "<TR><TD>#Friends: " << u.friends.size() << "</TD></TR>";
            file << "</TABLE>>];\n";
        }

        file << "\n";

        // Generate edges (only between included nodes)
        set<pair<int, int>> edgesAdded;
        for (int id : nodesToInclude) {
            if (g.users.find(id) == g.users.end()) continue;
            
            for (int friendId : g.users[id].friends) {
                if (nodesToInclude.find(friendId) != nodesToInclude.end()) {
                    // Avoid duplicate edges (undirected graph)
                    int u = min(id, friendId);
                    int v = max(id, friendId);
                    if (edgesAdded.find({u, v}) == edgesAdded.end()) {
                        file << "    \"User_" << id << "\" -- \"User_" << friendId << "\";\n";
                        edgesAdded.insert({u, v});
                    }
                }
            }
        }

        file << "}\n";
        file.close();
    }

    // Generate DOT file for shortest path visualization
    static void createShortestPath(Graph& g, int id1, int id2, const string& outputFile = "assets/graph.dot")
    {
        ofstream file(outputFile);
        if (!file) {
            cerr << "Error: Cannot create " << outputFile << endl;
            return;
        }

        file << "graph G {\n";
        file << "    size=\"10,10!\";\n";
        file << "    nodesep=0.1;\n";
        file << "    ranksep=0.2;\n";
        file << "    node [shape=box, style=filled, fontname=\"Arial\", fontsize=8];\n\n";

        vector<int> path = g.shortestPath(id1, id2);
        
        if (path.empty()) {
            file << "    \"User_" << id1 << "\" [label=\"User " << id1 << "\\n(No path found)\"];\n";
            file << "    \"User_" << id2 << "\" [label=\"User " << id2 << "\"];\n";
            file << "}\n";
            file.close();
            return;
        }

        // Color path nodes differently
        set<int> pathSet(path.begin(), path.end());

        // Add all nodes in path
        for (size_t i = 0; i < path.size(); i++) {
            int id = path[i];
            if (g.users.find(id) == g.users.end()) continue;
            
            User& u = g.users[id];
            string color = (i == 0 || i == path.size() - 1) ? "red" : "lightblue";
            
            file << "    \"User_" << id << "\" [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" ";
            file << "CELLSPACING=\"0\" CELLPADDING=\"2\" BGCOLOR=\"" << color << "\">";
            file << "<TR><TD>" << u.name << "</TD></TR>";
            if (!u.city.empty()) {
                file << "<TR><TD>" << u.city << "</TD></TR>";
            }
            file << "<TR><TD>Step " << i << "</TD></TR>";
            file << "</TABLE>>];\n";
        }

        file << "\n";

        // Add path edges (highlighted)
        for (size_t i = 0; i < path.size() - 1; i++) {
            file << "    \"User_" << path[i] << "\" -- \"User_" << path[i + 1] << "\" ";
            file << "[color=red, penwidth=3];\n";
        }

        // Add other edges (grayed out)
        set<pair<int, int>> pathEdges;
        for (size_t i = 0; i < path.size() - 1; i++) {
            int u = min(path[i], path[i + 1]);
            int v = max(path[i], path[i + 1]);
            pathEdges.insert({u, v});
        }

        for (int id : pathSet) {
            if (g.users.find(id) == g.users.end()) continue;
            
            for (int friendId : g.users[id].friends) {
                if (pathSet.find(friendId) != pathSet.end()) {
                    int u = min(id, friendId);
                    int v = max(id, friendId);
                    if (pathEdges.find({u, v}) == pathEdges.end()) {
                        file << "    \"User_" << id << "\" -- \"User_" << friendId << "\" ";
                        file << "[color=gray, style=dashed];\n";
                        pathEdges.insert({u, v});
                    }
                }
            }
        }

        file << "}\n";
        file.close();
    }

    // Generate DOT file for mutual connections visualization
    static void mutualConnectionGraph(Graph& g, int id1, int id2, const string& outputFile = "assets/graph.dot")
    {
        ofstream file(outputFile);
        if (!file) {
            cerr << "Error: Cannot create " << outputFile << endl;
            return;
        }

        file << "graph G {\n";
        file << "    size=\"10,10!\";\n";
        file << "    nodesep=0.1;\n";
        file << "    ranksep=0.2;\n";
        file << "    node [shape=box, style=filled, fontname=\"Arial\", fontsize=8];\n\n";

        vector<int> mutual = g.mutualFriends(id1, id2);
        set<int> nodesToInclude;
        nodesToInclude.insert(id1);
        nodesToInclude.insert(id2);
        nodesToInclude.insert(mutual.begin(), mutual.end());

        // Add user 1
        if (g.users.find(id1) != g.users.end()) {
            User& u1 = g.users[id1];
            file << "    \"User_" << id1 << "\" [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" ";
            file << "CELLSPACING=\"0\" CELLPADDING=\"2\" BGCOLOR=\"lightblue\">";
            file << "<TR><TD>" << u1.name << "</TD></TR>";
            if (!u1.city.empty()) {
                file << "<TR><TD>" << u1.city << "</TD></TR>";
            }
            file << "</TABLE>>];\n";
        }

        // Add user 2
        if (g.users.find(id2) != g.users.end()) {
            User& u2 = g.users[id2];
            file << "    \"User_" << id2 << "\" [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" ";
            file << "CELLSPACING=\"0\" CELLPADDING=\"2\" BGCOLOR=\"lightgreen\">";
            file << "<TR><TD>" << u2.name << "</TD></TR>";
            if (!u2.city.empty()) {
                file << "<TR><TD>" << u2.city << "</TD></TR>";
            }
            file << "</TABLE>>];\n";
        }

        // Add mutual friends (highlighted)
        for (int id : mutual) {
            if (g.users.find(id) == g.users.end()) continue;
            
            User& u = g.users[id];
            file << "    \"User_" << id << "\" [label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" ";
            file << "CELLSPACING=\"0\" CELLPADDING=\"2\" BGCOLOR=\"yellow\">";
            file << "<TR><TD>" << u.name << "</TD></TR>";
            if (!u.city.empty()) {
                file << "<TR><TD>" << u.city << "</TD></TR>";
            }
            file << "<TR><TD>Mutual Friend</TD></TR>";
            file << "</TABLE>>];\n";
        }

        file << "\n";

        // Add edges
        set<pair<int, int>> edgesAdded;
        
        // Edge from user1 to mutual friends
        if (g.users.find(id1) != g.users.end()) {
            for (int friendId : g.users[id1].friends) {
                if (nodesToInclude.find(friendId) != nodesToInclude.end()) {
                    int u = min(id1, friendId);
                    int v = max(id1, friendId);
                    if (edgesAdded.find({u, v}) == edgesAdded.end()) {
                        string color = (find(mutual.begin(), mutual.end(), friendId) != mutual.end()) 
                                     ? "blue" : "gray";
                        file << "    \"User_" << id1 << "\" -- \"User_" << friendId << "\" ";
                        file << "[color=" << color << "];\n";
                        edgesAdded.insert({u, v});
                    }
                }
            }
        }

        // Edge from user2 to mutual friends
        if (g.users.find(id2) != g.users.end()) {
            for (int friendId : g.users[id2].friends) {
                if (nodesToInclude.find(friendId) != nodesToInclude.end()) {
                    int u = min(id2, friendId);
                    int v = max(id2, friendId);
                    if (edgesAdded.find({u, v}) == edgesAdded.end()) {
                        string color = (find(mutual.begin(), mutual.end(), friendId) != mutual.end()) 
                                     ? "green" : "gray";
                        file << "    \"User_" << id2 << "\" -- \"User_" << friendId << "\" ";
                        file << "[color=" << color << "];\n";
                        edgesAdded.insert({u, v});
                    }
                }
            }
        }

        file << "}\n";
        file.close();
    }

    // Generate PNG image from DOT file using Graphviz
    static bool createImage(const string& dotFile = "assets/graph.dot", const string& outputFile = "assets/graph.png")
    {
        string command = "dot -Tpng " + dotFile + " -o " + outputFile;
        int result = system(command.c_str());
        return result == 0;
    }
};
