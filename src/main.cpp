/**
 * @name Sorting visualizer v1.0 (static version)
 * @author alesbe - github.com/alesbe/
 * @brief A lightweight sorting visualizer made with C++ and SFML.
 * @version v1.1
 * 
 * @copyright License - MIT [alesbe 2022]
 * 
 */

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "SortController.h"
#include "Utils.h"

int main()
{
	// Window settings
	sf::RenderWindow window(sf::VideoMode(600, 400), "Sorting visualizer v1.1");
	window.setFramerateLimit(60);

	// Visualizer settings (can be changed on runtime through the key events)
	int numOfElements = 150;
	int timeSleep = 1;
	int sortType = 0;

	// Initialize SortController
	SortController sortController(window.getSize(), timeSleep);
	sortController.populate(numOfElements);

	// Declare thread used to sort the array in parallel with the sfml/draw thread
	std::thread sortingThread;

	// Main loop
	while (window.isOpen())
	{

		// Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code)
				{

				// Start sort
				case sf::Keyboard::Space:
					if (!sortController.isSorting) {
						sortController.clear();
						sortController.populate(numOfElements);
						sortController.randomize();

						// Move sorting to a different thread (main thread will be drawing and can't be blocked)
						sortingThread = std::thread(&SortController::startSort, &sortController, sortType);
						sortingThread.detach();
					}
					break;

				// Stop sort
				case sf::Keyboard::Backspace:
					if (sortController.isSorting) {
						system(CLEAR);
						std::cout << "Sort stopped!" << std::endl;
						sortController.clear();
						sortController.populate(numOfElements);
					}
					break;

				// Display help
				case sf::Keyboard::H:
					system(CLEAR);
					std::cout << "[Space]: Start sort" << std::endl;
					std::cout << "[Backspace]: Stop sort" << std::endl;
					std::cout << "[Up/Down Arrows]: Change sort type" << std::endl;
					std::cout << "[F1]: Change number of elements" << std::endl;
					std::cout << "[F2]: Change time between comparisons" << std::endl;
					break;

				// Change sort type (increase)
				case sf::Keyboard::Up:
					if (sortType >= 0 && Utils::hasNextSortType(sortType)) {
						sortType++;
						system(CLEAR);
						std::cout << "Sort changed to: " << Utils::getSortType(sortType) << std::endl;
					}
					break;

				// Change sort type (decrease)
				case sf::Keyboard::Down:
					if (sortType > 0) {
						sortType--;
						system(CLEAR);
						std::cout << "Sort changed to: " << Utils::getSortType(sortType) << std::endl;
					}
					break;

				// Change number of elements
				case sf::Keyboard::F1:
					if(!sortController.isSorting) {
						system(CLEAR);
						std::cout << "Number of elements: ";
						std::cin >> numOfElements;
						std::cout << std::endl;

						sortController.clear();
						sortController.populate(numOfElements);
						break;
					}

				// Change time between comparisons
				case sf::Keyboard::F2:
					if(!sortController.isSorting) {
						system(CLEAR);
						std::cout << "Time between comparisons (milliseconds): ";
						std::cin >> timeSleep;
						std::cout << std::endl;

						sortController.setTimeSleep(timeSleep);
						break;
					}

				default:
					break;
				}
			}

			// Close window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Clear screen between each frame
		window.clear(sf::Color::Black);

		// Draw array elements
		int index = 0;
		for (auto sortable : sortController.sortElements) {
			sf::RectangleShape shape = sortable.shape();
			shape.setFillColor(sortable.color);
			shape.setPosition(sf::Vector2f(sortable.width * index++, sortController.winHeight - sortable.height));
			window.draw(shape);
		}

		// Display drawed content on screen
		window.display();
	}

	return 0;
}
