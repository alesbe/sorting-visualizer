#include "Sortable.h"

/**
 * @brief Construct a new Sortable object. Sortables are the elements that conforms the main sorting array
 * 
 * @param width width of the sortable on screen
 * @param height height of the sortable on screen
 * @param value associated value to each element used to sort
 */
Sortable::Sortable(float width, float height, int value) {
	this->width = width;
	this->height = height;
	this->value = value;
}

/**
 * @brief Defines a shape for the sortable
 * 
 * @return sf::RectangleShape prepared to be directly drawn on screen
 */
sf::RectangleShape Sortable::shape() {
	return sf::RectangleShape(sf::Vector2f((float)width, (float)height));
}