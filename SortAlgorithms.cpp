#include "SortAlgorithms.h"

void algo::bubbleSort(std::vector<Sortable>& sortElements, int timeSleep) {
	for (int n = 0; n < sortElements.size() - 1; n++) {
		if (sortElements[n].value > sortElements[n + 1].value) {
			algoUtils::swap(sortElements, timeSleep, sortElements[n], sortElements[n+1]);
		}
	}
}

void algo::selectionSort(std::vector<Sortable>& sortElements, int timeSleep) {
	for (int n = 0; n <= sortElements.size() - 1; n++) {
		for (int j = n; j <= sortElements.size() - 1; j++) {
			if (sortElements[n].value > sortElements[j].value) {
				algoUtils::swap(sortElements, timeSleep, sortElements[n], sortElements[j]);
			}
		}
	}
}

void algoUtils::swap(std::vector<Sortable>& sortElements, int timeSleep, Sortable& el1, Sortable& el2) {
	el1.color = sf::Color::Red;
	el2.color = sf::Color::Red;

	// Swap positions
	auto currElement = el1;
	auto tempElement = el2;
	el1 = tempElement;
	el2 = currElement;

	// Wait timeSleep ms between iterations
	sf::sleep(sf::milliseconds(timeSleep));

	el1.color = sf::Color::White;
	el2.color = sf::Color::White;
}