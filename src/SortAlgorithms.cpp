#include "SortAlgorithms.h"

#include <atomic>
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
 * @param interrupt Bool to stop the sort process
 * @return Number of comparisons made
 */
int algo::bubbleSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt) {
	int numOfComparisons = 0;

	for (int n = 0; n < sortElements.size() - 1; n++) {
		if (interrupt) {
			return numOfComparisons;
		}

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
 * @param interrupt Bool to stop the sort process
 * @return Number of comparisons made
 */
int algo::selectionSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt) {
	int numOfComparisons = 0;

	for (int n = 0; n <= sortElements.size() - 1; n++) {
		for (int j = n; j <= sortElements.size() - 1; j++) {
			if (interrupt) {
				return numOfComparisons;
			}

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
 * @param interrupt Bool to stop the sort process
 * @return Number of comparisons made
 */
int algo::insertionSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt) {
	int numOfComparisons = 0;

	for (int n = 1; n < sortElements.size(); n++)
	{
		auto temp = sortElements[n];
		int j = n - 1;
		while (j >= 0 && temp.value <= sortElements[j].value)
		{
			if (interrupt) {
				return numOfComparisons;
			}

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
 * @param interrupt Bool to stop the sort process
 * @return tuple, first is the pivot, second is the number of comparisons
 */
static int quickSortHelper(std::vector<Sortable>& parent, SortableIterator beg, SortableIterator end, int timeSleep, const std::atomic<bool>& interrupt);
static tuple<SortableIterator, int> quickSortPartition(std::vector<Sortable>& parent, SortableIterator beg, SortableIterator end, int timeSleep, const std::atomic<bool>& interrupt);

static int quickSortHelper(std::vector<Sortable>& parent, SortableIterator beg, SortableIterator end, int timeSleep, const std::atomic<bool>& interrupt) {
	if (interrupt) {
		return 0;
	}

	// base case
	if (end - beg < 2) return 0;

	SortableIterator pivot;
	int numOfComparisons;
	std::tie(pivot, numOfComparisons) = quickSortPartition(parent, beg, end, timeSleep, interrupt);

	return numOfComparisons +
		quickSortHelper(parent, beg, pivot, timeSleep, interrupt) +
		quickSortHelper(parent, pivot + 1, end, timeSleep, interrupt);

}

static tuple<SortableIterator, int> quickSortPartition( std::vector<Sortable>& parent, SortableIterator beg, SortableIterator end, int timeSleep, const std::atomic<bool>& interrupt) {
	auto pivot = end - 1;
	int numOfComparisons = 0;

	auto lhs = beg;
	for (auto rhs = lhs; rhs != pivot; ++rhs) {
		if (interrupt) {
			return std::make_tuple(lhs, numOfComparisons);
		}

		++numOfComparisons;
		if (rhs->value <= pivot->value) {
			algoUtils::swap(parent, timeSleep, *lhs, *rhs);
			++lhs;
		}
	}
	algoUtils::swap(parent, timeSleep, *lhs, *pivot);
	return tuple<SortableIterator, int>{lhs, numOfComparisons};
}

int algo::quickSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt) {
	return quickSortHelper(sortElements, sortElements.begin(), sortElements.end(), timeSleep, interrupt);
}

/**
 * @brief Cocktail sort
 *
 * @param sortElements Main array containing the elements to be sorted
 * @param timeSleep Time to wait between iterations in miliseconds
 * @return Number of comparisons made
 */
int algo::cocktailSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt) {
	int numOfComparisons = 0;
	bool Swapped = true;
	int end = sortElements.size() - 1;
	int start = 0;

	while (Swapped == true) {

		Swapped = false;

		for (int n = 0 + start; n < end; n++) {
			if (sortElements[n].value > sortElements[n + 1].value) {
				algoUtils::swap(sortElements, timeSleep, sortElements[n], sortElements[n + 1]);
				Swapped = true;
			}
			numOfComparisons++;

			Swapped = false;
			end = end - 1;

		for (int n = 0 + end; n > start; n--) {
			if (interrupt) {
				return numOfComparisons;
			}

			if (sortElements[n].value > sortElements[n + 1].value) {
				algoUtils::swap(sortElements, timeSleep, sortElements[n], sortElements[n + 1]);
				Swapped = true;
			}
			numOfComparisons++;

			start = start + 1;
			}
		}
	}
	return numOfComparisons;
}

/**
 * @brief Bogo sort: Randomizes the array until is sorted
 * 
 * @param sortElements Main array containing the elements to be sorted
 * @param timeSleep Time to wait between iterations in miliseconds
 * @return Number of comparisons made
 */
int algo::bogoSort(std::vector<Sortable>& sortElements, int timeSleep) {
	int numOfComparisons = 0;

	std::random_shuffle(std::begin(sortElements), std::end(sortElements));
	numOfComparisons++;

	return numOfComparisons;
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
