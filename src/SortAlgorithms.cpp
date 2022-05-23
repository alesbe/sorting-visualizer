#include "SortAlgorithms.h"

#include <tuple>

using SortableIterator = std::vector<Sortable>::iterator;
using std::tuple;

//
// ────────────────────────────────────────────────────────────────────── I ──────────
//   :::::: S O R T   A L G O R I T H M S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────────────────
//

/**
 * @brief Bubble sort
 * 
 * @param sortElements Main array containing the elements to be sorted
 * @param timeSleep Time to wait between iterations in miliseconds
 * @return Number of comparisons made
 */
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

/**
 * @brief Selection sort
 * 
 * @param sortElements Main array containing the elements to be sorted
 * @param timeSleep Time to wait between iterations in miliseconds
 * @return Number of comparisons made
 */
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

/**
 * @brief Insertion sort
 * 
 * @param sortElements Main array containing the elements to be sorted
 * @param timeSleep Time to wait between iterations in miliseconds
 * @return Number of comparisons made
 */
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

/**
 * @brief QuickSort Partition step. Iterators follow STL style for ranges.
 * 
 * @param parent  The parent array, needed for the swap utilities.
 * @param beg First element of the sub array
 * @param end "One past the last" element of the sub array
 * @param timeSleep pauses the thread for this many ms
 * @return tuple, first is the pivot, second is the number of comparisons
 */
static int quickSortHelper(std::vector<Sortable>& parent, SortableIterator beg, SortableIterator end, int timeSleep);
static tuple<SortableIterator, int> quickSortPartition(std::vector<Sortable>& parent, SortableIterator beg, SortableIterator end, int timeSleep);

static int quickSortHelper(std::vector<Sortable>& parent, SortableIterator beg, SortableIterator end, int timeSleep) {
	// base case
	if (end - beg < 2) return 0;

	auto [pivot, numOfComparisons] = quickSortPartition(parent, beg, end, timeSleep);
	return numOfComparisons +
		quickSortHelper(parent, beg, pivot, timeSleep) +
		quickSortHelper(parent, pivot + 1, end, timeSleep);

}

static tuple<SortableIterator, int> quickSortPartition( std::vector<Sortable>& parent, SortableIterator beg, SortableIterator end, int timeSleep) {
	auto pivot = end - 1;
	int numOfComparisons = 0;

	auto lhs = beg;
	for (auto rhs = lhs; rhs != pivot; ++rhs) {
		++numOfComparisons;
		if (rhs->value <= pivot->value) {
			algoUtils::swap(parent, timeSleep, *lhs, *rhs);
			++lhs;
		}
	}
	algoUtils::swap(parent, timeSleep, *lhs, *pivot);
	return tuple{lhs, numOfComparisons};
}

int algo::quickSort(std::vector<Sortable>& sortElements, int timeSleep) {
	return quickSortHelper(sortElements, sortElements.begin(), sortElements.end(), timeSleep);
}

//
// ────────────────────────────────────────────────────────── II ──────────
//   :::::: U T I L I T I E S : :  :   :    :     :        :          :
// ────────────────────────────────────────────────────────────────────
//



/**
 * @brief algoUtils::swap - Utility function for swapping elements and changing the colors on swap.
 * 
 * @param sortElements The array where the elements being swapped are located
 * @param timeSleep Time in milliseconds to wait between swaps
 * @param el1 First element to be swapped
 * @param el2 Second element to be swapped
 */
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
