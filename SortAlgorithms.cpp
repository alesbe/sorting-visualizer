#include "SortAlgorithms.h"

void algo::bubbleSort(std::vector<Sortable>& sortElements, int timeSleep) {
	for (int n = 0; n < sortElements.size() - 1; n++) {
		if (sortElements[n].value > sortElements[n + 1].value) {
			sortElements[n+1].color = sf::Color::Red;
			sortElements[n].color = sf::Color::Red;

			// Swap positions
			auto currElement = sortElements[n];
			auto tempElement = sortElements[n + 1];
			sortElements[n + 1] = currElement;
			sortElements[n] = tempElement;

			// Wait timeSleep ms between iterations
			sf::sleep(sf::milliseconds(timeSleep));

			sortElements[n+1].color = sf::Color::White;
			sortElements[n].color = sf::Color::White;
		}
	}
}