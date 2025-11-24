#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Graph.h"
using namespace std;

Graph g;
map<int, string> userNames;
map<int, string> userCities;

void loadNames(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Cannot open names file\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        int id;
        char colon;
        string name;
        stringstream ss(line);
        ss >> id >> colon;
        getline(ss, name);
        userNames[id] = name;
    }
}

void loadCities(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Cannot open cities file\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        int id;
        char colon;
        string city;
        stringstream ss(line);
        ss >> id >> colon;
        getline(ss, city);
        userCities[id] = city;
    }
}

void loadFriendshipData(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Cannot open friendship file\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        int user;
        char colon;
        ss >> user >> colon;

        string name = userNames.count(user) ? userNames[user] : "User" + to_string(user);
        string city = userCities.count(user) ? userCities[user] : "";

        g.addVertex(user, name, city);

        int friendID;
        while (ss >> friendID)
        {
            string friendName = userNames.count(friendID) ? userNames[friendID] : "User" + to_string(friendID);
            string friendCity = userCities.count(friendID) ? userCities[friendID] : "";
            g.addVertex(friendID, friendName, friendCity);
            g.addEdge(user, friendID);
        }
    }
}

int main()
{
    // Load data
    loadNames("names.txt");
    loadCities("cities.txt");
    loadFriendshipData("friends.txt");

    map<string, string> cityColors = {
        {"Karachi", "lightblue"}, {"Lahore", "lightgreen"}, {"Islamabad", "lightpink"}, {"Rawalpindi", "yellow"}, {"Faisalabad", "orange"}, {"Multan", "violet"}, {"Hyderabad", "cyan"}, {"Gujranwala", "gold"}, {"Sialkot", "magenta"}, {"Quetta", "salmon"}};

    g.exportToGraphviz("graph.dot", cityColors);

    // Mutual friends
    vector<int> m = g.mutualFriends(1, 2);
    cout << "Mutual friends of 1 and 2:\n";
    for (int x : m)
        cout << x << " ";
    cout << endl;

    // DFS path test
    g.DFS(1, 10);

    return 0;
}
