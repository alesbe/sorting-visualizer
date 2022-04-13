#pragma once
#include <vector>
#include <algorithm>
#include <random>
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
	void clear();
	void populate(int numOfElements);
	void startSort(int sortType);
	void randomize();
	bool isSorted();
	void checkSort();
};

