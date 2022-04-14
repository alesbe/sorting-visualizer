/*
- Sort Types -
0: Bubble Sort
1: ...
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "SortController.h"

void test(int num) {
    std::cout << "Hi, this is a test and this is my number: " << num << std::endl;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Sorting visualizer v0.1-alpha");

    int numOfElements = 10;
    int timeSleep = 1;
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
                        std::cout << "Randomizing..." << std::endl;
                        sortController.randomize();

                        sortingThread = std::thread(&SortController::startSort, &sortController, sortType);
                        sortingThread.detach();
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
            shape.setPosition(sf::Vector2f(sortable.width * index++, sortController.winHeight - sortable.height));
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}