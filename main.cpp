/*
- Sort Types -
0: Bubble Sort
1: ...

Due to the 1ms resolution of timers on Windows, the speed scale is smaller. The Linux version has a higher time resoltion < 1ms!
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "SortController.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Sorting visualizer v0.2-alpha");

    // Configs
    int numOfElements = 150;
    int timeSleep = 1; // milliseconds
    int sortType = 0;

    std::thread sortingThread;

    SortController sortController(window.getSize(), timeSleep);

    sortController.populate(numOfElements);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Key events
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code)
                {

                // Randomize and start sorting
                case sf::Keyboard::Space:
                    if (!sortController.isSorting) {
                        std::cout << "Starting sort!" << std::endl;
                        sortController.clear();
                        sortController.populate(numOfElements);
                        sortController.randomize();

                        sortingThread = std::thread(&SortController::startSort, &sortController, sortType);
                        sortingThread.detach();
                    }
                    break;

                // Stop sort
                case sf::Keyboard::Backspace:
                    if (sortController.isSorting) {
                        std::cout << "Sort stopped!" << std::endl;
                        sortController.clear();
                        sortController.populate(numOfElements);
                    }
                    break;

                // Change sort type (increase)
                case sf::Keyboard::Up:
                    sortType++;
                    std::cout << "Sort changed to: " << sortType << std::endl;
                    break;

                // Change sort type (decrease)
                case sf::Keyboard::Down:
                    sortType--;
                    std::cout << "Sort changed to: " << sortType << std::endl;
                    break;

                // Change number of sortables (increase)
                case sf::Keyboard::Right:
                    numOfElements++;
                    sortController.clear();
                    sortController.populate(numOfElements);
                    std::cout << "Num of elements changed to: " << numOfElements << std::endl;
                    break;

                // Change number of sortables (decrease)
                case sf::Keyboard::Left:
                    numOfElements--;
                    sortController.clear();
                    sortController.populate(numOfElements);
                    std::cout << "Num of elements changed to: " << numOfElements << std::endl;
                    break;

                // Change number of sortables through console
                case sf::Keyboard::F1:
                    std::cout << "Number of sortables: ";
                    std::cin >> numOfElements;
                    std::cout << std::endl;

                    sortController.clear();
                    sortController.populate(numOfElements);
                    break;

                // Change time between iterations
                case sf::Keyboard::F2:
                    std::cout << "Time between iterations (milliseconds): ";
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

        // Draw sortables
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