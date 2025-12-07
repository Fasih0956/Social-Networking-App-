#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class TextBox {
public:
    sf::RectangleShape box;
    sf::Text label;
    sf::Text content;
    string currentInput = "";
    bool focused = false;

    TextBox(sf::RenderWindow& window, sf::Vector2f pos, const string& labelText)
        : box({300, 30})
    {
        box.setPosition(pos);
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::Black);

        label.setString(labelText);
        label.setCharacterSize(14);
        label.setFillColor(sf::Color::Black);
        label.setPosition(pos.x - 150, pos.y + 5);

        content.setString("");
        content.setCharacterSize(14);
        content.setFillColor(sf::Color::Black);
        content.setPosition(pos.x + 5, pos.y + 5);
    }

    int poll() {
        if (currentInput.empty()) return -1;
        try {
            return stoi(currentInput);
        } catch (...) {
            return -1;
        }
    }

    void handleInput(sf::Event& event) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                if (event.text.unicode == '\b' && !currentInput.empty()) {
                    currentInput.pop_back();
                } else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    currentInput += static_cast<char>(event.text.unicode);
                }
                content.setString(currentInput);
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(label);
        window.draw(content);
    }
};
