#include "Sortable.h"

Sortable::Sortable(float width, float height, int value) {
	this->width = width;
	this->height = height;
	this->value = value;
}

sf::RectangleShape Sortable::shape() {
	return sf::RectangleShape(sf::Vector2f((float)width, (float)height));
}