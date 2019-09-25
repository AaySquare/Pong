#include "GameObject.h"

GameObject::GameObject(float startX, float startY, sf::RenderWindow& window) 
	: position{ startX, startY }
	, speed{ 0.3 }
	, m_window{ window }
{
}
