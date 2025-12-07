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

class Graph
{
private:
    Vertex graph[101];
    bool exists[101] = {false};

public:
    Graph() {}

    void addVertex(int index, const string &name, const string &city = "")
    {
        if (index < 1 || index > 100) return;
        graph[index] = Vertex(name, city);
        exists[index] = true;
    }

    void addEdge(int u, int v)
    {
        if (!exists[u] || !exists[v]) return;

        graph[u].connections.push_back(v);
        graph[v].connections.push_back(u);  // undirected
    }

    // ----------------------------------------------------------
    //          DEPTH LIMITED DFS (Max Depth = 2)
    // ----------------------------------------------------------
    void DFS(int start, int target)
    {
        bool visited[101] = {false};
        cout << "Path (depth ≤ 2): ";

        if (!dfsLimited(start, target, visited, 0))
            cout << "No path found";

        cout << endl;
    }

private:
    // depth-limited recursive DFS
    bool dfsLimited(int current, int target, bool visited[], int depth)
    {
        if (!exists[current]) return false;

        visited[current] = true;

        if (current == target)
        {
            cout << "<-- " << graph[current].name << "(" << graph[current].city << ")";
            return true;
        }

        if (depth >= 2)  // *** LIMIT: max depth = 2 ***
            return false;

        for (int neighbor : graph[current].connections)
        {
            if (!visited[neighbor])
            {
                if (dfsLimited(neighbor, target, visited, depth + 1))
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
    //      MUTUAL FRIENDS
    // ----------------------------------
    vector<int> mutualFriends(int u, int v)
    {
        vector<int> mutual;
        if (!exists[u] || !exists[v]) return mutual;

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

        for (int i = 1; i <= 100; i++)
        {
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

        for (int i = 1; i <= 100; i++)
        {
            if (!exists[i]) continue;

            for (int f : graph[i].connections)
            {
                if (i < f)
                    out << "  \"User_" << i << "\" -- \"User_" << f << "\";\n";
            }
        }

        out << "}\n";
        out.close();
    }
};


