#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Sortable
{
public:
	sf::Color color = sf::Color::White;
	int value;
	float width, height;

	Sortable(float width, float hight, int value);
	sf::RectangleShape shape();
};

