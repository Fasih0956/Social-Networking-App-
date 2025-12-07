#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>
#include<vector>

std::vector<sf::Sprite> sprites;
std::vector<sf::Texture> textures;

void loadTextures()
{
    textures.push_back(sf::Texture("assets/search.png"));
    textures.push_back(sf::Texture("assets/search_hover.png"));
    textures.push_back(sf::Texture("assets/book.png"));
    textures.push_back(sf::Texture("assets/book_hover.png"));
    textures.push_back(sf::Texture("assets/network.png"));
    textures.push_back(sf::Texture("assets/network_hover.png"));
    textures.push_back(sf::Texture("assets/restart_button.png"));
    textures.push_back(sf::Texture("assets/restart_button_hover.png"));
    textures.push_back(sf::Texture("include/graph.png"));
    for(auto& element:textures)sprites.push_back(sf::Sprite(element)); 
}

void scaleSprites()
{
    sprites[0].scale({0.3,0.3});
    sprites[1].scale({0.3,0.3});
    sprites[2].scale({0.3,0.3});
    sprites[3].scale({0.3,0.3});
    sprites[4].scale({0.3,0.3});
    sprites[5].scale({0.3,0.3});
    sprites[6].scale({10,10});
    sprites[7].scale({10,10});
    sprites[8].scale({1,1});
}

class Button
{
    sf::Vector2f position;
    sf::RenderWindow& window;
    bool hovered=false;
    sf::Sprite* button;
    sf::Sprite* button_hover;
    public:
    Button(sf::RenderWindow&window,sf::Vector2f position,int button_index,int button_hover_index):
    position{position},window{window}
    {
        button=new sf::Sprite(sprites[button_index]);
        button->setPosition(position);
        button_hover=new sf::Sprite(sprites[button_hover_index]);
        button_hover->setPosition(position);
    }
    
    bool poll()
    {
        auto buttonBounds=button->getGlobalBounds();
        auto mouse=sf::Mouse::getPosition(window);
        if(buttonBounds.contains({(float)mouse.x,(float)mouse.y}))hovered=true;
        else hovered=false;
      if(hovered&&sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))return true;
      return false;
    }

    void draw()
    {
        if(hovered)window.draw(*button);
        else window.draw(*button_hover);
    }

    ~Button()
    {
        delete button;
        delete button_hover;
    }
};


class SearchButton:public Button
{
  public:
  SearchButton(sf::RenderWindow&window,sf::Vector2f position):Button(window,position,0,1){}
};

class BookButton:public Button 
{
    public:
    BookButton(sf::RenderWindow&window,sf::Vector2f position):Button(window,position,2,3){}
};

class NetworkButton:public Button
{
    public:
    NetworkButton(sf::RenderWindow&window,sf::Vector2f position):Button(window,position,4,5){}
};

class RestartButton:public Button
{
    public:
    RestartButton(sf::RenderWindow&window,sf::Vector2f position):Button(window,position,6,7){}
};