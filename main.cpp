/*
Sorting visualizer v1.0 (static version) - by alesbe
Description: A program made with C++ and SFML to visualize sorting algorithms.

License: MIT [alesbe 2022]

github.com/alesbe/sorting-visualizer
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
    // Window
    sf::RenderWindow window(sf::VideoMode(600, 400), "Sorting visualizer v1.0");
    window.setFramerateLimit(60);

    // Configs (can be changed in runtime)
    int numOfElements = 150;
    int timeSleep = 1;
    int sortType = 0;

    // Initializations
    SortController sortController(window.getSize(), timeSleep);
    sortController.populate(numOfElements);

    std::thread sortingThread;

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Key events
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
                    system(CLEAR);
                    std::cout << "Number of elements: ";
                    std::cin >> numOfElements;
                    std::cout << std::endl;

                    sortController.clear();
                    sortController.populate(numOfElements);
                    break;

                // Change time between comparisons
                case sf::Keyboard::F2:
                    system(CLEAR);
                    std::cout << "Time between comparisons (milliseconds): ";
                    std::cin >> timeSleep;
                    std::cout << std::endl;

                    sortController.setTimeSleep(timeSleep);
                    break;

                default:
                    break;
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Draw elements
        int index = 0;
        for (auto sortable : sortController.sortElements) {
            sf::RectangleShape shape = sortable.shape();
            shape.setFillColor(sortable.color);
            shape.setPosition(sf::Vector2f(sortable.width * index++, sortController.winHeight - sortable.height));
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}
