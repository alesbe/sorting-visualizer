#include "SortAlgorithms.h"
#include <iostream>
#include <chrono>
#include <thread>

namespace algo {
	void bubbleSort(std::vector<Sortable>& sortElements, int timeSleep) {

		for (int n = 0; n < sortElements.size() - 1; n++) {

			/*
			std::cout << "[";
			for (auto i : sortElements) {
				std::cout << i.value << ", ";
			}
			std::cout << "]" << std::endl;
			
			*/

			if (sortElements[n].value > sortElements[n + 1].value) {
				// Change color while sorting
				sortElements[n].color = sf::Color::Red;
				sortElements[n+1].color = sf::Color::Red;

				// Swap positions
				auto currElement = sortElements[n];
				auto tempElement = sortElements[n + 1];
				sortElements[n + 1] = currElement;
				sortElements[n] = tempElement;

				// Reset color
				sortElements[n].color = sf::Color::White;
				sortElements[n + 1].color = sf::Color::White;
			}

			// Wait timeSleep ms between iterations
			std::this_thread::sleep_for(std::chrono::milliseconds(timeSleep));
		}
	}
}