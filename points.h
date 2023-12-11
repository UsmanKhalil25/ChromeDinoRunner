#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/System/Clock.hpp>


class Points
{
	bool increaseScore;
	float freq;
	sf::Texture texture;
	sf::Sprite sprite[3];
	bool pointEarned;
	sf::Clock scoreUpdateCooldown;
public:
	void update(bool day, sf::Time deltatime);
	void render(sf::RenderWindow &window);
	bool getIncreaseScore();
	void setIncreaseScore(bool increaseScore);
	bool getPoints();
	void resetPoints();
	void restart();
	void updateIncreaseScore(sf::Sprite player);
	Points();
	~Points();
};
