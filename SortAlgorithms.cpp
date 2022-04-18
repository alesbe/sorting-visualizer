#include "SortAlgorithms.h"

int algo::bubbleSort(std::vector<Sortable>& sortElements, int timeSleep) {
	int numOfComparisons = 0;

	for (int n = 0; n < sortElements.size() - 1; n++) {
		if (sortElements[n].value > sortElements[n + 1].value) {
			algoUtils::swap(sortElements, timeSleep, sortElements[n], sortElements[n+1]);
		}
		numOfComparisons++;
	}

	return numOfComparisons;
}

int algo::selectionSort(std::vector<Sortable>& sortElements, int timeSleep) {
	int numOfComparisons = 0;

	for (int n = 0; n <= sortElements.size() - 1; n++) {
		for (int j = n; j <= sortElements.size() - 1; j++) {
			if (sortElements[n].value > sortElements[j].value) {
				algoUtils::swap(sortElements, timeSleep, sortElements[n], sortElements[j]);

			}
			numOfComparisons++;
		}
	}

	return numOfComparisons;
}

int algo::insertionSort(std::vector<Sortable>& sortElements, int timeSleep) {
	int numOfComparisons = 0;

	for (int n = 1; n < sortElements.size(); n++)
	{
		auto temp = sortElements[n];
		int j = n - 1;
		while (j >= 0 && temp.value <= sortElements[j].value)
		{
			sortElements[j].color = sf::Color::Red;

			sortElements[j + 1] = sortElements[j];

			sf::sleep(sf::milliseconds(timeSleep));
			sortElements[j+1].color = sf::Color::White;
			
			j = j - 1;

			numOfComparisons++;

		}
		sortElements[j + 1] = temp;
		numOfComparisons++;
	}

	return numOfComparisons;
}

void algoUtils::swap(std::vector<Sortable>& sortElements, int timeSleep, Sortable& el1, Sortable& el2) {
	el1.color = sf::Color::Red;
	el2.color = sf::Color::Red;

	auto currElement = el1;
	auto tempElement = el2;
	el1 = tempElement;
	el2 = currElement;

	sf::sleep(sf::milliseconds(timeSleep));

	el1.color = sf::Color::White;
	el2.color = sf::Color::White;
}