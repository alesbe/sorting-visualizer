#pragma once
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
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
	void displaySortInfo(int sortType, bool isSorting, int numOfComparisons, int sortTime);

	// Sorting methods
	void startSort(int sortType);
	void checkSortAnim();
	bool isSorted();
};

