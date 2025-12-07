#include <iostream>
#include "SocialNetwork.h"
#include "Graphviz.h"
#include "includes.h"
using namespace std;

int main()
{
    SocialNetwork sn;
    sn.loadData();

    cout<<"==== Social Media Analytics Engine ====\n";
    cout<<"Data loaded successfully!\n\n";

    int choice;
    while(true)
    {
        cout<<"\n=== MENU ===\n";
        cout<<"1: Show User Info (Degree, Clustering, Influence)\n";
        cout<<"2: Find Shortest Path Between Two Users\n";
        cout<<"3: Find Mutual Connections\n";
        cout<<"4: Generate Graph (2 traversals from user)\n";
        cout<<"5: Generate Shortest Path Graph\n";
        cout<<"6: Generate Mutual Connections Graph\n";
        cout<<"0: Exit\n";
        cout<<"Choice: ";
        cin>>choice;

        if(choice==0) break;

        int uid, uid1, uid2;
        vector<int> path;
        
        switch(choice)
        {
            case 1:
                cout<<"UserID: "; cin>>uid;
                sn.printUserInfo(uid);
                break;
                
            case 2:
                cout<<"User1 ID: "; cin>>uid1;
                cout<<"User2 ID: "; cin>>uid2;
                path = sn.g.shortestPath(uid1, uid2);
                if(path.empty()) {
                    cout<<"No path found between users "<<uid1<<" and "<<uid2<<endl;
                } else {
                    cout<<"Shortest Path: ";
                    for(size_t i=0; i<path.size(); i++) {
                        if(i>0) cout<<" -> ";
                        cout<<path[i];
                    }
                    cout<<endl;
                    cout<<"Path length: "<<path.size()-1<<" connections"<<endl;
                }
                break;
                
            case 3:
                cout<<"User1 ID: "; cin>>uid1;
                cout<<"User2 ID: "; cin>>uid2;
                path = sn.g.mutualFriends(uid1, uid2);
                if(path.empty()) {
                    cout<<"No mutual connections found"<<endl;
                } else {
                    cout<<"Mutual Connections ("<<path.size()<<"): ";
                    for(int x:path) cout<<x<<" ";
                    cout<<endl;
                }
                break;
                
            case 4:
                cout<<"UserID (for 2-traversal graph): "; cin>>uid;
                Graphviz::createGraph(sn.g, uid, "graph.dot");
                if(Graphviz::createImage("graph.dot", "graph.png")) {
                    cout<<"Graph generated successfully! Check graph.png"<<endl;
                } else {
                    cout<<"Error generating graph. Make sure Graphviz is installed."<<endl;
                }
                break;
                
            case 5:
                cout<<"User1 ID: "; cin>>uid1;
                cout<<"User2 ID: "; cin>>uid2;
                Graphviz::createShortestPath(sn.g, uid1, uid2, "path.dot");
                if(Graphviz::createImage("path.dot", "path.png")) {
                    cout<<"Path graph generated successfully! Check path.png"<<endl;
                } else {
                    cout<<"Error generating graph. Make sure Graphviz is installed."<<endl;
                }
                break;
                
            case 6:
                cout<<"User1 ID: "; cin>>uid1;
                cout<<"User2 ID: "; cin>>uid2;
                Graphviz::mutualConnectionGraph(sn.g, uid1, uid2, "mutual.dot");
                if(Graphviz::createImage("mutual.dot", "mutual.png")) {
                    cout<<"Mutual connections graph generated! Check mutual.png"<<endl;
                } else {
                    cout<<"Error generating graph. Make sure Graphviz is installed."<<endl;
                }
                break;
                
            default: 
                cout<<"Invalid choice\n";
        }
    }

    cout<<"\nThank you for using Social Media Analytics Engine!\n";
    return 0;
}
