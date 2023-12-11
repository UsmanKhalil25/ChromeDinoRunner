#pragma once
#include <SFML/Graphics.hpp>

enum DinoTexture { START, RUN0, RUN2, RUN3, DUCK0, DUCK2, END };

class Player
{

	const float groundHeight, gravity, jumpForce;
	sf::Vector2f velocity;
	bool isGrounded, duck;

	sf::Clock clock;

	sf::Texture dinoTexture[8];
	sf::Texture nightTexture[8];
	DinoTexture currentTexture;

	sf::Sprite dinoSprite;
public:
	void update(bool day, sf::Event &event, sf::Time deltaTime);
	void render(sf::RenderWindow &window);
	void restart();
	void die(bool day);


	sf::Sprite getDinoSprite();
	Player();
	~Player();
};
