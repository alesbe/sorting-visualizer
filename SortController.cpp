#include "SortController.h"
#include <iostream>
#include <SFML/System.hpp>

SortController::SortController(sf::Vector2u windowSize, int timeSleep) {
	this->winWidth = windowSize.x;
	this->winHeight = windowSize.y;

	this->timeSleep = timeSleep;
}

///////////////////////////////
//
// Vector control methods
//
///////////////////////////////

void SortController::clear() {
	sortElements.clear();
}

void SortController::populate(int numOfElements) {
	for (int n = 0; n < numOfElements; n++) {
		Sortable sortable(((float)winWidth / numOfElements), ((float)winHeight / numOfElements) * (n+1), n); // Width defined to space max space in window, height defined by Sortable value
		sortElements.push_back(sortable);
	}
}

void SortController::randomize() {
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{ rd() };
	std::shuffle(std::begin(sortElements), std::end(sortElements), rng);
};

void SortController::setTimeSleep(int t) {
	timeSleep = t;
}

///////////////////////////////
//
// Sorting methods
//
///////////////////////////////

void SortController::startSort(int sortType) {
	isSorting = true;
	sf::Clock timeSort;
	while (!isSorted())
	{

		switch (sortType)
		{
		case 0:
			algo::bubbleSort(sortElements, timeSleep);
			break;
		case 1:
			algo::selectionSort(sortElements, timeSleep);
			break;
		default:
			break;
		}
	}

	std::cout << timeSort.getElapsedTime().asMilliseconds() << "ms" << std::endl;
	checkSort();
	isSorting = false;
}

bool SortController::isSorted() {
	for (int n = 0; n < sortElements.size()-1; n++) {
		if (sortElements[n].value > sortElements[n+1].value)
		{
			return false;
		}
	}

	return true;
};

// This function is only for the "checking animation", at this point, the vector is 100% sorted, verified by isSorted()
void SortController::checkSort() {
	for (int n = 0; n < sortElements.size(); n++) {
		sortElements[n].color = sf::Color::Green;
		sf::sleep(sf::milliseconds(timeSleep));
	}
};