/*
- Sort Types -
0: Bubble Sort
1: ...
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "SortController.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Sorting visualizer v0.1-alpha");

    int numOfElements = 10;
    int timeSleep = 50;
    int sortType = 0;

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
                    std::cout << "Randomizing..." << std::endl;
                    sortController.randomize();

                    std::cout << "Sort number " << sortType << " started!" << std::endl;
                    std::cout << "thread started" << std::endl;
                    //sortController.startSort(sortType);
                    break;

                // Change sort type (increase)
                case (sf::Keyboard::Up):
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
        for (int n = 0; n < sortController.sortElements.size(); n++) {
            Sortable sortable = sortController.sortElements[n];
            sf::RectangleShape shape = sortable.shape();

            shape.setPosition(sf::Vector2f(sortable.width * n, sortController.winHeight - sortable.height));
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}