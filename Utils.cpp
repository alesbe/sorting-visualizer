#include "Utils.h"

const std::string kNoSort = "<NO ALGORITHM>";

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

	default:
        return kNoSort;
	}
}

bool Utils::hasNextSortType(int sortType) {
    return getSortType(sortType + 1) != kNoSort;
}
