#include "manager.h"
#include <fstream>

int main()
{
	if (!std::ifstream("resources.dat")) {
		std::ofstream saveHighScores("resources.dat");
		saveHighScores << 0;
		saveHighScores.close();
	}
	std::ifstream loadHighScores("resources.dat", std::ios_base::in);
	Manager game;
	int temp;
	loadHighScores >> temp;
	game.setHighScore(temp);
	loadHighScores.close();
	while (game.isOpen()) {
		while (game.pollEvent()) {
			if (game.getEventType() == sf::Event::Closed) {
				game.close();
			}
			game.handleEvents();
		}
		game.update();
		game.clear();
		game.render();
		game.display();
	}
	temp = game.getHighScore();
	std::ofstream saveHighScores("resources.dat", std::ios_base::out);
	saveHighScores << temp;
	saveHighScores.close();

	return 0;
}