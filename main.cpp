#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "doodle.hpp"
#include "platform.hpp"
#include "Level.hpp"
#include "filing.hpp"
#include <fstream>

int operator +(Doodle& d1, Doodle& d2) {
    int score;
    score = d1.getscore() + d2.getscore();
    return score;
}
int operator +(int a, Doodle& d3) {
    int score;
    score = a + d3.getscore();
    return score;
}

int main()
{
    int tries = 0;
    intro:
    // create the intro window
    sf::RenderWindow introWindow(sf::VideoMode(1300, 700), "Intro"); // VideoMode(Width, Height)

    // create cursor texture
    sf::Texture handTexture;

    // load cursor texture
    handTexture.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/cursor.png");

    // create cursor sprite
    sf::Cursor handCursor;
    handCursor.loadFromPixels(handTexture.copyToImage().getPixelsPtr(), handTexture.getSize(), { 0, 0 });

    // set cursor to loaded texture
    introWindow.setMouseCursor(handCursor);

    // create play button texture
    sf::Texture textureplay;

    // load play button texture
    textureplay.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/start2.png");

    // create play button sprite
    sf::Sprite start(textureplay);

    // set play button position
    start.setPosition(600, 500);

    // create intro background texture
    sf::Texture textureintro;

    // load intro texture
    textureintro.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/retro.png");

    // create intro background sprite
    sf::Sprite intro(textureintro);

    // set intro background position
    intro.setPosition(0, 0);

    // create font and text for play button (hidden behind play button)
    sf::Font font;
    font.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/font.ttf");
    sf::Text playbutton("Playyy", font, 150);
    playbutton.setFillColor(sf::Color::White);
    playbutton.setPosition(400, 400);

    // create a clock to track elapsed time
    sf::Clock clock;

    // create click music 
    sf::Music click;

    // load click music
    click.openFromFile("C:/Users/Amna Shah/Desktop/Resources/click.wav");

    int count = 0;
    int s = 0;
    int high;
    std::string score = "";
    std::string highscore = "";
    int file = 0;
    // start the intro loop
    while (introWindow.isOpen())
    {
        // process events

        // create event sprite
        sf::Event event;


        while (introWindow.pollEvent(event)) //check for events
        {
            // close window if event closed
            if (event.type == sf::Event::Closed)
            {
                introWindow.close();
            }


            // check if play button is clicked
            if (event.type == sf::Event::MouseButtonPressed) // check if mouse is clicked
            {
                // getting position where mouse clicked
                sf::Vector2i mousePosition = sf::Mouse::getPosition(introWindow); //Vector2i stores the 2D coordinates

                // checking if mouse click coordinates lie in the perimeters of the play button
                if (playbutton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    click.play(); //play button sound
                    tries++;
                    introWindow.close(); // intro window closed
                }
            }
        }

        // Draw intro components
        //introWindow.draw(playbutton);
        introWindow.draw(intro);
        //introWindow.draw(start);
        introWindow.display();
    }
    sf::Sprite e;
    Doodle doodle1;
    Doodle doodle2;
    Doodle doodle3;
        // create level window
        sf::RenderWindow level1(sf::VideoMode(1300, 700), "Level 1");
        Level1 lvl1;
        //Doodle doodle1;
        std::vector<sf::Sprite> platforms; //vector defination 
        Platform p1;
        p1.platform.setPosition(270, 450);
        Platform p2;
        p2.platform.setPosition(500, 300);
        Platform p3;
        p3.platform.setPosition(700, 400);
        Platform p4;
        p4.platform.setPosition(900, 300);
        Platform p5;
        platforms.push_back(p1.platform);
        platforms.push_back(p2.platform);
        platforms.push_back(p3.platform);
        platforms.push_back(p4.platform);
        sf::Sprite tunnel;
        sf::Texture t;
        t.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/tunnel.png");
        tunnel.setTexture(t);
        tunnel.setPosition(1100, 420);

        playbutton.setPosition(1000, 470);

        level1.setMouseCursor(handCursor);
        sf::Event event;
        bool lost = false;
        while (level1.isOpen()) {
            level1.clear();
            while (level1.pollEvent(event)) //check for events
            {
                // close window if event closed
                if (event.type == sf::Event::Closed)
                {
                    level1.close();
                }
                
                // check if play button is clicked
                if (event.type == sf::Event::MouseButtonPressed) // check if mouse is clicked
                {
                    // getting position where mouse clicked
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(level1); //Vector2i stores the 2D coordinates

                    // checking if mouse click coordinates lie in the perimeters of the play button
                    if (playbutton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        click.openFromFile("C:/Users/Amna Shah/Desktop/Resources/click.wav");
                        click.play(); //play button sound
                        lvl1.change();
                        count = 1;

                        // create backgroundMusic Music
                        click.openFromFile("C:/Users/Amna Shah/Desktop/Resources/beat.wav");

                        // loop when it finishes
                        click.setLoop(true);
                        click.play();

                    }
                }
            }
            float deltaTime = clock.restart().asSeconds();
            doodle1.moveDoodle(clock, level1, platforms, tunnel, e);
            lvl1.draw(level1);
            if (count == 1) {
                p1.draw(level1, 500, 300);
                p2.draw(level1, 270, 450);
                p3.draw(level1, 700, 400);
                p4.draw(level1, 900, 300);
                level1.draw(tunnel);
                draw(level1, doodle1);
            }
            level1.display();
        }
        
        int direct = 1;
        p3.platform.setPosition(700, 500);
        p4.platform.setPosition(900, 400);
        p5.platform.setPosition(700, 175);
        platforms.erase(platforms.begin() + 2);
        platforms.erase(platforms.begin() + 2);
        platforms.push_back(p3.platform);
        platforms.push_back(p4.platform);
        platforms.push_back(p5.platform);
        // create level window
        sf::RenderWindow level2(sf::VideoMode(1300, 700), "Level 2");
        count = 0;

        Level2 lvl2;

        sf::Sprite pl1;
        sf::Sprite pl2;
        sf::Sprite pl3;
        sf::Texture tex;
        tex.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/platform.png");
        pl1.setTexture(tex);
        pl1.setPosition(700, 400);
        pl2.setTexture(tex);
        pl2.setPosition(700, 25);
        pl3.setTexture(tex);
        pl3.setPosition(1100, 25);

        sf::Sprite enemy;
        float amplitude = 8.f;
        float period = 1.f; // in seconds
        sf::Clock clk;
        sf::Texture tx;
        tx.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/spike.png");
        enemy.setTexture(tx);
        enemy.setPosition(700, 25);

        t.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/tunnel.png");
        tunnel.setTexture(t);
        tunnel.setPosition(1100, 420);

        playbutton.setPosition(1000, 470);

        level2.setMouseCursor(handCursor);
        while (level2.isOpen() && doodle1.lose!=true) {
            
            level2.clear();
            while (level2.pollEvent(event)) //check for events
            {
                // close window if event closed
                if (event.type == sf::Event::Closed)
                {
                    level2.close();
                }

                // check if play button is clicked
                if (event.type == sf::Event::MouseButtonPressed) // check if mouse is clicked
                {
                    // getting position where mouse clicked
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(level2); //Vector2i stores the 2D coordinates

                    // checking if mouse click coordinates lie in the perimeters of the play button
                    if (playbutton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        click.openFromFile("C:/Users/Amna Shah/Desktop/Resources/click.wav");
                        click.play(); //play button sound
                        lvl2.change();
                        count = 1;

                        // create backgroundMusic Music
                        click.openFromFile("C:/Users/Amna Shah/Desktop/Resources/beat.wav");

                        // loop when it finishes
                        click.setLoop(true);
                        click.play();

                    }
                }
            }
            float time = clock.getElapsedTime().asSeconds();
            float offset = amplitude * sin(2 * 3.14159 / period * time);
            float upwardOffset = 250; // Adjust this value as needed for upward movement

            enemy.move(0.f, direct*offset);

            if (enemy.getGlobalBounds().intersects(p3.platform.getGlobalBounds())) {
                direct = -1;
            }
            else if (enemy.getGlobalBounds().intersects(pl2.getGlobalBounds())) 
            {
                direct = 1;
            }

            float deltaTime = clock.restart().asSeconds();
            if (doodle2.doodle.getGlobalBounds().intersects(enemy.getGlobalBounds()))
            {
                doodle2.lose = true;
            }
            doodle2.moveDoodle(clock, level2, platforms, tunnel, enemy);
            level2.draw(pl1);
            level2.draw(pl2);
            lvl2.draw(level2);
            if (count == 1) {
                p1.draw(level2, 500, 300);
                p2.draw(level2, 300, 450);
                p3.draw(level2, 700, 500);
                p4.draw(level2, 900, 400);
                p5.draw(level2, 700, 175);
                level2.draw(tunnel);
                // doodle2.doodle.setPosition(80, 350);
                level2.draw(enemy);
                draw(level2, doodle2);
            }
            level2.display();
        }
        level2.close();

        // create level window
        sf::RenderWindow level3(sf::VideoMode(1300, 700), "Level 3");
        count = 0;
        Level3 lvl3;
        pl1.setPosition(350, 450);
        pl2.setPosition(600, 300);
        pl3.setPosition(900, 300);
        platforms.erase(platforms.begin() + 1);
        platforms.erase(platforms.begin() + 2);
        platforms.erase(platforms.begin() + 1);
        platforms.erase(platforms.begin() + 1);
        platforms.push_back(pl1);
        platforms.push_back(pl2);
        platforms.push_back(pl3);

        t.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/tunnel.png");
        tunnel.setTexture(t);
        tunnel.setPosition(1100, 420);

        playbutton.setPosition(1000, 470);

        level3.setMouseCursor(handCursor);
        while (level3.isOpen() && doodle1.lose != true && doodle2.lose != true)
        {
            level3.clear();
            while (level3.pollEvent(event)) //check for events
            {
                // close window if event closed
                if (event.type == sf::Event::Closed)
                {
                    level3.close();
                }

                // check if play button is clicked
                if (event.type == sf::Event::MouseButtonPressed) // check if mouse is clicked
                {
                    // getting position where mouse clicked
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(level3); //Vector2i stores the 2D coordinates

                    // checking if mouse click coordinates lie in the perimeters of the play button
                    if (playbutton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        click.openFromFile("C:/Users/Amna Shah/Desktop/Resources/click.wav");
                        click.play(); //play button sound
                        int i = 100;
                        lvl3.text.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/memorize.png");
                        lvl3.lvl.setTexture(lvl3.text);
                        lvl3.draw(level3);
                        sf::RenderWindow m(sf::VideoMode(1300, 700), "Memorize");
                        sf::Texture mem;
                        mem.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/memorize.png");
                        sf::Sprite memory;
                        memory.setTexture(mem);
                        while (m.isOpen()) {
                            // create event sprite
                            sf::Event event;
                            while (m.pollEvent(event)) //check for events
                            {
                                // close window if event closed
                                if (event.type == sf::Event::Closed)
                                {
                                    m.close();
                                }
                            }
                            m.clear();
                            m.draw(memory);
                            m.display();
                            sf::sleep(sf::seconds(3));
                            m.close();
                        }

                        lvl3.change();
                        count = 1;

                        // create backgroundMusic Music
                        click.openFromFile("C:/Users/Amna Shah/Desktop/Resources/beat.wav");

                        // loop when it finishes
                        click.setLoop(true);
                        click.play();

                    }
                }
            }
            float deltaTime = clock.restart().asSeconds();
            doodle3.moveDoodle(clock, level3, platforms, tunnel, e);
            if (count == 1) {
                p1.draw(level3, 600, 300);
                p2.draw(level3, 350, 450);
                p3.draw(level3, 900, 300);
            }
            lvl3.draw(level3);
            if (count == 1) {
                level3.draw(tunnel);
                draw(level3, doodle3);
            }
            level3.display();

        }
        level3.close();

    // create game over window
    sf::Texture over;
    sf::Texture text1;
    sf::Texture text2;
    sf::RenderWindow gameover(sf::VideoMode(339, 491), "Game Over");
    sf::Font scores;
    scores.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/ARCADE_N.ttf");
    sf::Text sc;
    sf::Text hs;
    sc.setFillColor(sf::Color::White);
    sc.setFont(scores);
    sc.setPosition(197, 141);
    sc.setCharacterSize(25);
    sc.setStyle(sf::Text::Bold);
    sc.setString("0");
    hs.setFillColor(sf::Color::White);
    hs.setFont(scores);
    hs.setPosition(197, 214);
    hs.setCharacterSize(25);
    hs.setStyle(sf::Text::Bold);

    // load the gameover texture
    over.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/gameover.png");
    text1.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/yes.png");
    text2.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/no.png");

    sf::Sprite game(over);
    sf::Sprite yes(text1);
    sf::Sprite no(text2);

    // create the background sprites
    game.setPosition(0, 0);
    yes.setPosition(41, 395);
    no.setPosition(210, 391);

    gameover.setMouseCursor(handCursor);

    while (gameover.isOpen())
    {
        // process events

        // create event sprite
        sf::Event event;


        while (gameover.pollEvent(event)) //check for events
        {
            // close window if event closed
            if (event.type == sf::Event::Closed)
            {
                gameover.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) // check if mouse is clicked
            {
                // getting position where mouse clicked
                sf::Vector2i mousePosition = sf::Mouse::getPosition(gameover); //Vector2i stores the 2D coordinates

                // checking if mouse click coordinates lie in the perimeters of the play button
                if (yes.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    click.play(); //play button sound
                    goto intro;
                }else if (no.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    click.play(); //play button sound
                    
                    gameover.close();
                }
                
            } 
            
        }
        s = doodle1 + doodle2;
        s = s + doodle3;
        s = (s / (tries)) * 100;
        score = std::to_string(s);
        sc.setString(score);
        high = filing(s);
        highscore = std::to_string(high);
        hs.setString(highscore);

        // Draw components
        gameover.draw(game);
        gameover.draw(yes);
        gameover.draw(no);
        gameover.draw(sc);
        gameover.draw(hs);
        gameover.display();

    }

    return 0;
}
