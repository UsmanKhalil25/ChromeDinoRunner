#pragma once
#include <SFML/Graphics.hpp>
#include "scene.h"
#include "player.h"
#include "obstacles.h"
#include "points.h"


class Manager
{
	enum State {
		Title,
		MainMenu,
		Play,
		Pause,
		GameOver,
		Exit
	};


	sf::Font font; sf::Text deathText[14]; unsigned endText;
	sf::Text pauseText[9]; unsigned hint; 
	sf::Text START; sf::Text howtoplayText;
	sf::Text titleText;
	
	sf::Clock clock;
	sf::Time delta;
	sf::Clock hClock;

	sf::RenderWindow window;
	Scene scene;
	Player player;
	Obstacles obstacles;
	Points points;
	sf::Event event;
	State currentState;
public:
	void handleEvents();
	void update();
	void render();
	bool isOpen();
	bool pollEvent();
	sf::Event::EventType getEventType();
	void close();
	void clear();
	void display();
	int getHighScore();
	void setHighScore(int s);
	Manager();
	virtual ~Manager();
};
