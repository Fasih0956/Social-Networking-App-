#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font* font;
    bool clicked = false;

    Button(sf::RenderWindow& window, const string& label, sf::Vector2f pos, sf::Vector2f size = {150, 50})
        : shape(size)
    {
        shape.setPosition(pos);
        shape.setFillColor(sf::Color::Blue);
        
        text.setString(label);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);
        text.setPosition(pos.x + 10, pos.y + 10);
    }

    bool isClicked(sf::RenderWindow& window) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto mousePos = sf::Mouse::getPosition(window);
            if (shape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                return true;
            }
        }
        return false;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
};

class SearchButton : public Button {
public:
    SearchButton(sf::RenderWindow& window, sf::Vector2f pos) 
        : Button(window, "Find Shortest Path", pos) {}

    int poll() {
        return isClicked ? 1 : 0;
    }
};

class BookButton : public Button {
public:
    BookButton(sf::RenderWindow& window, sf::Vector2f pos)
        : Button(window, "User Info", pos) {}

    int poll() {
        return isClicked ? 2 : 0;
    }
};

class NetworkButton : public Button {
public:
    NetworkButton(sf::RenderWindow& window, sf::Vector2f pos)
        : Button(window, "Network View", pos) {}

    int poll() {
        return isClicked ? 3 : 0;
    }
};

class RestartButton : public Button {
public:
    RestartButton(sf::RenderWindow& window, sf::Vector2f pos)
        : Button(window, "Back", pos, {100, 40}) {}

    int poll() {
        return isClicked ? 1 : 0;
    }
};
