#pragma once
#include <vector>
#include "Sortable.h"
#include "SortAlgorithms.h"

class SortController
{
public:
	int winWidth, winHeight;

	std::vector<Sortable> sortElements;
	int sortAlgorithm = 0; // 0 bubble, 1 insertion, 2 = boggo...

	SortController(sf::Vector2u windowSize);
	void populate(int numOfElements);
	void startSort();
};

