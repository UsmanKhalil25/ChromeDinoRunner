#pragma once
#include <SFML/Graphics.hpp>

enum SCENETEX { CLOUD, GROUND, STAR0, STAR1, STAR2, MOON0, MOON1, MOON2, MOON3, MOON4, MOON5, MOON6, MOON7, MOON8 };

class Scene
{
	sf::Font font;
	unsigned score;
	sf::Text scoreText;
	unsigned hScore;
	sf::Text hScoreText;
	sf::Text HealthText;
	unsigned health;
	sf::Clock scoreClock;
	sf::Clock dClock;
	sf::Time deltaTime;
	bool day;
	sf::Texture sceneTexture[14];
	sf::Sprite ground[2];
	sf::Sprite clouds[3];
	int derSpeedSir[3];
	sf::Sprite moon;
	sf::Sprite stars[5];
public:
	bool getDay();
	void handleEvents(sf::Event &event);
	void update(sf::Time deltatime);
	void render(sf::RenderWindow &window);
	void restart();
	void updateScore();
	void resetScore();
	void decreaseHealth();
	int getHealth();
	const int getHighScore();
	void setHighScore(int s);
	bool getGameOver();
	Scene();
	~Scene();
};
