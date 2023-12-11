#include "player.h"

void Player::update(bool day, sf::Event &event, sf::Time deltaTime)
{
	int texTime = clock.getElapsedTime().asMilliseconds() % 200;

	if (dinoSprite.getPosition().y < groundHeight) currentTexture = RUN3; else
		if (texTime >= 100) currentTexture = RUN0; else
			currentTexture = RUN2;

	if (this->dinoSprite.getPosition().y > groundHeight) dinoSprite.setPosition(dinoSprite.getPosition().x, groundHeight);
	this->isGrounded = dinoSprite.getPosition().y == groundHeight ? true : false;


	//jmp
	if (isGrounded) {
		velocity.y = 0;
		this->duck = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? true : sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? true : false;
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !duck) { velocity.y = -jumpForce; }
	}
	else {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) /*&&velocity<0 gdybym chcial zrobic spadanie niezaleznie od wcisniecia spacji*/) velocity.y += gravity / 2;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) velocity.y += gravity * 10;
		else velocity.y += gravity;
	}

	if (duck) {
		currentTexture = (DinoTexture)((int)currentTexture + 3);
	}

	//movem
	velocity.x = 0;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && dinoSprite.getPosition().x > 50) velocity.x = -.5f*deltaTime.asMicroseconds() / 1000;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && dinoSprite.getPosition().x < 750) velocity.x = .5f*deltaTime.asMicroseconds() / 1000;
	duck ? dinoSprite.setTextureRect(sf::IntRect(0, 0, 59, 30)) : dinoSprite.setTextureRect(sf::IntRect(0, 0, 44, 47));
	if (duck) dinoSprite.setPosition(dinoSprite.getPosition().x, 283.f);
	dinoSprite.setTexture(day ? dinoTexture[currentTexture] : nightTexture[currentTexture]);

	dinoSprite.move(velocity);

}

void Player::render(sf::RenderWindow &window)
{
	window.draw(this->dinoSprite);
}

void Player::restart()
{
	this->currentTexture = START;
	this->dinoSprite.setTexture(dinoTexture[currentTexture]);
	this->dinoSprite.setPosition(sf::Vector2f(50.f, 266.f));
	this->dinoSprite.setColor(sf::Color(255, 255, 255, 255));

	this->velocity = sf::Vector2f(0.f, 0.f);
}

void Player::die(bool day)
{
	this->dinoSprite.setTextureRect(sf::IntRect(0, 0, 44, 47));
	this->dinoSprite.setTexture(day ? dinoTexture[END] : nightTexture[END]);
}



sf::Sprite Player::getDinoSprite() {
	return dinoSprite;
}

Player::Player() :groundHeight(266.f), gravity(.0004f), isGrounded(true), jumpForce(.3f), duck(false)
{
	if (!this->dinoTexture[START].loadFromFile("Assets/dinoStart.png")) abort();
	if (!this->dinoTexture[RUN0].loadFromFile("Assets/dinoRun0.png")) abort();
	if (!this->dinoTexture[RUN2].loadFromFile("Assets/dinoRun2.png")) abort();
	if (!this->dinoTexture[RUN3].loadFromFile("Assets/dinoRun3.png")) abort();
	if (!this->dinoTexture[DUCK0].loadFromFile("Assets/duck0.png", sf::IntRect(0, 0, 59, 30))) abort();
	if (!this->dinoTexture[DUCK2].loadFromFile("Assets/duck2.png", sf::IntRect(0, 0, 59, 30))) abort();
	if (!this->dinoTexture[END].loadFromFile("Assets/dinoEnd.png")) abort();

	if (!this->nightTexture[START].loadFromFile("Assets/dinoStart.png")) abort();
	if (!this->nightTexture[RUN0].loadFromFile("Assets/nightRun0.png")) abort();
	if (!this->nightTexture[RUN2].loadFromFile("Assets/nightRun2.png")) abort();
	if (!this->nightTexture[RUN3].loadFromFile("Assets/nightRun3.png")) abort();
	if (!this->nightTexture[DUCK0].loadFromFile("Assets/nightduck0.png", sf::IntRect(0, 0, 59, 30))) abort();
	if (!this->nightTexture[DUCK2].loadFromFile("Assets/nightduck2.png", sf::IntRect(0, 0, 59, 30))) abort();
	if (!this->nightTexture[END].loadFromFile("Assets/nightEnd.png")) abort();

	this->currentTexture = START;
	this->dinoSprite.setTexture(dinoTexture[currentTexture]);
	this->dinoSprite.setPosition(sf::Vector2f(50.f, 266.f));
	this->dinoSprite.setColor(sf::Color(255, 255, 255, 255));

	this->velocity = sf::Vector2f(0.f, 0.f);
}


Player::~Player()
{
}