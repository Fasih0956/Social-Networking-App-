#include <vector>
#include <map>
#include <iostream>
#include <queue>
#include<algorithm>
#include "User.h"
using namespace std;

class Graph
{
public:
    map<int, User> users; // userID -> User

    // -------------------------
    // Add user and friendship
    // -------------------------
    void addUser(int id, const string &name, const string &city="")
    {
        if(users.find(id)==users.end())
            users[id] = User(id,name,city);
    }

    void addFriendship(int u, int v)
    {
        if(users.find(u)==users.end() || users.find(v)==users.end()) return;

        // add to adjacency
        users[u].addFriend(v);
        users[v].addFriend(u);
    }

    // -------------------------
    // Degree of user
    // -------------------------
    int degree(int id)
    {
        if(users.find(id)==users.end()) return 0;
        return users[id].friends.size();
    }

    // -------------------------
    // Clustering coefficient
    // -------------------------
    double clusteringCoefficient(int id)
    {
        if(users.find(id)==users.end()) return 0.0;
        auto &f = users[id].friends;
        int k = f.size();
        if(k<2) return 0.0;

        int links=0;
        for(int i=0;i<k;i++)
            for(int j=i+1;j<k;j++)
            {
                int u=f[i], v=f[j];
                if(users[u].friends.end() != find(users[u].friends.begin(), users[u].friends.end(), v))
                    links++;
            }
        return 2.0*links/(k*(k-1));
    }

    // -------------------------
    // BFS shortest path
    // -------------------------
    vector<int> shortestPath(int start, int target)
    {
        vector<int> path;
        if(users.find(start)==users.end() || users.find(target)==users.end()) return path;

        map<int,int> parent;
        queue<int> q;
        q.push(start);
        parent[start]=-1;

        while(!q.empty())
        {
            int u=q.front(); q.pop();
            if(u==target) break;

            for(int v : users[u].friends)
            {
                if(parent.find(v)==parent.end())
                {
                    parent[v]=u;
                    q.push(v);
                }
            }
        }

        if(parent.find(target)==parent.end()) return path; // no path

        // reconstruct path
        for(int at=target; at!=-1; at=parent[at])
            path.insert(path.begin(), at);

        return path;
    }

    // -------------------------
    // Mutual friends
    // -------------------------
    vector<int> mutualFriends(int u, int v)
    {
        vector<int> res;
        if(users.find(u)==users.end() || users.find(v)==users.end()) return res;

        map<int,bool> m;
        for(int f:users[u].friends) m[f]=true;
        for(int f:users[v].friends) if(m[f]) res.push_back(f);

        return res;
    }

    // -------------------------
    // Influence score: reachable users
    // -------------------------
    int influenceScore(int id)
    {
        if(users.find(id)==users.end()) return 0;

        map<int,bool> visited;
        queue<int> q;
        visited[id]=true;
        q.push(id);

        while(!q.empty())
        {
            int u=q.front(); q.pop();
            for(int v:users[u].friends)
                if(!visited[v])
                {
                    visited[v]=true;
                    q.push(v);
                }
        }

        return visited.size()-1; // exclude self
    }

};



