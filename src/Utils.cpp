#include "Utils.h"

const std::string kNoSort = "<NO ALGORITHM>";

/**
 * @brief Utils::getSortType - Returns the name of the algorithms providing the number asociated to it.
 * 
 * @param sortType Number associated to the algorithm
 * @return String of the algorithm name
 */
std::string Utils::getSortType(int sortType) {
	switch (sortType)
	{
	case 0:
		return "Bubble sort";

	case 1:
		return "Selection sort";

	case 2:
		return "Insertion sort";

	case 3:
		return "Quick sort";

	case 4:
		return "Cocktail sort";

	default:
		return kNoSort;
	}
}

/**
 * @brief Utils::hasNextSortType - Checks if the sort type exists
 * 
 * @param sortType Number associated to the algorithm
 * @return true The sort algorithm exists
 * @return false The sort algoritm does not exist
 */
bool Utils::hasNextSortType(int sortType) {
	return getSortType(sortType + 1) != kNoSort;
}
