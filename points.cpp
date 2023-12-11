#include"points.h"
#include<iostream>


void Points::update(bool day, sf::Time deltaTime)
{

	for (size_t i = 0; i < 3; i++) {

		this->sprite[i].move(-.5f*deltaTime.asMicroseconds() / 1000, 0.f);
		this->sprite[i].setTexture(texture);
		if (this->sprite[i].getPosition().x < -350) {
			this->sprite[i].setPosition(sf::Vector2f(this->sprite[i > 0 ? i - 1 : 2].getPosition().x + 1000.f / freq + this->sprite[i > 0 ? i - 1 : 2].getTexture()->getSize().x, 280.f));
		}
	}

	
}

void Points::render(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
		window.draw(sprite[i]);
}
bool Points::getIncreaseScore() {

	return this->increaseScore;
}

void Points::setIncreaseScore(bool increaseScore)
{
	this->increaseScore = increaseScore;
}

bool Points::getPoints()
{
	return this->pointEarned;
}



void Points::resetPoints()
{
	this->pointEarned = false;
}

void Points::restart()
{
	this->increaseScore = false;
	this->freq = 2.f;
	for (size_t i = 0; i < 3; i++) {
		sprite[i].setScale(.5f, .5f);
		sprite[i].setTexture(texture);
		sprite[i].setPosition(sf::Vector2f((float)500 * (2 + 1) + 500, 280.f));
		sprite[i].setColor(sf::Color::White);

	}
	
}

void Points::updateIncreaseScore(sf::Sprite player)
{
	// Check if enough time has passed since the last update
	if (scoreUpdateCooldown.getElapsedTime().asSeconds() < 1.0f) {
		return; // Ignore update if cooldown hasn't expired
	}

	player.setScale(.5f, .5f);
	player.move(player.getTexture()->getSize().x * player.getScale().x / 4, player.getTexture()->getSize().y * player.getScale().y / 4);

	// Use a boolean variable to track whether a collision has occurred
	bool collisionDetected = false;

	for (int i = 0; i < 3; i++) {
		if (player.getGlobalBounds().intersects(sprite[i].getGlobalBounds()) && !collisionDetected) {
			this->pointEarned = true;
			sf::Texture transparent;
			transparent.loadFromFile("Assets/transparent.png");
			this->sprite[i].setTexture(transparent);

			// Set the collisionDetected flag to true to break out of the loop
			collisionDetected = true;

			// Restart the cooldown timer
			scoreUpdateCooldown.restart();
		}
	}
}

Points::Points()
{
	this->pointEarned = 0;
	this->increaseScore = false;

	if (!this->texture.loadFromFile("Assets/point.png")) 
		abort();
	this->freq =2.f;
	for (size_t i = 0; i < 3; i++) {
		this->sprite[i].setTexture(texture);
		this->sprite[i].setPosition(sf::Vector2f((float)500.f*(2 + 1) + 500.f, 280.f));
		this->sprite[i].setColor(sf::Color::White);
	}


		
}



Points::~Points() {


}