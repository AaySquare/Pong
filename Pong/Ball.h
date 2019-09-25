#pragma once

#include "GameObject.h"
#include "Paddle.h"

class Ball : public GameObject
{
private:
	sf::CircleShape ballShape;
	static constexpr float radius = 10.0f;

public:
	float ballAngle = 0.0f;
	static constexpr float pi = 3.14159f;

public:
	Ball(float startX, float startY, sf::RenderWindow& window);
	sf::FloatRect getPosition();
	sf::CircleShape getShape();
	float getRadius();
	void reboundTop();
	void reboundBottom();
	void reboundBat();
	void Draw() override;
	void Update() override;
};

