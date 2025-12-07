#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.h"
using namespace std;

int StartScreen()
{
    const int height=1000;
    const int width=1000;
    sf::RenderWindow window(sf::VideoMode({width,height}), "Social Networking Simulator");
    SearchButton b1(window,{width*.4,height*.2});
    BookButton b2(window,{width*.4,height*.4});
    NetworkButton b3(window,{width*.4,height*.6});
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())window.close();
            int ret=0;
            if(b1.poll())ret=1;
            else if(b2.poll())ret=2;
            else if(b3.poll())ret=3;
            if(ret)return ret;
        }

        window.clear(sf::Color(128,128,128));
        b1.draw();
        b2.draw();
        b3.draw();
        window.display();
    }
    return 0;
}

int main()
{
    loadTextures();
    scaleSprites();
    while(true)
    {
    int option=StartScreen();
    if(!option)return 0;
    cout<<"The option is "<<option<<endl;
    }
    return 0;
}

