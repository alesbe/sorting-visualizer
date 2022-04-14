#pragma once
#include <vector>

#if defined(_WIN32)
#include <Windows.h>
#define PLATFORM "windows"
#endif

#include "Sortable.h"

namespace algo {
	void bubbleSort(std::vector<Sortable>& sortElements, int timeSleep);
}