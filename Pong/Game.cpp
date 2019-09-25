#include "Game.h"

Game::Game(sf::RenderWindow& window, const unsigned int& windowWidth, const unsigned int& windowHeight) 
	: m_window{ window }
	, m_windowWidth{ windowWidth }
	, m_windowHeight{ windowHeight }
{
	RestartGame();

	font.loadFromFile("resources/American Captain.ttf");
	title.setFont(font);
	title.setCharacterSize(50);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	title.setPosition(((float)m_windowWidth / 2) - 150, ((float)m_windowHeight / 2) - 100);

	description.setFont(font);
	description.setCharacterSize(25);
	description.setFillColor(sf::Color::White);
	description.setStyle(sf::Text::Regular);
	description.setPosition(((float)m_windowWidth / 2) - 150, ((float)m_windowHeight / 2) - 30);

	gameOver.setFont(font);
	gameOver.setCharacterSize(42);
	gameOver.setFillColor(sf::Color::White);
	gameOver.setStyle(sf::Text::Bold);
	gameOver.setPosition(((float)m_windowWidth / 2) - 100, (float)m_windowHeight / 2);

	pause.setFont(font);
	pause.setCharacterSize(42);
	pause.setFillColor(sf::Color::White);
	pause.setStyle(sf::Text::Regular);
	pause.setPosition(((float)m_windowWidth / 2) - 80, (float)m_windowHeight / 2);

	restart.setFont(font);
	restart.setCharacterSize(25);
	restart.setFillColor(sf::Color::White);
	restart.setStyle(sf::Text::Regular);
	restart.setPosition(((float)m_windowWidth / 2) - 100, ((float)m_windowHeight / 2) + 50);

	buffer.loadFromFile("resources/ball.wav");
	hitSound.setBuffer(buffer);
}

sf::RenderWindow& Game::GetWindow()
{
	return m_window;
}

void Game::RestartGame()
{
	isPaused = false;
	isGameOver = false;
	gameOver.setString("");
	pause.setString("");
	restart.setString("");
	player1 = std::make_unique<Paddle>(40, m_windowHeight / 2, m_window);
	player2 = std::make_unique<Paddle>(m_windowWidth - 50, m_windowHeight / 2, m_window);
	ball = std::make_unique<Ball>(m_windowWidth / 2, m_windowHeight / 2, m_window);
}

void Game::HandleCollision()
{
	if (ball->getShape().getPosition().x - ball->getRadius() < 0.0f)
	{
		isGameOver = true;
		gameOver.setString("PLAYER 2 WINS!");
		restart.setString("Press R to restart\nPress Esc to Quit");
	}
	else if (ball->getShape().getPosition().x + ball->getRadius() > m_windowWidth)
	{
		isGameOver = true;
		gameOver.setString("PLAYER 1 WINS!");
		restart.setString("Press R to restart\nPress Esc to Quit");
	}
	else if (ball->getShape().getPosition().y - ball->getRadius() < 0.0f)
	{
		hitSound.play();
		ball->reboundTop();
	}
	else if (ball->getShape().getPosition().y + ball->getRadius() > m_windowHeight)
	{
		hitSound.play();
		ball->reboundBottom();
	}
	else if (ball->getPosition().intersects(player2->getPosition()))
	{
		hitSound.play();
		if (ball->getShape().getPosition().y > player2->getShape().getPosition().y)
			ball->ballAngle = ball->pi - ball->ballAngle + (std::rand() % 20) * ball->pi / 180;
		else
			ball->ballAngle = ball->pi - ball->ballAngle - (std::rand() % 20) * ball->pi / 180;

		ball->getShape().setPosition(player2->getShape().getPosition().x - ball->getRadius() - player2->getShape().getSize().x / 2 - 0.1f, ball->getShape().getPosition().y);
	}

	else if (ball->getPosition().intersects(player1->getPosition()))
	{
		hitSound.play();
		if (ball->getShape().getPosition().y > player1->getShape().getPosition().y)
			ball->ballAngle = ball->pi - ball->ballAngle + (std::rand() % 20) * ball->pi / 180;
		else
			ball->ballAngle = ball->pi - ball->ballAngle - (std::rand() % 20) * ball->pi / 180;

		ball->getShape().setPosition(player1->getShape().getPosition().x - ball->getRadius() - player1->getShape().getSize().x / 2 - 0.1f, ball->getShape().getPosition().y);
	}
}

void Game::HandleInput()
{
	player1->HandleInput1();
	player2->HandleInput2();
}

void Game::Draw()
{
	if (!isGameOver && isStart)
	{
		player1->Draw();
		player2->Draw();
		ball->Draw();
	}

	if (!isStart)
	{
		m_window.draw(title);
		m_window.draw(description);
	}
	
	m_window.draw(pause);
	m_window.draw(gameOver);
	m_window.draw(restart);
}

void Game::Update()
{
	player1->Update();
	player2->Update();
	ball->Update();
}

void Game::Run()
{
	//Game Loop
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
			{
				if(!isGameOver && isStart)
					isPaused = !isPaused;
			}
				
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
				RestartGame();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				isStart = true;
		}

		m_window.clear();

		title.setString("Welcome to PONG");
		description.setString(
			"Press Space to start playing\n\n\n"
			"Player 1(Left) controls: W and S\n"
			"Player 2(right) controls: Up and Down arrows\n"
			"Press R to restart\n"
			"Press Esc to Quit"
		);
		if (isStart)
		{
			title.setString("");
			HandleCollision();

			if (!isPaused)
			{
				HandleInput();
				Update();
			}

			if (isPaused)
				pause.setString("Game Paused");
			else
				pause.setString("");
		}
		
		Draw();
		
		m_window.display();
	}
}
