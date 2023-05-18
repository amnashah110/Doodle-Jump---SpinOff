#include<iostream>
#include<SFML/Graphics.hpp>

class Platform
{
private:
    sf::Texture texture;
public:
    Platform()
    {
        texture.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/platform.png");
        platform.setTexture(texture);
    }

    // function for drawing platform;
    virtual void draw(sf::RenderWindow& window, int x, int y)
    {
        platform.setPosition(x, y);
        window.draw(platform);
    }
    sf::Sprite platform;
};
