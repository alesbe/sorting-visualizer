#include "SortController.h"
#include "Utils.h"

/**
 * @brief Sort controller constructor
 * 
 * @param windowSize Window size vector (x, y)
 * @param timeSleep Time to wait between iterations while sorting in miliseconds
 */
SortController::SortController(sf::Vector2u windowSize, int timeSleep)
:	_winWidth(windowSize.x), _winHeight(windowSize.y), _timeSleep(timeSleep) {
	//
}

//
// ──────────────────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: V E C T O R   C O N T R O L   M E T H O D S : :  :   :    :     :        :          :
// ──────────────────────────────────────────────────────────────────────────────────────────────
//

/**
 * @brief Empty the array
 * 
 */
void SortController::clear() {
	_sortElements.clear();
}

/**
 * @brief Populate the array with Sorable elements
 * 
 * @param numOfElements Number of elements to be included in the array (array size)
 */
void SortController::populate(int numOfElements) {
	for (int n = 0; n < numOfElements; n++) {
		Sortable sortable(((float)_winWidth / numOfElements), ((float)_winHeight / numOfElements) * (n+1), n); // Width defined for max space in window, height defined by element value
		_sortElements.push_back(sortable);
	}
}

/**
 * @brief Randomize element positions inside the array
 * 
 */
void SortController::randomize() {
	std::random_shuffle(std::begin(_sortElements), std::end(_sortElements));
};

/**
 * @brief Update time sleep
 * 
 * @param t Time to wait between iterations while sorting in miliseconds
 */
void SortController::setTimeSleep(int t) {
	_timeSleep = t;
}

/**
 * @brief Display sort info on terminal after the algorithm finished
 * 
 * @param sortType Number associated to each sort type
 * @param isSorting true = display only sort type and sorting message, false = display all info
 * @param numOfComparisons Number of comparisons that the algorithm running made
 * @param sortTime Time that the algorithm took to sort all elements
 * 
 * 
 */
void SortController::displaySortInfo(int sortType, bool isSorting, int numOfComparisons, int sortTime) const {
	system(CLEAR);
	
	std::cout << "Sort type: " << Utils::getSortType(sortType) << std::endl << std::endl;

	if (isSorting) {
		std::cout << std::endl << "Sorting..." << std::endl;
	}
	else {
		std::cout << "Sort time: " << sortTime << "ms || " << (double)sortTime/1000 << "s" << std::endl;
		std::cout << "Number of elements: " << _sortElements.size() << std::endl;
		std::cout << "Time between comparisons: " << _timeSleep << "ms" << std::endl;
		std::cout << "Number of comparisons: " << numOfComparisons << std::endl;
	}
}

//
// ────────────────────────────────────────────────────────────────────── II ──────────
//   :::::: S O R T I N G   M E T H O D S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────
//

/**
 * @brief Start sort timer, run the algorithm and increment the number of comparisons while the array isn't sorted, and display sort info at the end.
 * 
 * @param sortType Number associated to the algorithm
 */
void SortController::startSort(int sortType) {
	_isSorting = true;
	int numOfComparisons = 0;
	sf::Clock sortTime;

	displaySortInfo(sortType, _isSorting, numOfComparisons, sortTime.getElapsedTime().asMilliseconds());

	while (!isSorted())
	{
		switch (sortType)
		{
		case 0:
			numOfComparisons += algo::bubbleSort(_sortElements, _timeSleep);
			break;
		case 1:
			numOfComparisons += algo::selectionSort(_sortElements, _timeSleep);
			break;
		case 2:
			numOfComparisons += algo::insertionSort(_sortElements, _timeSleep);
			break;
		case 3:
			numOfComparisons += algo::quickSort(_sortElements, _timeSleep);
			break;
		case 4:
			numOfComparisons += algo::cocktailSort(_sortElements, _timeSleep);
			break;
		case 5:
			numOfComparisons += algo::bogoSort(_sortElements, _timeSleep);
			break;
		default:
			return;
		}
	}

	_isSorting = false;
	displaySortInfo(sortType, _isSorting, numOfComparisons, sortTime.getElapsedTime().asMilliseconds());
	checkSortAnim();
}

/**
 * @brief Iterate one time through the array to check if is sorted
 * 
 * @return true The array is sorted
 * @return false The array isn't sorted
 */
bool SortController::isSorted() {
	for (int n = 0; n < _sortElements.size()-1; n++) {
		if (_sortElements[n].value > _sortElements[n+1].value)
		{
			return false;
		}
	}

	return true;
};

/**
 * @brief Do a checking animation from the start to the end of the array changing color to green to show that the algorithm finished.
 * (Does not check the array, only does the color animation)
 * 
 */
void SortController::checkSortAnim() {
	for (int n = 0; n < _sortElements.size(); n++) {
		_sortElements[n].color = sf::Color::Green;
		sf::sleep(sf::milliseconds(1));
	}
};
