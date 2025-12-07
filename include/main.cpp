#include <iostream>
#include "SocialNetwork.h"
using namespace std;

int main()
{
    SocialNetwork sn;
    sn.loadData();

    cout<<"==== Social Network Loaded ====\n";

    int choice;
    while(true)
    {
        cout<<"\n1: Show User Info\n2: Shortest Path\n3: Mutual Friends\n0: Exit\nChoice: ";
        cin>>choice;

        if(choice==0) break;

        int uid,fid,pidx;
        string content;
        vector<int> path;
        switch(choice)
        {
            case 1:
                cout<<"UserID: "; cin>>uid;
                sn.printUserInfo(uid);
                break;
            case 2:
                cout<<"User1 ID: "; cin>>uid;
                cout<<"User2 ID: "; cin>>fid;
                path = sn.g.shortestPath(uid,fid);
                if(path.empty()) cout<<"No path found\n";
                else {cout<<"Path: "; for(int x:path) cout<<x<<" "; cout<<endl;}
                break;
            case 3:
                cout<<"User1 ID: "; cin>>uid;
                cout<<"User2 ID: "; cin>>fid;
                path = sn.g.mutualFriends(uid,fid);
                cout<<"Mutual Friends: "; for(int x:path) cout<<x<<" "; cout<<endl;
                break;
            default: cout<<"Invalid choice\n";
        }
    }

    return 0;
}

