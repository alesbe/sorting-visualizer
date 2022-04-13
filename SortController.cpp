#include "SortController.h"

SortController::SortController(sf::Vector2u windowSize, int timeSleep) {
	this->winWidth = windowSize.x;
	this->winHeight = windowSize.y;

	this->timeSleep = timeSleep;
}

void SortController::clear() {
	sortElements.clear();
}

void SortController::populate(int numOfElements) {
	for (int n = 0; n < numOfElements; n++) {
		Sortable sortable((float)(winWidth / numOfElements), (float)(winHeight / numOfElements) * (n+1), n); // Width defined to space max space in window, height defined by Sortable value
		sortElements.push_back(sortable);
	}
}

void SortController::startSort(int sortType) {
	while (!isSorted()) {
		if (sortType == 0) {
			algo::bubbleSort(sortElements, timeSleep);
		}
	}
}

void SortController::randomize() {
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(sortElements), std::end(sortElements), rng);
};

bool SortController::isSorted() {
	for (int n = 0; n < sortElements.size()-1; n++) {
		if (sortElements[n].value > sortElements[n+1].value)
		{
			return false;
		}
	}

	return true;
};

void SortController::checkSort() {

};