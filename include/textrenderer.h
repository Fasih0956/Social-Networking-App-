#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class TextRenderer {
public:
    static void drawText(sf::RenderWindow& window, const string& text, float x, float y, int size = 14) {
        sf::Text sfText;
        sfText.setString(text);
        sfText.setCharacterSize(size);
        sfText.setFillColor(sf::Color::White);
        sfText.setPosition(x, y);
        window.draw(sfText);
    }
};
