#pragma once
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <atomic>
#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>
#include <SFML/System.hpp>

#include "Sortable.h"
#include "SortAlgorithms.h"

class SortController
{
private:
	// Configurations
	int _winWidth, _winHeight;
	int _timeSleep;
	
	// Sort state
	bool _isSorting = false;
	std::atomic<bool> _interrupt = false;

	// Vector to be sorted
	std::vector<Sortable> _sortElements;

	// Threads
	std::thread _sortingThread;
	std::thread _animThread;

	/*
	This does the actual sorting loop, while `startSort`
	(with no underscore) just starts this function in its own thread
	*/
	void _startSort(int sortType);

public:
	// Constructor
	SortController(sf::Vector2u windowSize, int timeSleep);

	// Getters
	bool isSorting() const { return _isSorting; }
	int winWidth() const { return _winWidth; }
	int winHeight() const { return _winHeight; }
	const std::vector<Sortable>& sortElements() const { return _sortElements; }

	// Vector control methods
	void clear();
	void populate(int numOfElements);
	void randomize();
	void setTimeSleep(int t);
	void displaySortInfo(int sortType, bool isSorting, int numOfComparisons, int sortTime) const;

	// Sorting methods
	void startSort(int sortType);
	void stopSort();
	void checkSortAnim();
	bool isSorted();
};

