#include<iostream>
#include<SFML/Graphics.hpp>
#include<string.h>
#include<memory>

class Doodle {
   
    int lvl = 1;
    //texture object created
    sf::Texture texture;
    int count = 0;
    int score = 0;


public:
    //int tries=0;
    bool lose;
    int x = 80;
    int y = 350; 
    //int h = 100;
    float dx = 0, dy = 0;
    float gravity = 0.1;
    float max_velocity = 3;

    Doodle()
    {
        lose = false;
        // load the doodle texture
        texture.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/lucario.png");

        // create doodle sprite
        doodle.setTexture(texture);
        doodle.setPosition(80, 320);
    }

    // function for drawing backgrounds;
    friend void draw(sf::RenderWindow& window, const Doodle&doodle);

    int getscore() {
        return score;
    }

    ~Doodle() {

    }

    // function for moving doodle
    void moveDoodle(sf::Clock& clock, sf::RenderWindow& window, std::vector<sf::Sprite>& p, sf::Sprite tunnel, sf::Sprite e)
    {
        // define the boundaries of the game window
        float leftBound = 0;
        float topBound = 0;
        float rightBound = window.getSize().x - doodle.getGlobalBounds().width;
        float bottomBound = window.getSize().y - doodle.getGlobalBounds().height;
        float deltaTime = clock.restart().asSeconds();


        // move the doodle left or right depending on keyboard input
        float speed = 100.0f * 170.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && doodle.getPosition().x > leftBound)
        {
            doodle.move(-speed * deltaTime * 4, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && doodle.getPosition().x < rightBound)
        {
            doodle.move(speed * deltaTime * 4, 0.0f);
            
        }
        

        // make the doodle jump
        static bool isJumping = false;
        static bool canJump = true;
        float y_jump = y;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canJump && !isJumping && doodle.getPosition().y > topBound)
        {
            count = 1;
            // Start the jump
            isJumping = true;
            dy = -7; // Set the initial upward velocity

            // Set y_jump to the current y position
            y_jump = y;

            // Cannot jump again until landing
            canJump = false;
        }
        

        if (isJumping) {
            // Update y position based on velocity
            y += dy;
            dy += gravity;

            // Apply max velocity limit
            if (dy > max_velocity) {
                dy = max_velocity;
            }

            bool isColliding = false;
            for (int i = 0; i < p.size(); i++) {
                if (doodle.getGlobalBounds().intersects(p[i].getGlobalBounds())) {
                    // Place doodle on top of the platform
                    y = p[i].getPosition().y - doodle.getGlobalBounds().height;
                    dy = 0;
                    isJumping = false;
                    canJump = true;
                    isColliding = true;
                    break;
                }
            }
            
            if (doodle.getGlobalBounds().intersects(e.getGlobalBounds())){
                score = score - 15;
                isJumping = false;
                canJump = true;
                isColliding = true;
                lose = true;
                window.close();
            }
            
            if (doodle.getGlobalBounds().intersects(tunnel.getGlobalBounds())) {
                score = score + 30;
                isJumping = false;
                canJump = true;
                isColliding = true;
                window.close();
 
            }
            if (doodle.getPosition().y > 700) {
                score = score - 15;
                isJumping = false;
                canJump = true;
                isColliding = true;
                lose = true;
                window.close();
            }

            doodle.setPosition(doodle.getPosition().x + dx, y + dy);
        }
    }


    //sprite object created
    sf::Sprite doodle;

};
void draw(sf::RenderWindow& window, const Doodle& doodle) {
    window.draw(doodle.doodle);
}
