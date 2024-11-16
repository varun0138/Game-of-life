#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Grid.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game of Life", sf::Style::Close | sf::Style::Titlebar);

    Grid grid(sf::Vector2f(60.0f, 10.0f), sf::Vector2f(GRID_WIDTH, GRID_HEIGHT), ROWS, COLS);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        window.clear(GREY);

        grid.draw(window);

        window.display();
    }

}