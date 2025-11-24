#include "Graph.h"

Graph g;

void loadFriendshipData(const string &filename)
{
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        int user;
        char colon;
        ss >> user >> colon;

        g.addVertex(user, "User" + to_string(user));

        int f;
        while (ss >> f)
        {
            g.addVertex(f, "User" + to_string(f));
            g.addEdge(user, f);
        }
    }
}

int main()
{
    loadFriendshipData("friends.txt");

    // Mutual friends
    vector<int> m = g.mutualFriends(1, 2);
    cout << "Mutual friends of 1 and 2:\n";
    for (int x : m) cout << x << " ";
    cout << endl;

    // Graphviz output
    g.exportToGraphviz("graph.dot");

    // DFS test
    g.DFS(1, 10);

    return 0;
}
