#include "SortAlgorithms.h"

#include <atomic>
#include <limits>
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
int algo::bogoSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt) {
	int numOfComparisons = 0;

	std::random_shuffle(std::begin(sortElements), std::end(sortElements));
	numOfComparisons++;

	return numOfComparisons;
}

namespace bitonicUtils {

	/**
	 * @brief Bitonic merge: Recursively merge 2 bitonic sequences into 1 monotonic sequence
	 * @author @ForgotMyCode
	 * @param sortElements Main array containing the elements to be sorted
	 * @param timeSleep Time to wait between iterations in miliseconds
	 * @param interrupt Bool to stop the sort process
	 * @param begin Index of inclusive start of the sub-array
	 * @param end Index of exclusive end of the sub-array
	 * @param isMinimizing Bool, if set to true, left half of the subarray will be minimized (it will be smaller than the right subarray),
	 * 	otherwise it will be maximized (it will be larger than the right subarray)
	 * @param numOfComparisons Number of comparisons made
	 */
	void internalBitonicMerge(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt, size_t begin, size_t end, bool isMinimizing, int& numOfComparisons) {
		if(begin + size_t{1} >= end || interrupt) {
			return;
		}

		auto const mid = (begin + end) / size_t{2};
		auto const stride = mid - begin;

		for(size_t i = begin; i < mid; ++i) {
			if(isMinimizing) {
				++numOfComparisons;
				// min
				if(sortElements[i].value > sortElements[i + stride].value) {
					algoUtils::swap(sortElements, timeSleep, sortElements[i], sortElements[i + stride]);
				}
			}
			else {
				++numOfComparisons;
				// max
				if(sortElements[i].value < sortElements[i + stride].value) {
					algoUtils::swap(sortElements, timeSleep, sortElements[i], sortElements[i + stride]);
				}
			}
		}

		// recurse left
		internalBitonicMerge(sortElements, timeSleep, interrupt, begin, mid, isMinimizing, numOfComparisons);
		// recurse right
		internalBitonicMerge(sortElements, timeSleep, interrupt, mid, end, isMinimizing, numOfComparisons);
	}

	/**
	 * @brief Bitonic sort: Recursively create left and right bitonic sequences and then merge them together into a monotonic sequence
	 * @author @ForgotMyCode
	 * @param sortElements Main array containing the elements to be sorted
	 * @param timeSleep Time to wait between iterations in miliseconds
	 * @param interrupt Bool to stop the sort process
	 * @param begin Index of inclusive start of the sub-array
	 * @param end Index of exclusive end of the sub-array
	 * @param isMinimizing Bool, if set to true, left half of the subarray will be minimized (it will be smaller than the right subarray, 
	 *	results in increasing sequence), otherwise it will be maximized (it will be larger than the right subarray, results in decreasing sequence)
	 * @param numOfComparisons Number of comparisons made
	 */
	void internalBitonicSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt, size_t begin, size_t end, bool isMinimizing, int& numOfComparisons) {
		if(begin + size_t{1} >= end || interrupt) {
			return;
		}

		auto const mid = (begin + end) / size_t{2};

		// create left bitonic subsequence
		internalBitonicSort(sortElements, timeSleep, interrupt, begin, mid, true, numOfComparisons);
		// create right bitonic subsequence
		internalBitonicSort(sortElements, timeSleep, interrupt, mid, end, false, numOfComparisons);
		// merge
		internalBitonicMerge(sortElements, timeSleep, interrupt, begin, end, isMinimizing, numOfComparisons);
	}
}

/**
 * @brief Bitonic sort
 * @details Performs recursive Bitonic sort. It is recommended the input size is a power of 2,
 *	otherwise the input will be padded to the closest (not less) power of 2.
 *	The padding is removed when the sorting finishes.
 * @author @ForgotMyCode
 * @param sortElements Main array containing the elements to be sorted
 * @param timeSleep Time to wait between iterations in miliseconds
 * @param interrupt Bool to stop the sort process
 * @return Number of comparisons made
 */
int algo::bitonicSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt) {
	if(sortElements.empty() || interrupt) {
		return 0;
	}

	size_t n = sortElements.size();

	// find closest (not less) power of 2
	size_t closestNotLessPowerOf2{ 1 };
	while(closestNotLessPowerOf2 < n) {
		closestNotLessPowerOf2 *= size_t{2};
	}

	size_t const paddingSize = closestNotLessPowerOf2 - n;

	// please use a power of 2 as # of elements to avoid padding!

	// add padding
	sortElements.insert(sortElements.end(), paddingSize, Sortable(0.f, 0.f, std::numeric_limits<int>::max()));

	int numOfComparisons = 0;

	// sort
	bitonicUtils::internalBitonicSort(sortElements, timeSleep, interrupt, size_t{0}, sortElements.size(), true, numOfComparisons);

	// remove padding
	sortElements.erase(std::next(sortElements.begin(), n), sortElements.end());

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
