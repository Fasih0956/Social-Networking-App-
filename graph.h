#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <map>
using namespace std;

struct Vertex
{
    string name;
    string city;
    vector<int> connections;

    Vertex() {}
    Vertex(string name, string city = "") : name(name), city(city) {}
};

// Example: assign a color to each city
map<string, string> cityColors = {
    {"Karachi", "lightblue"},
    {"Lahore", "lightgreen"},
    {"Islamabad", "lightpink"},
    {"Rawalpindi", "yellow"},
    {"Faisalabad", "orange"},
    {"Multan", "violet"},
    {"Hyderabad", "cyan"},
    {"Gujranwala", "gold"},
    {"Sialkot", "magenta"},
    {"Quetta", "salmon"}};

class Graph
{
private:
    Vertex graph[101];
    bool exists[101] = {false};
    bool explored[101];

public:
    Graph()
    {
        // ensure explored array is initialized
        resetExplored();
    }

    void resetExplored()
    {
        for (int i = 0; i < 100; i++)
            explored[i] = false;
    }

    void addVertex(int index, const string &name, const string &city = "")
    {
        if (index < 0 || index >= 100)
            return;
        graph[index] = Vertex(name, city);
        exists[index] = true;
    }

    void addEdge(int u, int v)
    {
        if (!exists[u] || !exists[v])
            return;

        graph[u].connections.push_back(v);
        graph[v].connections.push_back(u); // undirected
    }
    // ----------------------------------------------------------
    //          DFS
    // ----------------------------------------------------------

    void DFS(int start, int target)
    {
        bool explored[101] = {false};
        cout << "Path: ";
        if (!dfsRecursive(start, target, explored))
            cout << "No path found";
        cout << endl;
    }

private:
    bool dfsRecursive(int current, int target, bool explored[])
    {
        if (!exists[current])
            return false;
        if (current == target)
        {
            cout << "<-- " << graph[current].name << "(" << graph[current].city << ")";
            return true;
        }
        explored[current] = true;
        for (int n : graph[current].connections)
        {
            if (!explored[n])
            {
                if (dfsRecursive(n, target, explored))
                {
                    cout << "<-- " << graph[current].name << "(" << graph[current].city << ")";
                    return true;
                }
            }
        }
        return false;
    }

public:
    // ----------------------------------
    //      MUTUAL FRIENDS FUNCTION
    // ----------------------------------
    vector<int> mutualFriends(int u, int v)
    {
        vector<int> mutual;
        if (!exists[u] || !exists[v])
            return mutual;

        bool isFriend[101] = {false};
        for (int f : graph[u].connections)
            isFriend[f] = true;

        for (int f : graph[v].connections)
            if (isFriend[f])
                mutual.push_back(f);

        return mutual;
    }

    // ----------------------------------
    //      EXPORT TO GRAPHVIZ
    // ----------------------------------
    void exportToGraphviz(const string &filename, map<string,string> &cityColors)
{
    ofstream out(filename);
    out << "graph G {\n";
    out << "  node [shape=box, style=filled, fontname=\"Arial\"];\n";

    for (int i = 1; i <= 100; i++) {
        if (!exists[i]) continue;
        string nodeID = "User_" + to_string(i);
        string color = "white";
        if (!graph[i].city.empty() && cityColors.count(graph[i].city))
            color = cityColors[graph[i].city];

        string label = "<"
            "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" BGCOLOR=\"" + color + "\">"
            "<TR><TD>" + graph[i].name + "</TD></TR>"
            "<TR><TD>" + graph[i].city + "</TD></TR>"
            "<TR><TD>#Friends: " + to_string(graph[i].connections.size()) + "</TD></TR>"
            "</TABLE>>";

        out << "  \"" << nodeID << "\" [label=" << label << "];\n";
    }

    // edges
    for (int i = 1; i <= 100; i++) {
        if (!exists[i]) continue;
        string nodeA = "User_" + to_string(i);
        for (int f : graph[i].connections) {
            if (i < f) {
                string nodeB = "User_" + to_string(f);
                out << "  \"" << nodeA << "\" -- \"" << nodeB << "\";\n";
            }
        }
    }

    out << "}\n";
    out.close();
}

};
