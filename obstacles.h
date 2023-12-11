#pragma once
#include "SFML/Graphics.hpp"

enum OBSTACLETYPE { SMALL, WIDE, TALL, HIGH, FLYING };

class Obstacles
{
	bool gameOver;
	bool collide;
	float freq;
	sf::Texture texture[2][5];
	sf::Sprite flyingObstacles[2];
	sf::Sprite standingObstacles[3];
	unsigned standingType[3];
	sf::Clock healthUpdateCooldown;
public:
	void update(bool day, sf::Time deltatime);
	void render(sf::RenderWindow &window);
	void restart();
	bool getCollideCheck();
	void resetCollideCheck();
	void updateGameOver(sf::Sprite player);
	Obstacles();
	~Obstacles();
};
