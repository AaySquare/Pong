#pragma once
#include "GameObject.h"

class Paddle : public GameObject
{
private:
	sf::RectangleShape paddleShape;
	static constexpr int shapeWidth = 10;
	static constexpr int shapeHeight = 50;

public:
	Paddle(float startX, float startY, sf::RenderWindow& window);
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
	void HandleInput1();
	void HandleInput2();
	void Draw() override;
	void Update() override;
};

