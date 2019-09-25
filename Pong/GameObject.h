#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
protected:
	sf::Vector2f position;
	float speed;
	sf::RenderWindow& m_window;

public:
	GameObject(float startX, float startY, sf::RenderWindow& window);
	virtual ~GameObject() {};
	virtual void Draw() = 0;
	virtual void Update() = 0;
};