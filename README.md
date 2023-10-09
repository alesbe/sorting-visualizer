# 📊 Sorting Visualizer

A lightweight sorting visualizer made with C++ and [SFML](https://www.sfml-dev.org/index.php).

| ![Quick sort gif](https://i.imgur.com/TsWwumg.gif) |
|:--:|
| *Quick sort* |

| ![Bubble visualizer](https://i.imgur.com/086SZ51.png) |
|:--:|
| *Bubble sort* |

| ![Bubble sort info](https://i.imgur.com/P5ypw86.png) |
|:--:|
| *Bubble sort info* |

## 📖 I want to contribute to the project!
Awesome! [Here](https://github.com/alesbe/sorting-visualizer/wiki) you can find some useful info about the visualizer, we accept first contributors too!

*Also, make sure to pull the last changes from [dev](https://github.com/alesbe/sorting-visualizer/tree/dev) branch!*

## 🗂️ Sort types
- Bubble sort
  - Bubble sort works by continuously swapping elements next to each other that are in the wrong place. Starting from the beginning of the dataset, each element 'floats' to its correct spot. More on Bubble sort can be found [here](https://www.geeksforgeeks.org/bubble-sort/).
- Selection sort
  - Selection sort works by having two sections, the sorted and unsorted sections, and continuously search through the unsorted section and place the smallest element into the sorted section. This sorting algorithm could be implemented where the largest element is selected instead. More on selection sort can be found [here](https://www.geeksforgeeks.org/selection-sort/).
- Insertion sort
  - Insertion sort is similar to selection sort in that they both have a sorted and unsorted section. Instead of continuously selected the smallest/largest element, it will insert a selected element from the unsorted portion and 'insert' it into the correct spot in the sorted section. More on insertion sort can be found [here](https://www.geeksforgeeks.org/insertion-sort/).
- Quick sort
  - Quick sort is a "Divide and Conquer" algorithm. Divide and Conquer algorithms work by splitting the problem into smaller portions, solving the smaller problems, then combing the solutions into one final solution. Quick sort works by choosing an element as a 'pivot', moving the other elements around where elements less than the pivot are on one side and elements greater than the pivot are on the other, then continuously doing that process with each side. Once each element has been partitioned, the solution is combined into the sorted array. More on quick sort can be found [here](https://www.geeksforgeeks.org/quick-sort/) and more on Divide and Conquer algorithms can be found [here](https://www.geeksforgeeks.org/introduction-to-divide-and-conquer-algorithm-data-structure-and-algorithm-tutorials/).
- Cocktail shaker sort
  - Cocktail shaker sort is a variant of Bubble Sort. Instead of only having elements 'float' from the bottom to its correct spot in the dataset, elements also 'sink' from the top of the datset into its correct position. More on cocktail shaker sort can be found [here](https://www.geeksforgeeks.org/cocktail-sort/).
- Bogo sort
  - Bogo sort is an inefficient sorting algorithm where it randomly generates different versions of the original dataset and checks if it's sorted or not. More on bogo sort can be found [here](https://www.geeksforgeeks.org/bogosort-permutation-sort/).
- Bitonic sort
  - Bitonic sort is a comparison based sorting algorithm that can be run with parallel implementation. Within different subarrays, the algorithm checks if the first element is smaller than the second and vice versa. It continuously does that on larger subarrays until the whole dataset is sorted. More on bitonic sort can be found [here](https://www.geeksforgeeks.org/bitonic-sort/).

## 🕹️ Usage
- **Space**: Start sort <br>
- **Backspace**: Stop sort <br>
- **h**: Display help <br>
- **F1**: Change number of elements <br>
- **F2**: Change time between comparisons <br>
- **Arrow Up / Arrow down**: Change sort type <br>

## 🖨️ Download
**Requirements:**
- CMake

### 🐧 Linux
- Clone the project: `git clone https://github.com/alesbe/sorting-visualizer && cd sorting-visualizer`
- Run `./install.sh`

### 🖥️ Windows / MacOS
The libraries included with the project only work with gcc compiler, for now, if you want to use it on Windows or macOS, you'll need to [download sfml](https://www.sfml-dev.org/download/sfml/2.5.1/) and compile the source code located in `/src` yourself.
