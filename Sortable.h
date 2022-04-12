#pragma once
#include <SFML/Graphics.hpp>

class Sortable
{
private:
	sf::Color color = sf::Color::White;

public:
	int value;
	float width, height;

	Sortable(float width, float hight, int value);
	sf::RectangleShape shape();
};

