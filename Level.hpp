#include<iostream>
#include<SFML/Graphics.hpp>

class Level { // virtual
public:
	sf::Texture text;
	sf::Sprite lvl;
	Level() {

	}
	Level(std::string fp) {
		// load the background texture
		text.loadFromFile(fp);

		// create the background sprites
		lvl.setTexture(text);
	}
	Level(const Level& other) : text(other.text), lvl(other.lvl) {}
	virtual void draw(sf::RenderWindow& window) = 0; // pure virtual func
};
class Level1: virtual public Level { 
	std::string filepath;
public:
	Level1():Level("C:/Users/Amna Shah/Desktop/Resources/lvl1.png"){
	}
	// function for drawing level;
	void draw(sf::RenderWindow& window) override
	{
		window.draw(lvl);
	}
	void change() {
		text.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/draw.png");
		lvl.setTexture(text);
	}
};

class Level2 : virtual public Level {
	std::string filepath;
public:
	Level2():Level("C:/Users/Amna Shah/Desktop/Resources/lvl2.png"){
	}
	// function for drawing level;
	void draw(sf::RenderWindow& window) override
	{
		window.draw(lvl);
	}
	void change() {
		text.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/draw.png");
		lvl.setTexture(text);
	}
};

class Level3 : virtual public Level {
	std::string filepath;
public:
	Level3() :Level("C:/Users/Amna Shah/Desktop/Resources/lvl3.png") {
	}
	// function for drawing level;
	void draw(sf::RenderWindow& window) override
	{
		window.draw(lvl);
	}
	void change() {
		text.loadFromFile("C:/Users/Amna Shah/Desktop/Resources/draw.png");
		lvl.setTexture(text);
	}
};
