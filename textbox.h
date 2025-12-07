#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>
sf::Font dodot("assets/dodot.ttf");
class TextBox
{
  sf::RenderWindow& window;
  sf::Vector2f pos;
  sf::Text display;
  std::string buffer;
  std::string placeholder;
  int val;
  int clock=0;
  public:
  TextBox(sf::RenderWindow& window,sf::Vector2f pos,std::string placeholder,int val=-1):window(window),pos{pos},
  display(dodot),placeholder(placeholder),val{val}
  {
    display.setPosition(pos);
    display.setFillColor(sf::Color(255,255,255));
    window.setKeyRepeatEnabled(false);
    if(val!=-1)buffer=std::to_string(val);
  }

  int poll()
  {
    clock++;
    auto mousePos=sf::Mouse::getPosition(window);
    auto bounds=display.getGlobalBounds();
    if(!bounds.contains({(float)mousePos.x,(float)mousePos.y}))
    {
        display.setFillColor(sf::Color(100,100,100));
        display.setString(placeholder+buffer);
        return val;
    }
    display.setFillColor(sf::Color(255,255,255));  
    if(clock%2==0)
    {
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))buffer+='0';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))buffer+='1';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))buffer+='2';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))buffer+='3';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))buffer+='4';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5))buffer+='5';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6))buffer+='6';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7))buffer+='7';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8))buffer+='8';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9))buffer+='9';
       else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace))
       {
           if(!buffer.empty())buffer.pop_back();
       }
    }
    if(buffer.size()>3)buffer.pop_back();
    if(buffer.size())val=std::stoi(buffer.c_str());
    if(val<=0||val>100)val=-1;
    std::cout<<val<<std::endl;
    display.setString(placeholder+buffer);
    return val;
  }

  void draw()
  {
    window.draw(display);
  }
};