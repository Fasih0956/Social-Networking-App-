#include <iostream>
#include "Graph.h"
#include "Parser.h"
using namespace std;

class SocialNetwork
{
public:
    Graph g;
    int nextPostID = 1;

    void loadData()
    {
        auto names = Parser::loadNames("../assets/names.txt");
        auto cities = Parser::loadCities("../assets/cities.txt");
        auto adj = Parser::loadAdjList("../assets/friends.txt");

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

    // Add post
    void addPost(int userID, const string &content)
    {
        g.users[userID].addPost(content,nextPostID++);
    }

    void addLike(int userID, int friendID, int postIndex)
    {
        g.users[friendID].addLike(postIndex);
    }

    void addComment(int userID, int friendID, int postIndex, const string &comment)
    {
        g.users[friendID].addComment(postIndex,userID,comment);
    }

    void addFriend(int u, int v)
    {
        g.addFriendship(u,v);
    }

    void printUserInfo(int id)
    {
        if(g.users.find(id)==g.users.end()) {cout<<"No such user\n"; return;}
        auto &u=g.users[id];
        cout<<"User "<<id<<": "<<u.name<<" ("<<u.city<<")\n";
        cout<<"Friends: "; for(int f:u.friends) cout<<f<<" "; cout<<endl;
        cout<<"Followers: "; for(int f:u.followers) cout<<f<<" "; cout<<endl;
        cout<<"Following: "; for(int f:u.following) cout<<f<<" "; cout<<endl;
        cout<<"Posts:\n";
        for(auto &p:u.posts)
        {
            cout<<"["<<p.id<<"] "<<p.content<<" Likes: "<<p.likes<<" Comments: "<<p.comments.size()<<"\n";
        }
        cout<<"Degree: "<<g.degree(id)<<" Clustering: "<<g.clusteringCoefficient(id)<<" Influence: "<<g.influenceScore(id)<<endl;
    }

};
