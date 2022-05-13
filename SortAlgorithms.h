#pragma once
#include <vector>
#include "Sortable.h"

namespace algo {
    int bubbleSort(std::vector<Sortable>& sortElements, int timeSleep);
	int selectionSort(std::vector<Sortable>& sortElements, int timeSleep);
	int insertionSort(std::vector<Sortable>& sortElements, int timeSleep);

    int quickSort(std::vector<Sortable>& sortElements, int timeSleep);
}

namespace algoUtils {
	void swap(std::vector<Sortable>& sortElements, int timeSleep, Sortable& el1, Sortable& el2);
}
