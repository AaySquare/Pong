#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Paddle.h"
#include "Ball.h"

class Game
{
private:
	sf::RenderWindow& m_window;

	std::unique_ptr<Paddle> player1;
	std::unique_ptr<Paddle> player2;
	std::unique_ptr<Ball> ball;

	sf::Font font;
	sf::Text title;
	sf::Text description;
	sf::Text pause;
	sf::Text gameOver;
	sf::Text restart;

	sf::SoundBuffer buffer;
	sf::Sound hitSound;

	bool isPaused;
	bool isGameOver;
	bool isStart;

public:
	const unsigned int m_windowWidth;
	const unsigned int m_windowHeight;

public:
	Game(sf::RenderWindow& window, const unsigned int& windowWidth, const unsigned int& windowHeight);
	sf::RenderWindow& GetWindow();
	void RestartGame();
	void HandleCollision();
	void HandleInput();
	void Draw();
	void Update();
	void Run();
};

