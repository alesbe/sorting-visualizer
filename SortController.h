#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <SFML/System.hpp>

#include "Sortable.h"
#include "SortAlgorithms.h"

class SortController
{
public:
	bool isSorting = false;
	int winWidth, winHeight;
	int timeSleep;

	std::vector<Sortable> sortElements;

	SortController(sf::Vector2u windowSize, int timeSleep);

	// Vector control methods
	void clear();
	void populate(int numOfElements);
	void randomize();
	void setTimeSleep(int t);

	// Sorting methods
	void startSort(int sortType);
	void checkSort();
	bool isSorted();
};

