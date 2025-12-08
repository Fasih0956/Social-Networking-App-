#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"
#include "textbox.h"
#include "include/includes.h"
#include "include/SocialNetwork.h"

int user1id=-1;
int user2id=-1;
const int height=1000;
const int width=1000;

using namespace std;

int StartScreen(sf::RenderWindow& window)
{
    string title="Social Networking Simulator";
    sf::Text header(dodot,title,50);
    header.setPosition({width*0.1,0});
    if(!window.isOpen())window.create(sf::VideoMode({width,height}), "Social Networking Simulator");
    SearchButton b1(window,{width*.4,height*.2});
    BookButton b2(window,{width*.4,height*.4});
    NetworkButton b3(window,{width*.4,height*.6});
    TextBox b4(window,{width*.4,height*.8},"User 1 ID:",user1id);
    TextBox b5(window,{width*.4,height*.85},"User 2 ID:",user2id);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())window.close();
            int ret=0;
            if(b1.poll())ret=1;
            if(b2.poll())ret=2;
            if(b3.poll())ret=3;
            user1id=b4.poll();
            user2id=b5.poll();
            if(ret&&user1id!=-1&&user2id!=-1)
            {
                //window.close();
                return ret;
            }
            //sf::sleep(sf::milliseconds(30));
        }

        window.clear(sf::Color(128,128,128));
        b1.draw();
        b2.draw();
        b3.draw();
        b4.draw();
        b5.draw();
        window.draw(header);
        window.display();
    }
    return 0;
}

bool shortestPath(sf::RenderWindow& window)
{
    if(!window.isOpen())window.create(sf::VideoMode({width,height}), "Social Networking Simulator");
    string title="Shortest Path From User "+to_string(user1id)+" to User "+to_string(user2id);
    sf::Text header(dodot,title,20);
    header.setPosition({width*0.2,0});
    header.setFillColor(sf::Color(0,0,0));
    RestartButton b1(window,{0,0});
    sf::Sprite graph(textures[8]);
    graph.setPosition({width*.4,height*.3});
    graph.setScale({0.4,0.4});
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())window.close();
            if(b1.poll())return 1;
            //sf::sleep(sf::milliseconds(30));
        }

        window.clear(sf::Color(255,255,255));
        b1.draw();
        window.draw(header);
        window.draw(graph);
        window.display();
    }
    return 0;
}

bool userInfo(sf::RenderWindow& window,string stats)
{
    string title="Details and 2 traversal connections for User "+to_string(user1id);
    sf::Text header(dodot,title,20);
    header.setPosition({width*0.2,0});
    header.setFillColor(sf::Color(0,0,0));
    sf::Text userInfo(dodot,stats);
    userInfo.scale({0.5,1.5});
    userInfo.setPosition({width*0.5,height*0.9});
    userInfo.setFillColor(sf::Color(134,12,49));
    sf::Sprite graph(textures[8]);
    graph.setPosition({width*.2,height*.2});
    graph.setScale({0.5,0.5});
    if(!window.isOpen())window.create(sf::VideoMode({width,height}), "Social Networking Simulator");
    RestartButton b1(window,{0,0});
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())window.close();
            if(b1.poll())return 1;
            //sf::sleep(sf::milliseconds(30));
        }

        window.clear(sf::Color(255,255,255));
        b1.draw();
        window.draw(userInfo);
        window.draw(graph);
        window.draw(header);
        window.display();
    }
    return 0;
}

bool mutualFriends(sf::RenderWindow& window)
{
    if(!window.isOpen())window.create(sf::VideoMode({width,height}), "Social Networking Simulator");
    string title="Mutual Connection graph between User "+to_string(user1id)+" and User "+to_string(user2id);
    sf::Text header(dodot,title,20);
    header.setPosition({width*0.2,0});
    header.setFillColor(sf::Color(0,0,0));
    RestartButton b1(window,{0,0});
    sf::Sprite graph(textures[8]);
    graph.setPosition({0,height*.3});
    //graph.setScale({0.5,2});
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())window.close();
            if(b1.poll())return 1;
            //sf::sleep(sf::milliseconds(30));
        }

        window.clear(sf::Color(255,255,255));
        b1.draw();
        window.draw(header);
        window.draw(graph);
        window.display();
    }
    return 0;
}

int main()
{
    const int height=1000;
    const int width=1000;
    sf::RenderWindow window(sf::VideoMode({width,height}), "Social Network Simulator");
    window.setVerticalSyncEnabled(true);
    loadTextures();
    scaleSprites();
    SocialNetwork sn;
    sn.loadData();
    while(true)
    {
    int option=StartScreen(window);
    if(!option)return 0;
    if(option==1)
    {
        createShortestPath(sn.g,user1id,user2id);
        bool success=textures[8].loadFromFile("assets/graph.png");
        textures[8].setSmooth(true);
        if(!success)cout<<"texture not loaded\n";
        if(!shortestPath(window))return 0;
    }
    if(option==2)
    {
        createGraph(sn.g,user1id);
        string stats=generateStatistics(sn.g,user1id);
        bool success=textures[8].loadFromFile("assets/graph.png");
        textures[8].setSmooth(true);
        if(!success)cout<<"texture not loaded\n";
        if(!userInfo(window,stats))return 0;
    }
    if(option==3)
    {
        mutualConnectionGraph(sn.g,user1id,user2id);
        bool success=textures[8].loadFromFile("assets/graph.png");
        textures[8].setSmooth(true);
        if(!success)cout<<"texture not loaded\n";
        if(!mutualFriends(window))return 0;
    }
    }
    return 0;
}

