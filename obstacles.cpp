#include "obstacles.h"
//#include <iostream> //DEBUG


void Obstacles::update(bool day, sf::Time deltaTime)
{
	for (size_t i = 0; i < 3; i++) {
		this->standingObstacles[i].move(-.5f*deltaTime.asMicroseconds() / 1000, 0.f);
		day ? this->standingObstacles[i].setTexture(texture[1][standingType[i]]) : this->standingObstacles[i].setTexture(texture[0][standingType[i]]);
		if (this->standingObstacles[i].getPosition().x < -350) {
			standingType[i] = (unsigned)rand() % 4;
			switch (standingType[i])
			{
			case SMALL:
				standingObstacles[i].setTextureRect(sf::IntRect(0, 0, 75, 117));
				this->standingObstacles[i].setPosition(sf::Vector2f(this->standingObstacles[i > 0 ? i - 1 : 2].getPosition().x + 1000.f / freq + this->standingObstacles[i > 0 ? i - 1 : 2].getTexture()->getSize().x, 250.f));
				break;
			case WIDE:
				standingObstacles[i].setTextureRect(sf::IntRect(0, 0, 300, 117));
				this->standingObstacles[i].setPosition(sf::Vector2f(this->standingObstacles[i > 0 ? i - 1 : 2].getPosition().x + 1000.f / freq + this->standingObstacles[i > 0 ? i - 1 : 2].getTexture()->getSize().x, 250.f));
				break;
			case HIGH:
				standingObstacles[i].setTextureRect(sf::IntRect(0, 0, 38, 350));
				this->standingObstacles[i].setPosition(sf::Vector2f(this->standingObstacles[i > 0 ? i - 1 : 2].getPosition().x + 1000.f / freq + this->standingObstacles[i > 0 ? i - 1 : 2].getTexture()->getSize().x, -75.f));
				break;
			case TALL:
				standingObstacles[i].setTextureRect(sf::IntRect(0, 0, 38, 350));
				this->standingObstacles[i].setPosition(sf::Vector2f(this->standingObstacles[i > 0 ? i - 1 : 2].getPosition().x + 1000.f / freq + this->standingObstacles[i > 0 ? i - 1 : 2].getTexture()->getSize().x, 150.f));
				break;
			}
			if (!i&&freq < 2.5f) this->freq += .025f;
			//std::cout << freq<<std::endl;//DEBUG
		}
	}
	//if(freq>2.f)
	for (size_t i = 0; i < 2; i++) {
		this->flyingObstacles[i].move((flyingObstacles[i].getPosition().x > 750 ? -.2f : -.75f)*deltaTime.asMicroseconds() / 1000, 0.f);
		day ? this->flyingObstacles[i].setTexture(texture[1][FLYING]) : this->flyingObstacles[i].setTexture(texture[0][FLYING]);
		if (this->flyingObstacles[i].getPosition().x < -100) {
			this->flyingObstacles[i].setPosition(sf::Vector2f(this->flyingObstacles[i > 0 ? i - 1 : 1].getPosition().x + 5000.f / freq, (float)(rand() % 200 + 30)));
			this->flyingObstacles[i].setRotation(90.f);
			//std::cout << freq<<std::endl;//DEBUG
		}
	}
}

void Obstacles::render(sf::RenderWindow &window)
{
	for (auto i : standingObstacles) window.draw(i);
	for (auto i : flyingObstacles) window.draw(i);
}


void Obstacles::restart()
{
	this->gameOver = false;
	this->freq = 1.f;
	for (size_t i = 0; i < 3; i++) {
		standingType[i] = 0;
		standingObstacles[i].setTextureRect(sf::IntRect(0, 0, 75, 117));
		standingObstacles[i].setScale(1.f, 1.f);
		this->standingObstacles[i].setTexture(texture[1][SMALL]);
		this->standingObstacles[i].setPosition(sf::Vector2f((float)1000 * (i + 1) + 500, 250.f));
		//this->standingObs[i].setPosition(sf::Vector2f((float)1000 * (i + 1)+500, (float)(rand() % 250 + 30)));
		this->standingObstacles[i].setColor(sf::Color::White);
	}
	for (size_t i = 0; i < 2; i++) {
		this->flyingObstacles[i].setTexture(texture[1][FLYING]);
		this->flyingObstacles[i].setPosition(sf::Vector2f((float)5000 * (i + 1) + 500, (float)(rand() % 200 + 30)));
		this->flyingObstacles[i].setColor(sf::Color::White);
		this->flyingObstacles[i].setRotation(90.f);
	}
}

bool Obstacles::getCollideCheck()
{
	return this->collide;
}

void Obstacles::resetCollideCheck()
{
	this->collide = false;
}



void Obstacles::updateGameOver(sf::Sprite player)
{
	// Check if enough time has passed since the last update
	if (healthUpdateCooldown.getElapsedTime().asSeconds() < 1.0f) {
		return; // Ignore update if cooldown hasn't expired
	}

	player.setScale(.5f, .5f);
	player.move(player.getTexture()->getSize().x * player.getScale().x / 4, player.getTexture()->getSize().y * player.getScale().y / 4);

	bool collisionDetected = false;
	for (size_t i = 0; i < 3; i++){
		if (player.getGlobalBounds().intersects(standingObstacles[i].getGlobalBounds()) && !collisionDetected) {

			this->collide = true;
			// Set the collisionDetected flag to true to break out of the loop
			collisionDetected = true;
			// Restart the cooldown timer
			healthUpdateCooldown.restart();
		}
	}

	for (size_t i = 0; i < 2; i++) {
		if (player.getGlobalBounds().intersects(flyingObstacles[i].getGlobalBounds()) && !collisionDetected) {

			this->collide = true;

			// Set the collisionDetected flag to true to break out of the loop
			collisionDetected = true;

			// Restart the cooldown timer
			healthUpdateCooldown.restart();
		}
	}
}

Obstacles::Obstacles()
{
	this->gameOver = true;
	this->collide = false;

	if (!this->texture[1][SMALL].loadFromFile("Assets/sthdaysq.png")) abort();
	if (!this->texture[0][SMALL].loadFromFile("Assets/sthnightsq.png")) abort();
	if (!this->texture[1][FLYING].loadFromFile("Assets/sthday.png")) abort();
	if (!this->texture[0][FLYING].loadFromFile("Assets/sthnight.png")) abort();
	if (!this->texture[1][WIDE].loadFromFile("Assets/wat2.png")) abort();
	if (!this->texture[0][WIDE].loadFromFile("Assets/wat2night.png")) abort();
	if (!this->texture[1][HIGH].loadFromFile("Assets/hi.png")) abort();
	if (!this->texture[0][HIGH].loadFromFile("Assets/hinight.png")) abort();
	if (!this->texture[1][TALL].loadFromFile("Assets/tall.png")) abort();
	if (!this->texture[0][TALL].loadFromFile("Assets/tallnight.png")) abort();

	for (size_t i = 0; i < 3; i++) standingType[i] = 0;
	this->freq = 1.f;
	for (size_t i = 0; i < 3; i++) {
		this->standingObstacles[i].setTexture(texture[1][SMALL]);
		//this->standingObs[i].setPosition(sf::Vector2f((float)1000.f*(i+1)+500.f, (float)(rand() % 250 + 30)));
		this->standingObstacles[i].setPosition(sf::Vector2f((float)1000.f*(i + 1) + 500.f, 250.f));
		this->standingObstacles[i].setColor(sf::Color::White);
	}
	for (size_t i = 0; i < 2; i++) {
		this->flyingObstacles[i].setTexture(texture[1][FLYING]);
		this->flyingObstacles[i].setPosition(sf::Vector2f((float)5000.f*(i + 1) + 500.f, (float)(rand() % 200 + 30)));
		this->flyingObstacles[i].setColor(sf::Color::White);
		this->flyingObstacles[i].setRotation(90.f);
	}
}


Obstacles::~Obstacles()
{
}