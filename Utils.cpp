#include "Utils.h"

std::string Utils::getSortType(int sortType) {
	switch (sortType)
	{
	case 0:
		return "Bubble sort";

	case 1:
		return "Selection sort";

	case 2:
		return "Insertion sort";

	default:
		return std::to_string(sortType);
	}
}