#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

class Parser
{
public:

    
    // Load ID -> Name mapping
    
    static map<int,string> loadNames(const string &filename)
    {
        map<int,string> names;
        ifstream file(filename);
        if (!file)
        {
            cerr << "Cannot open " << filename << endl;
            return names;
        }

        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue;

            int id;
            char colon;
            string name;

            stringstream ss(line);
            ss >> id >> colon;   // reads "1:" correctly
            getline(ss, name);

            names[id] = name;
        }
        return names;
    }

    
    // Load ID -> City mapping
    
    static map<int,string> loadCities(const string &filename)
    {
        map<int,string> cities;
        ifstream file(filename);
        if (!file)
        {
            cerr << "Cannot open " << filename << endl;
            return cities;
        }

        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue;

            int id;
            char colon;
            string city;

            stringstream ss(line);
            ss >> id >> colon;
            getline(ss, city);

            cities[id] = city;
        }
        return cities;
    }

    
    // Load adjacency list from friends.txt
    
    static vector<vector<int>> loadAdjList(const string &filename)
    {
        vector<vector<int>> adj(101);

        ifstream file(filename);
        if (!file)
        {
            cerr << "Cannot open " << filename << endl;
            return adj;
        }

        string line;
        while (getline(file, line))
        {
            if (line.empty()) continue;

            int id;
            char colon;

            stringstream ss(line);
            ss >> id >> colon;

            int neighbor;
            while (ss >> neighbor)
                adj[id].push_back(neighbor);
        }

        return adj;
    }

    // Convert adjacency list -> adjacency matrix
    static vector<vector<int>> convertToMatrix(const vector<vector<int>> &adj)
    {
        vector<vector<int>> matrix(101, vector<int>(101, 0));

        for (int i = 1; i <= 100; i++)
        {
            for (int n : adj[i])
            {
                matrix[i][n] = 1;
                matrix[n][i] = 1;     // undirected
            }
        }

        return matrix;
    }

};
