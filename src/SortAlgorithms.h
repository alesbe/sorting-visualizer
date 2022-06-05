#pragma once
#include <atomic>
#include <vector>
#include "Sortable.h"

namespace algo {
	int bubbleSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt);
	int selectionSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt);
	int insertionSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt);
	int quickSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt);
	int cocktailSort(std::vector<Sortable>& sortElements, int timeSleep, const std::atomic<bool>& interrupt);
	int bogoSort(std::vector<Sortable>& sortElements, int timeSleep);
}

namespace algoUtils {
	void swap(std::vector<Sortable>& sortElements, int timeSleep, Sortable& el1, Sortable& el2);
}
