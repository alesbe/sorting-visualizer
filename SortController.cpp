#include "SortController.h"
#include "Utils.h"

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
		Sortable sortable(((float)winWidth / numOfElements), ((float)winHeight / numOfElements) * (n+1), n); // Width defined for max space in window, height defined by element value
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

void SortController::displaySortInfo(int sortType, bool isSorting, int numOfComparisons, int sortTime) {
	system(CLEAR);
	
	std::cout << "Sort type: " << Utils::getSortType(sortType) << std::endl << std::endl;

	if (isSorting) {
		std::cout << std::endl << "Sorting..." << std::endl;
	}
	else {
		std::cout << "Sort time: " << sortTime << "ms || " << (double)sortTime/1000 << "s" << std::endl;
		std::cout << "Number of elements: " << sortElements.size() << std::endl;
		std::cout << "Time between comparisons: " << timeSleep << "ms" << std::endl;
		std::cout << "Number of comparisons: " << numOfComparisons << std::endl;
	}
}

///////////////////////////////
//
// Sorting methods
//
///////////////////////////////

void SortController::startSort(int sortType) {
	isSorting = true;
	int numOfComparisons = 0;
	sf::Clock sortTime;

	displaySortInfo(sortType, isSorting, numOfComparisons, sortTime.getElapsedTime().asMilliseconds());

	while (!isSorted())
	{
		switch (sortType)
		{
		case 0:
			numOfComparisons += algo::bubbleSort(sortElements, timeSleep);
			break;
		case 1:
			numOfComparisons += algo::selectionSort(sortElements, timeSleep);
			break;
		case 2:
			numOfComparisons += algo::insertionSort(sortElements, timeSleep);
			break;
        case 3:
            numOfComparisons += algo::quickSort(sortElements, timeSleep);
            break;
		default:
			return;
		}
	}

	isSorting = false;
	displaySortInfo(sortType, isSorting, numOfComparisons, sortTime.getElapsedTime().asMilliseconds());
	checkSortAnim();
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

// This function is only for the "checking animation", the verification is made by isSorted()
void SortController::checkSortAnim() {
	for (int n = 0; n < sortElements.size(); n++) {
		sortElements[n].color = sf::Color::Green;
		sf::sleep(sf::milliseconds(timeSleep));
	}
};
