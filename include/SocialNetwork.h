#pragma once
#include <iostream>
#include "Graph.h"
#include "Parser.h"
using namespace std;

class SocialNetwork
{
public:
    Graph g;
    int nextPostID = 1;

    void loadData(const string& assetPath = "assets/")
    {
        auto names = Parser::loadNames(assetPath + "names.txt");
        auto cities = Parser::loadCities(assetPath + "cities.txt");
        auto adj = Parser::loadAdjList(assetPath + "friends.txt");

        // add users
        for(auto &p:names)
        {
            string city = cities.count(p.first)? cities[p.first] : "";
            g.addUser(p.first,p.second,city);
        }

        // add friendships
        for(int i=1;i<=100;i++)
            for(int f:adj[i])
                g.addFriendship(i,f);
    }

    void printUserInfo(int id)
    {
        if(g.users.find(id)==g.users.end()) {cout<<"No such user\n"; return;}
        auto &u=g.users[id];
        cout<<"User "<<id<<": "<<u.name<<" ("<<u.city<<")\n";
        cout<<"Friends: "; for(int f:u.friends) cout<<f<<" "; cout<<endl;
        cout<<"Degree: "<<g.degree(id)<<endl;
        cout<<"Clustering Coefficient: "<<g.clusteringCoefficient(id)<<endl;
        cout<<"Influence Score: "<<g.influenceScore(id)<<endl;
    }
};
