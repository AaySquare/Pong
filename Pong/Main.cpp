#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	const unsigned int windowWidth = 800;
	const unsigned int windowHeight = 600;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "PONG GAME");

	Game game(window, windowWidth, windowHeight);
	game.Run();

	return 0;
}