#include <SFML/Graphics.hpp>
#include "SortController.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Sorting visualizer v0.1-alpha - by alesbe");
    
    int numOfElements = 200;
    SortController sortController(window.getSize());
    
    sortController.populate(numOfElements); // Initialize sortable vector
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Draw sortables vector
        for (Sortable sortable : sortController.sortElements) {
            sf::RectangleShape shape = sortable.shape();
            shape.setPosition(sf::Vector2f(sortable.width * sortable.value, sortController.winHeight - sortable.height)); // temporary, this should come from SortAlgorithms.cpp
            window.draw(shape);

            // Debug
            std::cout << "Position x: " << shape.getPosition().x << " - Position y: " << shape.getPosition().y;
            std::cout << " || Width: " << sortable.width << " - Height: " << sortable.height << "\n";
        }

        window.display();
    }

    return 0;
}