#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_set>
using namespace std;

struct Vertex
{
    string name;
    vector<int> connections;

    Vertex() {}
    Vertex(string name) : name(name) {}
    Vertex(string name, vector<int> c) : name(name), connections(c) {}
};

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

    void addVertex(int index, string name)
    {
        if (index < 0 || index >= 100)
            return;

        graph[index] = Vertex(name);
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

    bool DFS(int start, int target)
    {
        resetExplored();
        cout << "Path: ";
        bool found = dfsRecursive(start, target);
        cout << endl;
        return found;
    }


private:
    bool dfsRecursive(int current, int target)
    {
        if (!exists[current])
            return false;

        if (current == target)
        {
            cout << "<-- " << graph[current].name;
            return true;
        }

        explored[current] = true;

        for (int neighbor : graph[current].connections)
        {
            if (!explored[neighbor])
            {
                if (dfsRecursive(neighbor, target))
                {
                    cout << "<-- " << graph[current].name;
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
        vector<int> result;

        if (!exists[u] || !exists[v])
            return result;

        unordered_set<int> friendSet(graph[u].connections.begin(),
                                     graph[u].connections.end());

        for (int f : graph[v].connections)
        {
            if (friendSet.count(f))
                result.push_back(f);
        }

        return result;
    }

    // ----------------------------------
    //      EXPORT TO GRAPHVIZ
    // ----------------------------------
    void exportToGraphviz(const string &filename)
    {
        ofstream out(filename);
        out << "graph G {\n";

        for (int i = 1; i <= 100; i++)
        {
            if (!exists[i])
                continue;

            for (int f : graph[i].connections)
            {
                if (i < f) // avoid duplicate edges
                    out << "  " << i << " -- " << f << ";\n";
            }
        }

        out << "}\n";
        out.close();
    }
};
