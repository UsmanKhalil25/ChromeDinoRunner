#include "manager.h"
#include<iostream>


void Manager::handleEvents()
{
	// Handle events based on the current state
	switch (currentState) {
	case Title:
		// Handle events for the Title state
		if (event.key.code == sf::Keyboard::Return && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			this->currentState = MainMenu;
		break;
	case MainMenu:
		if (event.key.code == sf::Keyboard::Q && sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			this->currentState = Exit;
		if (event.key.code == sf::Keyboard::Return && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){\
			this->scene.resetScore();
			points.restart();
			obstacles.restart();
			player.restart();
			scene.restart();
			endText < 13 ? endText++ : endText = 1;
			this->currentState = Play;
		}

		break;
	case Play:
		// Handle events for the Play state
		if ( event.type == event.KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Numpad0 || event.key.code == sf::Keyboard::E)) {
			hint < 8 ? hint++ : hint = 1;
			this->currentState = Pause;

		}
		
		break;
	case Pause:
		if (event.type == event.KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Numpad0 || event.key.code == sf::Keyboard::E)) {
			this->currentState = Play;
		}
		if (event.type == event.KeyPressed && (event.key.code == sf::Keyboard::Q))
			this->currentState = MainMenu;
		break;
	case GameOver:

		if (this->scene.getGameOver() && event.type == event.KeyPressed) {
			this->currentState = MainMenu;
			this->scene.restart();
		}

		break;
	case Exit:
		// Handle events for the Exit state
		this->close();
		break;
	}
}


void Manager::update()
{
	delta = clock.restart();
	// Update based on the current state
	switch (currentState) {
	case Play:
		this->obstacles.updateGameOver(player.getDinoSprite());
		if (obstacles.getCollideCheck()) {
			this->scene.decreaseHealth();
			this->obstacles.resetCollideCheck();
		}
		if (this->scene.getGameOver()) {
			this->currentState = GameOver;
		}
		this->points.updateIncreaseScore(player.getDinoSprite());
		if (this->currentState != GameOver) {

			this->scene.update(delta);
			this->player.update(this->scene.getDay(), event, delta);
			this->points.update(this->scene.getDay(), delta);
			this->obstacles.update(this->scene.getDay(), delta);
			if (this->points.getPoints() == 1) {
				this->scene.updateScore();
				this->points.resetPoints();
			}
		}
		break;
	case GameOver:
		this->scene.resetScore();
		player.die(scene.getDay());

		break;
	}
}


void Manager::render()
{
	// Render based on the current state

	switch (currentState) {
	case Title:
		// Render logic for the Title state
		window.draw(titleText);
		break;
	case MainMenu:
		// Render logic for the Main Menu state

		this->clear();
	
		this->scene.render(this->window);
		window.draw(START);
		window.draw(howtoplayText);
		break;
	case Play:
		// Render logic for the Play state
		this->scene.render(this->window);
		this->points.render(this->window);
		this->obstacles.render(this->window);
		this->player.render(this->window);
		break;
	case Pause:
		// Render logic for the Pause state
		pauseText[3].setString("I was launched exactly\n        " + std::to_string((int)hClock.getElapsedTime().asSeconds()) + "\n                seconds ago.");
		this->window.draw(pauseText[0]);
		this->window.draw(pauseText[hint]);
		break;
	case GameOver:
		this->window.draw(deathText[0]);
		this->window.draw(deathText[endText]);
		break;
	case Exit:
		// Render logic for the Exit state
		this->close();
		break;
	}
}

bool Manager::isOpen()
{
	return this->window.isOpen();
}

bool Manager::pollEvent()
{
	return this->window.pollEvent(this->event);
}

sf::Event::EventType Manager::getEventType()
{
	return this->event.type;
}

void Manager::close()
{
	this->window.close();
}

void Manager::clear()
{

	this->window.clear(this->scene.getDay() ? sf::Color(255, 255, 255, 255) : sf::Color(0, 0, 0, 255));
}

void Manager::display()
{
	this->window.display();
}

int Manager::getHighScore()
{
	return scene.getHighScore();
}

void Manager::setHighScore(int s)
{
	scene.setHighScore(s);
}

Manager::Manager() : window(sf::VideoMode(800, 400), "Dino Runner", sf::Style::Close | sf::Style::Titlebar)
{

	this->currentState = Title;
	srand(NULL);

	if (!font.loadFromFile("Assets/8bitOperatorPlus8-Bold.ttf")) abort();
	for (size_t i = 0; i < 14; i++) deathText[i].setFont(font);
	for (size_t i = 0; i < 9; i++) pauseText[i].setFont(font);
	START.setFont(font);
	howtoplayText.setFont(font);
	titleText.setFont(font);
	titleText.setString("Press ENTER to jump into Jurassic Park");

	deathText[0].setString("DEAD!");
	pauseText[0].setString("PAUSE");
	START.setString("DinoRunner");
	howtoplayText.setString("Movement - WSAD/arrows\n      Pause - Escape / E / Numpad0\n            Quit - Q\n\n\n\n\n\n\n\nPress any key to continue...");

	deathText[1].setString("K.O.");
	deathText[2].setString("And that's how dinosaurs become extinct!");
	deathText[3].setString("You motherf****r! You murdered him!");
	deathText[4].setString("Fatality!");
	deathText[5].setString("Are you proud of yourself?");
	deathText[6].setString("Not even funny anymore...");
	deathText[7].setString("Even my mother could beat you in this game!");
	deathText[8].setString("Don't be fooled. Earth is flat.");
	deathText[9].setString("You had one job.");
	deathText[10].setString("Caroline told me that if you quit now\n        you will get a cake.");
	deathText[11].setString("Go home and be a family man!");
	deathText[12].setString("It's super effective!");
	deathText[13].setString("This way you will never knew what's above 99999.");

	pauseText[1].setString("To cheat a little bit - press 'Q'!");
	pauseText[2].setString("Press 'P' and see what will happen!");
	pauseText[3].setString("Amount of seconds you're in\n" + (int)hClock.getElapsedTime().asSeconds());
	pauseText[4].setString("Give up. Just close the game and let him die.");
	pauseText[5].setString("There is no escape.");
	pauseText[6].setString("You have to avoid obstacles.");
	pauseText[7].setString("Oh, come on. Hi. Welcome. AGAIN...");
	pauseText[8].setString("\"Hint: That's not a hint.\"\n        Is the above a hint?");

	deathText[0].setPosition(150.f, -50.f);
	deathText[0].setCharacterSize(192);
	deathText[0].setRotation(20.f);
	pauseText[0].setPosition(50.f, 200.f);
	pauseText[0].setCharacterSize(192);
	pauseText[0].setRotation(-20.f);

	START.setPosition(50.f, 50.f);
	howtoplayText.setPosition(75.f, 125.f);
	titleText.setPosition(145.f, 180.f);
	START.setCharacterSize(60);
	howtoplayText.setCharacterSize(20);
	titleText.setCharacterSize(22);

	for (size_t i = 1; i < 14; i++) {
		deathText[i].setPosition(100.f, 150.f);
		deathText[i].setCharacterSize(20);
		deathText[i].setRotation(20.f);
	}
	for (size_t i = 0; i < 14; i++) {
		deathText[i].setFillColor(sf::Color(153, 0, 51, 255));
		deathText[i].setOutlineThickness(2.f);
		deathText[i].setOutlineColor(sf::Color(255, 255, 255, 255));
	}
	for (size_t i = 1; i < 9; i++) {
		pauseText[i].setPosition(250.f, 350.f);
		pauseText[i].setCharacterSize(20);
		pauseText[i].setRotation(-20.f);
	}
	for (size_t i = 0; i < 9; i++) {
		pauseText[i].setFillColor(sf::Color(0, 102, 153, 255));
		pauseText[i].setOutlineThickness(2.f);
		pauseText[i].setOutlineColor(sf::Color(255, 255, 255, 255));
	}
	hint = 1;
	endText = rand() % 13 + 1;
	START.setFillColor(sf::Color(153, 128, 0, 255));
	howtoplayText.setFillColor(sf::Color(153, 128, 0, 255));
	titleText.setFillColor(sf::Color(153, 128, 0, 255));
	START.setOutlineThickness(2.f);
	howtoplayText.setOutlineThickness(2.f);
	titleText.setOutlineThickness(2.f);
	START.setOutlineColor(sf::Color::White);
	howtoplayText.setOutlineColor(sf::Color::White);
	titleText.setOutlineColor(sf::Color::White);
}

Manager::~Manager() {}