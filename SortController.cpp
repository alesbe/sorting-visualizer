#include "SortController.h"

SortController::SortController(sf::Vector2u windowSize) {
	this->winWidth = windowSize.x;
	this->winHeight = windowSize.y;
}

void SortController::populate(int numOfElements) {
	for (int n = 0; n < numOfElements; n++) {
		Sortable sortable((float)(winWidth / numOfElements), (float)(winHeight / numOfElements) * (n+1), n);
		sortElements.push_back(sortable);
	}
}