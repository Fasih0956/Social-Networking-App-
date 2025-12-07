#include <string>
#include <vector>
#include <map>
using namespace std;

struct Post {
    int id;
    string content;
    int likes = 0;
    vector<pair<int,string>> comments; // pair<userID, comment>
};

class User
{
public:
    int id;
    string name;
    string city;

    vector<int> friends;        // adjacency list
    vector<int> followers;
    vector<int> following;

    vector<Post> posts;

    User() {}
    User(int uid, const string &uname, const string &ucity="") : id(uid), name(uname), city(ucity) {}

    void addFriend(int uid) { friends.push_back(uid); }
    void addFollower(int uid) { followers.push_back(uid); }
    void addFollowing(int uid) { following.push_back(uid); }

    void addPost(const string &content, int postID)
    {
        posts.push_back({postID, content, 0, {}});
    }

    void addLike(int postIndex) { if(postIndex >=0 && postIndex < posts.size()) posts[postIndex].likes++; }
    void addComment(int postIndex, int userID, const string &comment)
    {
        if(postIndex >=0 && postIndex < posts.size())
            posts[postIndex].comments.push_back({userID, comment});
    }
};
