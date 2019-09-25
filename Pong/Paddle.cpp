#include "Paddle.h"

Paddle::Paddle(float startX, float startY, sf::RenderWindow& window) 
	: GameObject{ startX, startY, window }
{
	paddleShape.setSize(sf::Vector2f(shapeWidth, shapeHeight));
	paddleShape.setPosition(position);
}

sf::FloatRect Paddle::getPosition()
{
	return paddleShape.getGlobalBounds();
}

sf::RectangleShape Paddle::getShape()
{
	return paddleShape;
}

void Paddle::HandleInput1()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (paddleShape.getPosition().y - paddleShape.getSize().y / 2 > -20.0f))
	{
		paddleShape.move(0.f, -speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (paddleShape.getPosition().y + paddleShape.getSize().y / 2 < m_window.getSize().y - 35.f))
	{
		paddleShape.move(0.f, speed);
	}
}

void Paddle::HandleInput2()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (paddleShape.getPosition().y - paddleShape.getSize().y / 2 > -20.0f))
	{
		paddleShape.move(0.f, -speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (paddleShape.getPosition().y + paddleShape.getSize().y / 2 < m_window.getSize().y - 35.f))
	{
		paddleShape.move(0.f, speed);
	}
}

void Paddle::Draw()
{
	m_window.draw(paddleShape);
}

void Paddle::Update()
{

}
