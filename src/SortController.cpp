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
 */
void SortController::clear() {
	_sortElements.clear();
}

/**
 * @brief Populate the array with Sortable elements
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
 * @brief Loop the sort algorithm until is sorted or stopped
 * 
 * @param sortType Number associated to each sort type
 */
void SortController::_startSort(int sortType) {
	int numOfComparisons = 0;
	sf::Clock sortTime;

	// Display sort info, (_isSorting) should be false, so it will display "Sorting..."
	displaySortInfo(sortType, _isSorting, numOfComparisons, sortTime.getElapsedTime().asMilliseconds());

	// Loop the current algorithm until the array is sorted or interrupted
	while (!isSorted() && !_interrupt)
	{
		switch (sortType)
		{
		case 0:
			numOfComparisons += algo::bubbleSort(_sortElements, _timeSleep, _interrupt);
			break;
		case 1:
			numOfComparisons += algo::selectionSort(_sortElements, _timeSleep, _interrupt);
			break;
		case 2:
			numOfComparisons += algo::insertionSort(_sortElements, _timeSleep, _interrupt);
			break;
		case 3:
			numOfComparisons += algo::quickSort(_sortElements, _timeSleep, _interrupt);
			break;
		case 4:
			numOfComparisons += algo::cocktailSort(_sortElements, _timeSleep, _interrupt);
			break;
		case 5:
			numOfComparisons += algo::bogoSort(_sortElements, _timeSleep, _interrupt);
			break;
		default:
			return;
		}
	}

	// When the sort is finished or interrupted, _isSorting is false
	_isSorting = false;

	/*
	If the sorting was interrupted, the array is not sorted
	so we replace it with a sorted array so the animation
	looks correct
	*/
	if (_interrupt) {
		int n = _sortElements.size();
		clear();
		populate(n);
	}

	// Display sort info, (_isSorting) should be true, so it will display the sort stats
	displaySortInfo(sortType, _isSorting, numOfComparisons, sortTime.getElapsedTime().asMilliseconds());

	// Run the final animation in a separated thread to prevent issues
	_animThread = std::thread(&SortController::checkSortAnim, this);
	_animThread.detach();
}

/**
 * @brief Start the sort thread
 * 
 * @param sortType Number associated to the algorithm
 */
void SortController::startSort(int sortType) {
	/*
	If the last sort completed on its own, the thread has not
	been joined yet, so we need to join it
	*/
	if (_sortingThread.joinable()) {
		_sortingThread.join();
	}

	_interrupt = false;
	_isSorting = true;

	_sortingThread = std::thread(&SortController::_startSort, this, sortType);
}

/**
 * @brief Stop the sorting activating the interrupt and joining the sort thread
 * 
 */
void SortController::stopSort() {
	/*
	This only happens if `stopSort` was already called,
	so the thread is already joined
	*/
	if (!_sortingThread.joinable()) {
		return;
	}

	_interrupt = true;
	_sortingThread.join();
	_isSorting = false;
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
